/*
 * =====================================================================================
 *
 *       Filename:  genericVcArbiter.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/02/2010 01:41:41 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mitchelle Rasquinha (), mitchelle.rasquinha@gatech.edu
 *        Company:  Georgia Institute of Technology
 *
 * =====================================================================================
 */
#ifndef  _genericvcarbiter_cc_INC
#define  _genericvcarbiter_cc_INC

#include	"genericVcArbiter.h"

GenericVcArbiter::GenericVcArbiter()
{

}

GenericVcArbiter::~GenericVcArbiter()
{

}

void
GenericVcArbiter::set_no_vcs(uint ch)
{
    vcs = ch;
    requests.resize(ch);
    for ( uint i=0 ; i<ch ; i++ )
        requests[i] = false;
}

void
GenericVcArbiter::request( uint ch)
{
    requests[ch] = true;
    done = false;
    return;
}

bool
GenericVcArbiter::is_requested( uint ch)
{
    assert(ch<requests.size());
    return requests[ch];
}

uint
GenericVcArbiter::get_no_requests()
{
    uint no =0;
    for ( uint i=0; i<vcs; i++)
        if ( requests[i] )
            no++;

    return no;
}

void
GenericVcArbiter::clear_winner()
{
    done = false;
    requests[last_winner] = false;
    return;
}

uint
GenericVcArbiter::pick_winner()
{
    if(!done)
    {
        done = true;
        for ( uint i=last_winner+1 ; i<requests.size() ; i++ )
            if ( requests[i] )
            {
                last_winner = i;
                return i;
            }

        for ( uint i=0 ; i<last_winner+1 ; i++ )
            if ( requests[i])
            {
                last_winner = i;
                return i;
            }
    }
    else
        return last_winner;

    printf("Was requested to pick winner but dint find a winner " );

    return -1;
}

string
GenericVcArbiter::toString () const
{
    stringstream str;
    str << "GenericVcArbiter: "
        << "\t last_winner: " << last_winner
        << "\t no of requests: " << requests.size();
    return str.str();
}	

#endif   /* ----- #ifndef _genericvcarbiter_cc_INC  ----- */

