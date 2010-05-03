/*
 * =====================================================================================
 *
 *       Filename:  mshr.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/12/2010 12:43:15 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SYED MINHAJ HASSAN
 *        Company:  Georgia Institute of Technology
 *
 * =====================================================================================
 */

#include <math.h>
#include "mshr.h"

using namespace std;

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MSHR_H
 *      Method:  MSHR_H
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */

MSHR_H::MSHR_H()
{
    unsink = 0;
    globalUnSink = 0;
    lastFinishTime = 0;	
    done = 0;
    lastScheduledIndex = 0;	
    mshr.clear();
    writeQueue.clear();			
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MSHR_H
 *      Method:  ~MSHR_H
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */
MSHR_H::~MSHR_H()
{
     mshr.clear();
     writeQueue.clear();		
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MSHR_H
 *      Method:  process_event
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void MSHR_H::process_event(IrisEvent* e)
{
    Addr_t addr;
    UInt thread_id;
    Time time;
    UInt cmd;	
	
    if (mshr.size() >= MSHR_SIZE)
    {
	unsink++;
    	Request * req = new Request();	
    	IrisEvent *event = new IrisEvent();
    	*req = *((Request*)e->event_data.at(0));	//TODO needs to set this through manifold kernel's links
    	event->src = (Component*)this;
    	event->dst = (Component*)this;
    	event->event_data.push_back(req);	
#ifdef DEEP_DEBUG
  //  	cout << dec << Simulator::Now() << ": " << hex << req->address << ": MSHR Full Now Waiting " << endl;	
#endif
    	Simulator::Schedule(Simulator::Now()+1, &MSHR_H::process_event, (MSHR_H*)event->dst, event);  
    }
    else
    {
	Request * req = new Request();
	*req = *((Request*)e->event_data.at(0));	//TODO needs to set this through manifold kernel's links
	if (req->cmdType!=CACHE_WRITEBACK)
	    mshr.push_back(*req);
	else
	    writeQueue.push_back(*req);	 
	
	    	
#ifdef DEEP_DEBUG
    	cout << dec << Simulator::Now() << ": " << hex << req->address << ": " << id << " PUSHED IN MSHR of size " << mshr.size() << endl;	
#endif
//	delete req;
	if (!trace_filename.eof())
	{
	    trace_filename >> hex >> addr;
	    trace_filename >> thread_id;	
	    trace_filename >> dec >> time;
	    trace_filename >> dec >> cmd; 

//	    if (!trace_filename.eof())	
	    	time = time+lastFinishTime;
	    if (trace_filename.eof())
	    {
	    	if (done == 0)
	    	{
		    done = 1;			//TODO needs to set this
	//	    cout << "thread done " << id << endl;
	    	}	
	    	lastFinishTime = Simulator::Now();
	    	globalUnSink += unsink;
	    	unsink = 0;
	    	cout << dec << "lastFinishTime = " << lastFinishTime << ", " << id << ", " << globalUnSink << endl;	

	    	trace_filename.close();	
	    	trace_filename.open(filename,ios::in);
    	    	if(!trace_filename.is_open())
    	    	{
	    	    cout<<"Err opening trace"<<endl;
	   	    exit(1);
    	    	}	
	   
	    	if (!trace_filename.eof())
	    	{ 
            	    trace_filename >> hex >> addr;
	    	    trace_filename >> thread_id;	
	    	    trace_filename >> dec >> time;
	    	    trace_filename >> dec >> cmd;
		
		    if (!trace_filename.eof())
		    	time = time+lastFinishTime;	
	    	}
	    }
	}
	
	
	

    	Request *req2 = new Request();
	req2->cmdType = (Command_t)cmd;
	req2->address = addr;
	req2->arrivalTime = time+unsink;
	req2->threadId = id;
	req2->address = GlobalAddrMap(req2->address,id);

	IrisEvent *event = new IrisEvent();
    	event->src = (Component*)this;
    	event->dst = (Component*)this;
    	event->event_data.push_back(req2);	
    	Simulator::Schedule(time+unsink, &MSHR_H::process_event, (MSHR_H*)event->dst, event);  
    }
//    delete (Request*)e->event_data.at(0);	
//    delete e;
}

Addr_t MSHR_H::GlobalAddrMap(Addr_t addr, UInt threadId)
{
    Addr_t newAddr;
    unsigned int threadBits = ceil(log2(NO_OF_THREADS));
    unsigned int threadBitsPos = THREAD_BITS_POSITION;
    Addr_t lowerMask = (Addr_t)pow(2,threadBitsPos)-1;
    Addr_t upperMask = 0xFFFFFFFF << threadBitsPos;
    Addr_t lowerAddr = addr & lowerMask;
    Addr_t upperAddr = addr & upperMask;
    Addr_t threadAddr = (threadId & ((Addr_t)pow(2,threadBits)-1));
    newAddr = lowerAddr | (threadAddr << threadBitsPos)| (upperAddr << threadBits);
//    cout << hex << addr << ", " << threadId << ", " << newAddr << endl;	
    return newAddr;
}

