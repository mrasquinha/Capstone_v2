/*
 * =====================================================================================
 *
 *       Filename:  stats.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/13/2010 06:53:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SYED MINHAJ HASSAN
 *        Company:  Georgia Institute of Technology
 *
 * =====================================================================================
 */
#include "MC.h"
#include "../MemCtrl/stats.h"

void Statistic::CollectStatsPerRequest(Request *req)
{
 //   if (!(*doneOnce[req->threadId]))	
    {	
    ///////// calculating runing average ////////////////

    avgLatPerThreadPerBank[req->threadId][req->bankNo] 
	= ( avgLatPerThreadPerBank[req->threadId][req->bankNo] * 1.0 / (reqPerThreadPerBank[req->threadId][req->bankNo] + 1) )
	* ( reqPerThreadPerBank[req->threadId][req->bankNo] * 1.0 )	
	+ ( (req->retireTime - req->arrivalTime) * 1.0 / (reqPerThreadPerBank[req->threadId][req->bankNo] + 1) );
    
    avgThrottlePerThreadPerBank[req->threadId][req->bankNo] 
	= ( avgThrottlePerThreadPerBank[req->threadId][req->bankNo] * 1.0 / (reqPerThreadPerBank[req->threadId][req->bankNo] + 1) )
	* ( reqPerThreadPerBank[req->threadId][req->bankNo] * 1.0 )	
	+ ( req->throttleTime * 1.0 / (reqPerThreadPerBank[req->threadId][req->bankNo] + 1) );

    reqPerThreadPerBank[req->threadId][req->bankNo]++;	
    latPerThreadPerBank[req->threadId][req->bankNo] += (req->retireTime - req->arrivalTime);
    
    TotalFrontSideTimePerThreadPerBank[req->threadId][req->bankNo] += (req->rbufferInsertionTime - req->arrivalTime);
    TotalQueueDelayPerThreadPerBank[req->threadId][req->bankNo] += (req->cbufferInsertionTime - req->rbufferInsertionTime);
    TotalCBufDelayPerThreadPerBank[req->threadId][req->bankNo] += (req->busInsertionTime - req->cbufferInsertionTime);
    TotalBusMemDelayPerThreadPerBank[req->threadId][req->bankNo] += (req->retireTime - req->busInsertionTime - 1);
#ifdef DEBUG
    cout << "MC[" << ((MC*)mc)->id << "] " << req->address << ": " << Simulator::Now() 
	<<  ": Reached stats collection with arrival Time = "<< req->arrivalTime 
	<< ", req buffer insertion time = " << req->rbufferInsertionTime 
	<< " cmd queue insertion time = " << req->cbufferInsertionTime 
	<< ", bus insertion time = " << req->busInsertionTime 
	<< "and retire time = " << req->retireTime << endl;
#endif
    //throttlePerThreadPerBank[req->threadId][req->bankNo] += req->throttleTime;	
    if (req->status == OPEN)    
	hitsPerThreadPerBank[req->threadId][req->bankNo]++;
    hitRatePerThreadPerBank[req->threadId][req->bankNo] =  hitsPerThreadPerBank[req->threadId][req->bankNo] * 100.0
							 / reqPerThreadPerBank[req->threadId][req->bankNo];  
    }
//      cout << req->status << endl;
//    cout << "Latency " << latPerThreadPerBank[req->threadId][req->bankNo] << endl;
//    cout << "Average Latency " << avgLatPerThreadPerBank[req->threadId][req->bankNo] << endl;
//    cout << "Requests " << reqPerThreadPerBank[req->threadId][req->bankNo] << endl;
//    cout << "Hits " << hitsPerThreadPerBank[req->threadId][req->bankNo] << endl;
//    cout << "Hit Rate " << hitRatePerThreadPerBank[req->threadId][req->bankNo] << endl;
	
}

void Statistic::CollectStatsPerCycle()
{
    for (unsigned int i=0; i<NO_OF_CHANNELS; i++)
    {
	for (unsigned int j=0; j<NO_OF_RANKS; j++)
    	{
	    for (unsigned int k=0; k<NO_OF_BUFFERS; k++)
    	    {
//		if ( ((MC*)mc)->reqH->chan[i].rank[j].rbuffer[k].empty() )
//		    emptyCycles[i][j][k]++;
//		rbufferOccupancy[i][j][k] += ((MC*)mc)->reqH->chan[i].rank[j].rbuffer[k].size();
	    }
	}
    }		
    
}

