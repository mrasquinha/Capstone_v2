/*
 * =====================================================================================
 *
 *       Filename:  dram.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/23/2010 07:25:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SYED MINHAJ HASSAN
 *        Company:  Georgia Institute of Technology
 *
 * =====================================================================================
 */

#include <math.h>
#include "dram.h"
#include "../MemCtrl/bus.h"
#include "../MemCtrl/cmd_issuer.h"
#include "../MemCtrl/data_bus_handler.h"
#include "MC.h"

using namespace std;

/*
 *--------------------------------------------------------------------------------------
 *       Class:  DRAM
 *      Method:  DRAM
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */

DRAM::DRAM()
{
    for (unsigned int i=0; i<NO_OF_CHANNELS; i++)
    {
    	dc[i].dramBusyTime = 0;
    	dc[i].dramBusyCycles = 0;	
    	for (unsigned int j=0; j<NO_OF_CHANNELS; j++)
    	{
    	    for (unsigned int k=0; k<NO_OF_CHANNELS; k++)
    	    {
		dc[i].dramBankBusyTime[j][k] = 0;
    		dc[i].dramBankBusyCycles[j][k] = 0;	
	    }	    
	}
    }
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  DRAM
 *      Method:  ~DRAM
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */
DRAM::~DRAM()
{
   // delete[] dc;
}

void DRAM::SetLinks()
{
    for (unsigned int i=0; i<NO_OF_CHANNELS; i++)
    {
	dc[i].parent = this;
	dc[i].mc = mc;
	dc[i].child = (Component*)(&((Bus*)parent)->dataBus[i]);
    }  			
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  DRAM
 *      Method:  process_event
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void DRAM::process_event(IrisEvent* e)
{
/*  DRAMCmd cmd;
    IrisEvent *event = new IrisEvent();
    cmd = e->event_data.at(0);
    map_addr(req);
    event->source = (Component*)this;
    event->dst = (Component*)child;
    event->event_data.push_back((void*)cmd);

    Simulator::Schedule(Simulator::Now()+1, &DRAM[i]::process_event, (DRAM*)event->dst, event);    	
   */
   delete e;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  DRAM
 *      Method:  DRAM
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */

DRAMChannel::DRAMChannel()
{
   	
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  DRAM
 *      Method:  ~DRAM
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */
DRAMChannel::~DRAMChannel()
{

}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  DRAM
 *      Method:  process_event
 * Description:  ((Bus*)((DRAM*)parent)->parent)->
 *--------------------------------------------------------------------------------------
 */
void DRAMChannel::process_event(IrisEvent* e)
{
//    DRAMCmdState *cmd = new DRAMCmdState();
    IrisEvent *event = new IrisEvent();
    DRAMCmdState *cmd = ((DRAMCmdState*)e->event_data.at(0));	//TODO needs to set this through manifold kernel's links	

    switch (cmd->cmd)
    {
	case PRECHARGE: 
             dramBusyTime = Simulator::Now()+t_RP;
	     dramBankBusyTime[cmd->req.rankNo][cmd->req.bankNo] = Simulator::Now()+t_RP;	
	     break;
	case ACTIVATE:
             dramBusyTime = Simulator::Now()+t_RCD;
	     dramBankBusyTime[cmd->req.rankNo][cmd->req.bankNo] = Simulator::Now()+t_RCD;	
	     break;
	case WRITE:
             dramBusyTime = Simulator::Now()+t_WR;
	     dramBankBusyTime[cmd->req.rankNo][cmd->req.bankNo] = Simulator::Now()+t_WR;	
	     break;
	case READ:
             dramBusyTime = Simulator::Now()+t_CAS;
	     dramBankBusyTime[cmd->req.rankNo][cmd->req.bankNo] = Simulator::Now()+t_CAS;	
	     break;
	case ALL_BANK_REFRESH:
             dramBusyTime = Simulator::Now()+t_RFC;
	     for (unsigned int i=0; i<NO_OF_BANKS; i++)
	     {		
	     	dramBankBusyTime[cmd->req.rankNo][i] = Simulator::Now()+t_RFC;
    		if (dramBankBusyCycles[cmd->req.rankNo][i] > Simulator::Now())
    	    	    dramBankBusyCycles[cmd->req.rankNo][i] += 
			(dramBankBusyTime[cmd->req.rankNo][i]-dramBankBusyCycles[cmd->req.rankNo][i]);
    		else	
    	    	    dramBankBusyCycles[cmd->req.rankNo][i] += 
			(dramBankBusyTime[cmd->req.rankNo][i]-Simulator::Now());
	     }
	     break;
        default:
	     cout << "Unknown DRAM command reached DRAM" << endl;	

    }
    if (dramBusyCycles > Simulator::Now())
    	dramBusyCycles += (dramBusyTime-dramBusyCycles);
    else	
    	dramBusyCycles += (dramBusyTime-Simulator::Now());
    if (cmd->cmd != ALL_BANK_REFRESH)
    {
    	if (dramBankBusyCycles[cmd->req.rankNo][cmd->req.bankNo] > Simulator::Now())
    	    dramBankBusyCycles[cmd->req.rankNo][cmd->req.bankNo] += 
			(dramBankBusyTime[cmd->req.rankNo][cmd->req.bankNo]-dramBankBusyCycles[cmd->req.rankNo][cmd->req.bankNo]);
    	else	
    	    dramBankBusyCycles[cmd->req.rankNo][cmd->req.bankNo] += 
			(dramBankBusyTime[cmd->req.rankNo][cmd->req.bankNo]-Simulator::Now());
    }   

    switch (e->type)
    {
	case START_READ:
#ifdef DEEP_DEBUG
	    cout << dec << Simulator::Now() << ": " << hex << cmd->req.address << ": I am in DRAM READ with " << dec << cmd->cmd << endl;	
#endif		     
	    if (cmd->cmd == READ)
	    {		     
		event->src = (Component*)this;
	    	event->dst = child;
	     	event->type = START_READ;	
	     	event->event_data.push_back((void*)cmd);	//TODO needs to set this through manifold kernel's links

	     	Simulator::Schedule(Simulator::Now()+t_CAS+1, &DataBusHandler::process_event, (DataBusHandler*)event->dst, event); 
	    }  
	    else
	    {
		delete cmd;
		delete event;
	    }	 	
	break;
	case START_WRITE:
#ifdef DEEP_DEBUG
		cout << dec << Simulator::Now() << ": " << hex << cmd->req.address << ": I am in DRAM WRITE with " << dec << cmd->cmd << endl;
#endif
		cmd->req.retireTime = Simulator::Now()+t_WR;
#ifdef DEBUG
		cout << dec << Simulator::Now()+t_WR << ": " << hex << cmd->req.address << ": Total Time taken by request " << dec << cmd->req.retireTime - cmd->req.arrivalTime << endl;
#endif
		((MC*)mc)->stats->CollectStatsPerRequest(&cmd->req);
		delete cmd;
		delete event;
	break;
	default:
		delete cmd;
		delete event;
#ifdef DEBUG
		cout << Simulator::Now() << ": I should not come to default of process event in DRAM\n";
#endif
	break;
    }
    
  //  if (!e->event_data.empty())	
  //  	delete ((DRAMCmdState*)e->event_data.at(0));	
    delete e;
}


