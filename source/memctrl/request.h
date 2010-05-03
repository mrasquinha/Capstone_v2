/*
 * =====================================================================================
 *
 *       Filename:  request.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/13/2010 02:13:15 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mitchelle Rasquinha (), mitchelle.rasquinha@gatech.edu
 *        Company:  Georgia Institute of Technology
 *
 * =====================================================================================
 */

#ifndef  request_h_INC
#define  request_h_INC

#include        <string>
#include        <sstream>
#include        <iostream>
#include        <cstdlib>
#include        <map>
#include        "../kernel/component.h"
#include        "../kernel/simulator.h"
#include	"constants.h"

using namespace std;

/*  
 *  =====================================================================================
 *      Class:  Request
 *      Description:  
 *     
 *     
 *   =====================================================================================
 */

enum CStatus {OPEN, CLOSED, CONFLICT, IDLE};
enum Command_t {CACHE_NOP, CACHE_READ, CACHE_WRITE, CACHE_WRITEBACK, CACHE_PREFETCH, REFRESH};

struct Data
{
    unsigned long long int value;
    short size;	
};
typedef Data Data;

class Request
{
    public:
        Request();
        ~ Request();
        UInt channelNo;
        UInt dimmNo;
        UInt rankNo;
        UInt bankNo;
        UInt columnNo;
        UInt rowNo;
        Command_t cmdType;
        UInt threadId; 
        Addr_t address;
        Time arrivalTime;
        Time retireTime;
	Data data;
        bool mark;
        bool local;
//	int indexWhenScheduled; 
	CStatus status;
	int tag;
        string toString() const;
	
                                                                            
    protected:
                                                                            
    private:

}; /* ----- end of class Request ------ */

#endif   /*  ----- #ifndef request_INC  ----- */