void Statistic::InitStats()
{
    for (unsigned int i=0; i<NO_OF_CHANNELS; i++)
    {
	for (unsigned int j=0; j<NO_OF_RANKS; j++)
    	{
	    for (unsigned int k=0; k<NO_OF_BUFFERS; k++)
    	    {
		emptyCycles[i][j][k] = 0;
		rbufferOccupancy[i][j][k] = 0;
	    }	
	}
    }		
/*    for (unsigned int i=0; i<NO_OF_CHANNELS; i++)
    {
	for (unsigned int j=0; j<NO_OF_RANKS; j++)
    	{
	    for (unsigned int k=0; k<NO_OF_BUFFERS; k++)
    	    {
		rbufferOccupancy[i][j][k] += ((MC*)mc)->reqH->chan[i].rank[j].rbuffer[k].size();
	    }
	}
    }		
*/	
    for (unsigned int i=0; i<NO_OF_THREADS; i++)	
    {
	avgLatPerThread[i] = 0.0;
	latPerThread[i] = 0;
	reqPerThread[i] = 0;
    	hitsPerThread[i] = 0;
	hitRatePerThread[i] = 0.0;
    	BLPPerThread[i] = 0.0;
	avgThrottlePerThread[i] = 0.0;
	throttlePerThread[i] = 0;
	avgFrontSideTimePerThread[i] = 0;
	avgQueueDelayPerThread[i] = 0;
	avgCBufDelayPerThread[i] = 0;
	avgBusMemDelayPerThread[i] = 0;	
	TotalFrontSideTimePerThread[i] = 0;
	TotalQueueDelayPerThread[i] = 0;
	TotalCBufDelayPerThread[i] = 0;
	TotalBusMemDelayPerThread[i] = 0;	
    }

    for (unsigned int i=0; i<NO_OF_BANKS; i++)
    {
	avgLatPerBank[i] = 0.0;
	latPerBank[i] = 0;
    	reqPerBank[i] = 0;
    	hitsPerBank[i] = 0;
    	hitRatePerBank[i] = 0.0;
	avgThrottlePerBank[i] = 0.0;
	throttlePerBank[i] = 0;
	avgFrontSideTimePerBank[i] = 0;
	avgQueueDelayPerBank[i] = 0;
	avgCBufDelayPerBank[i] = 0;
	avgBusMemDelayPerBank[i] = 0;	
	TotalFrontSideTimePerBank[i] = 0;
	TotalQueueDelayPerBank[i] = 0;
	TotalCBufDelayPerBank[i] = 0;
	TotalBusMemDelayPerBank[i] = 0;	
    }	

    for (unsigned int i=0; i<NO_OF_THREADS; i++)	
    {
	for (unsigned int j=0; j<NO_OF_BANKS; j++)
        {	 
	    avgLatPerThreadPerBank[i][j] = 0.0;
	    latPerThreadPerBank[i][j] = 0;   
	    reqPerThreadPerBank[i][j] = 0;
	    hitsPerThreadPerBank[i][j] = 0;
	    hitRatePerThreadPerBank[i][j] = 0.0;
	    avgThrottlePerThreadPerBank[i][j] = 0.0;
	    throttlePerThreadPerBank[i][j] = 0;
	   
	    TotalFrontSideTimePerThreadPerBank[i][j] = 0;
	    TotalQueueDelayPerThreadPerBank[i][j] = 0;
	    TotalCBufDelayPerThreadPerBank[i][j] = 0;
	    TotalBusMemDelayPerThreadPerBank[i][j] = 0;	
	}
    }
}

