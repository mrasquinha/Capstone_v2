/*
 * =====================================================================================
 *
 *       Filename:  mshr.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/12/2010 12:43:25 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SYED MINHAJ HASSAN
 *        Company:  Georgia Institute of Technology
 *
 * =====================================================================================
 */

#ifndef  mshr_h_INC
#define  mshr_h_INC

#include        <string>
#include        <sstream>
#include        <iostream>
#include 	<iomanip>
#include        <cstdlib>
#include 	<fstream>
#include        <map>
#include        "../kernel/component.h"
#include        "../kernel/simulator.h"
#include        "../data_types/impl/irisEvent.h"
#include        "../MemCtrl/request.h"

using namespace std;

/*  
 *  =====================================================================================
 *      Class:  MSHR_H
 *      Description:  
 *     
 *     
 *   =====================================================================================
 */
extern unsigned long long int max_sim_time;
class MSHR_H : public Component
{
    public:
        MSHR_H ();                             /*  constructor */
        ~ MSHR_H ();
	Time unsink;
	Time lastFinishTime;
	Time globalUnSink;
	bool done;
	vector <Request> mshr;
	vector <Request> writeQueue;
	ifstream trace_filename;
	char * filename;
	unsigned int id; 
	unsigned int lastScheduledIndex;
	Component* parent;
	Component* child;
	Addr_t GlobalAddrMap(Addr_t addr, UInt threadId);
        void process_event (IrisEvent* e);
	void DeleteInMSHR(Request* req);	
        void demap_addr(Addr_t oldAddress, Addr_t newAddress);
	bool waiting;
	Request waitingForMSHR;
	Request nextReq;
	Time lastFullTime;
        std::string toString();
                                                                            
    protected:
                                                                            
    private:
                                                                            
}; /*  -----  end of class MSHR_H  ----- */

#endif   /*  ----- #ifndef mshr_INC  ----- */