void Statistic::CalculateAggregateStats()
{
    for (unsigned int i=0; i<NO_OF_CHANNELS; i++)
    {
	for (unsigned int j=0; j<NO_OF_RANKS; j++)
    	{
	    for (unsigned int k=0; k<NO_OF_BANKS; k++)
    	    {
                if (((MC*)mc)->reqH->chan[i].rank[j].bank[k].bufferOccupancy != 0)
		    rbufferOccupancyRatio[i][j][k] = ((MC*)mc)->reqH->chan[i].rank[j].bank[k].bufferSize*1.0 / ((MC*)mc)->reqH->chan[i].rank[j].bank[k].bufferOccupancy;
		
		bufferFullCycles[i][j][k] = ((MC*)mc)->reqH->chan[i].rank[j].bank[k].bufferFullCounter;
	    }
	}
    }		
    for (unsigned int j=0; j<NO_OF_BANKS; j++)
    {    	
	for (unsigned int i=0; i<NO_OF_THREADS; i++)	
    	{
	    
	    latPerBank[j] += latPerThreadPerBank[i][j];
	    throttlePerBank[j] += throttlePerThreadPerBank[i][j];	
	    reqPerBank[j] += reqPerThreadPerBank[i][j];
	    hitsPerBank[j] += hitsPerThreadPerBank[i][j];
	    avgLatPerBank[j] += (avgLatPerThreadPerBank[i][j] * reqPerThreadPerBank[i][j]);
	    avgThrottlePerBank[j] += (avgThrottlePerThreadPerBank[i][j] * reqPerThreadPerBank[i][j]);		
	//    avgFrontSideTimePerBank[j] += (avgFrontSideTimePerThreadPerBank[i][j] * reqPerThreadPerBank[i][j]);
	//    avgQueueDelayPerBank[j] += (avgQueueDelayPerThreadPerBank[i][j] * reqPerThreadPerBank[i][j]);
	//    avgCBufDelayPerBank[j] += (avgCBufDelayPerThreadPerBank[i][j] * reqPerThreadPerBank[i][j]);
	//    avgBusMemDelayPerBank[j] += (avgBusMemDelayPerThreadPerBank[i][j] * reqPerThreadPerBank[i][j]);	
	    TotalFrontSideTimePerBank[j] += TotalFrontSideTimePerThreadPerBank[i][j];
	    TotalQueueDelayPerBank[j] += TotalQueueDelayPerThreadPerBank[i][j];
	    TotalCBufDelayPerBank[j] += TotalCBufDelayPerThreadPerBank[i][j];
	    TotalBusMemDelayPerBank[j] += TotalBusMemDelayPerThreadPerBank[i][j];	
    	}
	if (reqPerBank[j] !=0 ) 
	{
    	avgLatPerBank[j] = avgLatPerBank[j] / reqPerBank[j];
	avgThrottlePerBank[j] = avgThrottlePerBank[j] / reqPerBank[j];
        hitRatePerBank[j] += hitsPerBank[j] * 100.0 / reqPerBank[j];

	avgFrontSideTimePerBank[j] = TotalFrontSideTimePerBank[j]*1.0 / reqPerBank[j];
	avgQueueDelayPerBank[j] = TotalQueueDelayPerBank[j]*1.0 / reqPerBank[j];
	avgCBufDelayPerBank[j] = TotalCBufDelayPerBank[j]*1.0 / reqPerBank[j];
	avgBusMemDelayPerBank[j] = TotalBusMemDelayPerBank[j]*1.0 / reqPerBank[j];	
	}
    }
    
    for (unsigned int i=0; i<NO_OF_THREADS; i++)	
    {   	
	for (unsigned int j=0; j<NO_OF_BANKS; j++)
    	{ 
	    latPerThread[i] += latPerThreadPerBank[i][j];
	    throttlePerThread[i] += throttlePerThreadPerBank[i][j];
	    reqPerThread[i] += reqPerThreadPerBank[i][j];
	    hitsPerThread[i] += hitsPerThreadPerBank[i][j];
	    avgLatPerThread[i] += (avgLatPerThreadPerBank[i][j] * reqPerThreadPerBank[i][j]);
	    avgThrottlePerThread[i] += (avgThrottlePerThreadPerBank[i][j] * reqPerThreadPerBank[i][j]);		
	//    avgFrontSideTimePerThread[i] += (avgFrontSideTimePerThreadPerBank[i][j] * reqPerThreadPerBank[i][j]);
	//    avgQueueDelayPerThread[i] += (avgQueueDelayPerThreadPerBank[i][j] * reqPerThreadPerBank[i][j]);
	//    avgCBufDelayPerThread[i] += (avgCBufDelayPerThreadPerBank[i][j] * reqPerThreadPerBank[i][j]);
	//    avgBusMemDelayPerThread[i] += (avgBusMemDelayPerThreadPerBank[i][j] * reqPerThreadPerBank[i][j]);	
	    TotalFrontSideTimePerThread[i] += TotalFrontSideTimePerThreadPerBank[i][j];
	    TotalQueueDelayPerThread[i] += TotalQueueDelayPerThreadPerBank[i][j];
	    TotalCBufDelayPerThread[i] += TotalCBufDelayPerThreadPerBank[i][j];
	    TotalBusMemDelayPerThread[i] += TotalBusMemDelayPerThreadPerBank[i][j];	
    	}
	if (reqPerThread[i])
	{
	avgLatPerThread[i] = avgLatPerThread[i] / reqPerThread[i];
	avgThrottlePerThread[i] = avgThrottlePerThread[i] / reqPerThread[i];
        hitRatePerThread[i] += hitsPerThread[i] * 100.0 / reqPerThread[i];
	
	avgFrontSideTimePerThread[i] = TotalFrontSideTimePerThread[i]*1.0 / reqPerThread[i];
	avgQueueDelayPerThread[i] = TotalQueueDelayPerThread[i]*1.0 / reqPerThread[i];
	avgCBufDelayPerThread[i] = TotalCBufDelayPerThread[i]*1.0 / reqPerThread[i];
	avgBusMemDelayPerThread[i] = TotalBusMemDelayPerThread[i]*1.0 / reqPerThread[i];	
	}
    }		
}

string Statistic::PrintAggregateStats( uint n)
{
    stringstream str;
    str << dec;	
/*    for (unsigned int i=0; i<NO_OF_THREADS; i++)	
    {   	
	for (unsigned int j=0; j<NO_OF_BANKS; j++)
    	{ 
	    str << "MC [" << n << "] " << "Total Request  for Thread " << i << ", bank " << j << " = " << reqPerThreadPerBank[i][j] << endl;
	}
    }
    str << endl;			

    for (unsigned int i=0; i<NO_OF_THREADS; i++)	
    {   	
	for (unsigned int j=0; j<NO_OF_BANKS; j++)
    	{ 
		str << "MC [" << n << "] " << "Avg Latency for Thread " << i << ", bank " << j << " = " << avgLatPerThreadPerBank[i][j] << endl;
	}
    }

    str << endl;			
    for (unsigned int i=0; i<NO_OF_THREADS; i++)	
    {   	
	for (unsigned int j=0; j<NO_OF_BANKS; j++)
    	{ 
		str << "Avg Throttling time for Thread " << i << ", bank " << j << " = " << avgThrottlePerThreadPerBank[i][j] << endl;
	}
    str << endl;			
    }
    str << endl;			
    
    for (unsigned int i=0; i<NO_OF_THREADS; i++)	
    {   	
	for (unsigned int j=0; j<NO_OF_BANKS; j++)
    	{ 
	    str << "MC [" << n << "] " << "Hits for Thread " << i << ", bank " << j << " = " << hitsPerThreadPerBank[i][j] << endl;
	}
    str << endl;			
    }	


    for (unsigned int i=0; i<NO_OF_THREADS; i++)	
    {   	
	for (unsigned int j=0; j<NO_OF_BANKS; j++)
    	{ 
	    str << "MC [" << n << "] " << "Hit Rate for Thread " << i << ", bank " << j << " = " << hitRatePerThreadPerBank[i][j] << endl;
	}
    str << endl;			
    }	

    for (unsigned int i=0; i<NO_OF_THREADS; i++)	
    {   	
	for (unsigned int j=0; j<NO_OF_BANKS; j++)
    	{ 
	    str << "MC [" << n << "] " << "Total FrontSide Time for Thread " << i << ", bank " << j << " = " << TotalFrontSideTimePerThreadPerBank[i][j] << endl;
	}
    str << endl;			
    }	

    for (unsigned int i=0; i<NO_OF_THREADS; i++)	
    {   	
	for (unsigned int j=0; j<NO_OF_BANKS; j++)
    	{ 
	    str << "MC [" << n << "] " << "Total Queuing Delay for Thread " << i << ", bank " << j << " = " << TotalQueueDelayPerThreadPerBank[i][j] << endl;
	}
    str << endl;			
    }	
    for (unsigned int i=0; i<NO_OF_THREADS; i++)	
    {   	
	for (unsigned int j=0; j<NO_OF_BANKS; j++)
    	{ 
	    str << "MC [" << n << "] " << "Total Cmd Buffer Time for Thread " << i << ", bank " << j << " = " << TotalCBufDelayPerThreadPerBank[i][j] << endl;
	}
    str << endl;			
    }	
    for (unsigned int i=0; i<NO_OF_THREADS; i++)	
    {   	
	for (unsigned int j=0; j<NO_OF_BANKS; j++)
    	{ 
	    str << "MC [" << n << "] " << "Total Bus & Memory Time for Thread " << i << ", bank " << j << " = " << TotalBusMemDelayPerThreadPerBank[i][j] << endl;
	}
    str << endl;			
    }	

*/
    for (unsigned int i=0; i<NO_OF_THREADS; i++)	
    {   	
	str << "MC [" << n << "] " << "Total Request  for Thread " << i << " = " << reqPerThread[i] << endl;
    }
    str << endl;			
   
    for (unsigned int i=0; i<NO_OF_THREADS; i++)	
    {   	
	str << "MC [" << n << "] " << "Hits  for Thread " << i << " = " << hitsPerThread[i] << endl;
    }
    str << endl;			

    for (unsigned int i=0; i<NO_OF_THREADS; i++)	
    {   	
	str << "MC [" << n << "] " << "Hit Rate  for Thread " << i << " = " << hitRatePerThread[i] << endl;
    }
    str << endl;			

    for (unsigned int i=0; i<NO_OF_THREADS; i++)	
    {   	
	str << "MC [" << n << "] " << "Average Latency  for Thread " << i << " = " << avgLatPerThread[i] << endl;
    }
    str << endl;			

    for (unsigned int i=0; i<NO_OF_THREADS; i++)	
    {   	
	str << "MC [" << n << "] " << "Average FrontSide Time for Thread " << i << " = " << avgFrontSideTimePerThread[i] << endl;
    }
    str << endl;			

    for (unsigned int i=0; i<NO_OF_THREADS; i++)	
    {   	
	str << "MC [" << n << "] " << "Average Queueing Delay for Thread " << i << " = " << avgQueueDelayPerThread[i] << endl;
    }
    str << endl;			

    for (unsigned int i=0; i<NO_OF_THREADS; i++)	
    {   	
	str << "MC [" << n << "] " << "Average Cmd Buffer Time for Thread " << i << " = " << avgCBufDelayPerThread[i] << endl;
    }
    str << endl;			

    for (unsigned int i=0; i<NO_OF_THREADS; i++)	
    {   	
	str << "MC [" << n << "] " << "Average Bus & Memory Delay for Thread " << i << " = " << avgBusMemDelayPerThread[i] << endl;
    }
    str << endl;			

/*    for (unsigned int i=0; i<NO_OF_THREADS; i++)	
    {   	
	str << "MC [" << n << "] " << "Average Throttling time for Thread " << i << " = " << avgThrottlePerThread[i] << endl;
    }
    str << endl;			
*/

 				
    for (unsigned int i=0; i<NO_OF_BANKS; i++)	
    {   	
	str << "MC [" << n << "] " << "Total Request  for Bank " << i << " = " << reqPerBank[i] << endl;
    }
    str << endl;			
   
    for (unsigned int i=0; i<NO_OF_BANKS; i++)	
    {   	
	str << "MC [" << n << "] " << "Hits  for Bank " << i << " = " << hitsPerBank[i] << endl;
    }
    str << endl;			

    for (unsigned int i=0; i<NO_OF_BANKS; i++)	
    {   	
	str << "MC [" << n << "] " << "Hit Rate  for Bank " << i << " = " << hitRatePerBank[i] << endl;
    }
    str << endl;			

    for (unsigned int i=0; i<NO_OF_BANKS; i++)	
    {   	
	str << "MC [" << n << "] " << "Average Latency  for Bank " << i << " = " << avgLatPerBank[i] << endl;
    }
    str << endl;			

    for (unsigned int i=0; i<NO_OF_BANKS; i++)	
    {   	
	str << "MC [" << n << "] " << "Average FrontSide Time for Bank " << i << " = " << avgFrontSideTimePerBank[i] << endl;
    }
    str << endl;			

    for (unsigned int i=0; i<NO_OF_BANKS; i++)	
    {   	
	str << "MC [" << n << "] " << "Average Queueing Delay for Bank " << i << " = " << avgQueueDelayPerBank[i] << endl;
    }
    str << endl;			

    for (unsigned int i=0; i<NO_OF_BANKS; i++)	
    {   	
	str << "MC [" << n << "] " << "Average Cmd Buffer Time for Bank " << i << " = " << avgCBufDelayPerBank[i] << endl;
    }
    str << endl;			

    for (unsigned int i=0; i<NO_OF_BANKS; i++)	
    {   	
	str << "MC [" << n << "] " << "Average Bus & Memory Delay for Bank " << i << " = " << avgBusMemDelayPerBank[i] << endl;
    }
    str << endl;			

/*    for (unsigned int i=0; i<NO_OF_BANKS; i++)	
    {   	
	str << "MC [" << n << "] " << "Average Throttling time for Bank " << i << " = " << avgThrottlePerBank[i] << endl;
    }
    str << endl;
*/
     for (unsigned int i=0; i<NO_OF_CHANNELS; i++)
    {
	for (unsigned int j=0; j<NO_OF_RANKS; j++)
    	{
	    for (unsigned int k=0; k<NO_OF_BANKS; k++)
    	    {
		str << "MC [" << n << "] " << "Average Occupancy for Channel " << i << ", " << " Rank " << j << ", " << " Bank " << ", " << k << " = " << rbufferOccupancyRatio[i][j][k] << endl;
	    }
	}
  }
    str << endl;			

    for (unsigned int i=0; i<NO_OF_CHANNELS; i++)
    {
	for (unsigned int j=0; j<NO_OF_RANKS; j++)
    	{
	    for (unsigned int k=0; k<NO_OF_BANKS; k++)
    	    {
		str << "MC [" << n << "] " << "Total Occupancy Cycles for Channel " << i << ", " 
                    << " Rank " << j << ", " << " Bank " << ", " << k << " = " << ((MC*)mc)->reqH->chan[i].rank[j].bank[k].bufferOccupancy << endl;
	    }
	}
    }
    str << endl;			

    for (unsigned int i=0; i<NO_OF_CHANNELS; i++)
    {
	for (unsigned int j=0; j<NO_OF_RANKS; j++)
    	{
	    for (unsigned int k=0; k<NO_OF_BANKS; k++)
    	    {
		str << "MC [" << n << "] " << "Buffer Full Cycles for Channel " << i << ", " 
                    << " Rank " << j << ", " << " Bank " << ", " << k << " = " << bufferFullCycles[i][j][k] << endl;
	    }
	}
    }
    str << endl;	
/*
    for (unsigned int i=0; i<NO_OF_CHANNELS; i++)
    {
	for (unsigned int j=0; j<NO_OF_RANKS; j++)
    	{
	    for (unsigned int k=0; k<NO_OF_BUFFERS; k++)
    	    {
		str << "MC [" << n << "] " << "Empty Cycles for Channel " << i << ", " << " Rank " << j << ", " << " Bank " << ", " << k << " = " << emptyCycles[i][j][k] << endl;
	    }
	}
    }
    str << endl;			
*/
    for (unsigned int i=0; i<NO_OF_CHANNELS; i++)
    {
	for (unsigned int j=0; j<NO_OF_RANKS; j++)
    	{
	    for (unsigned int k=0; k<NO_OF_BUFFERS; k++)
    	    {
		str << "MC [" << n << "] " << "DRAM Busy Time for Channel " << i << ", " << " Rank " << j << ", " << " Bank " << ", " << k << " = " << ((MC*)mc)->dram->dc[i].dramBankBusyCycles[j][k] << endl;
	    }
	}
    }
    str << endl;			

    for (unsigned int i=0; i<NO_OF_CHANNELS; i++)
    for (unsigned int i=0; i<NO_OF_CHANNELS; i++)
    {
        str  <<  "MC [" << n << "] " << "Bus Busy Cycles = " << ((MC*)mc)->bus->dataBus[i].busBusyTime << endl;
        str  <<  "MC [" << n << "] " << "Per Bus occupancy = " << (((MC*)mc)->bus->dataBus[i].busBusyTime+0.0)/Simulator::Now()*100 << endl;
        str  <<  "MC [" << n << "] " << "DRAM Busy Cycles = " << ((MC*)mc)->dram->dc[i].dramBusyCycles;
    }
    str << endl;
    str <<  "MC [" << n << "] " << "Total Cycles = " << Simulator::Now() << endl;

    return str.str();
}
