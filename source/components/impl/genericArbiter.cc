/*
 * =====================================================================================
 *
 *       Filename:  genericVcArbiter.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/23/2010 01:15:21 PM
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

#include	"genericArbiter.h"


GenericArbiter::GenericArbiter ()
{
    name = "arbiter";
    address = -1;
    node_ip = -1;
    last_winner = 0;
    done = false;
}		/* -----  end of function GenericArbiter  ----- */

GenericArbiter::~GenericArbiter ()
{
}		/* -----  end of function GenericArbiter  ----- */

void
GenericArbiter::request (Flit* f, uint vc)
{
    requests[vc] = true;
    flits[vc] = f;
    return ;
}		/* -----  end of function GenericArbiter::request  ----- */

Flit*
GenericArbiter::pull_winner ()
{
    if ( !done )
        pick_winner();

    done = false;

    if ( !requests[ last_winner ])
    {
        _DBG("GenericArbiter:: Invalid flit exception last_winner %d", last_winner);
        exit(1);
    }

    requests[last_winner] =  false;
    return flits [last_winner];
}		/* -----  end of function GenericArbiter::pull_winner  ----- */

bool
GenericArbiter::is_requested( uint ch )
{
    /*  Check for exceptions here is ch greater than requests size */
    if( ch > requests.size())
    {
        _DBG(" Invalid VC Exception req_vc: %d ", ch);
        cout.flush();
        exit(1);
    }

    return requests[ch];
}		/* -----  end of function GenericArbiter::ready  ----- */

uint
GenericArbiter::get_no_requests ()
{
    return requests.size();
}		/* -----  end of function GenericArbiter::size  ----- */

void
GenericArbiter::set_req_queue_size ( uint size)
{
    requests.resize(size);
    flits.resize(size);
    next_port.resize(size);
    for ( uint i=0 ; i<size; i++ )
        requests[i] = false;

    return ;
}		/* -----  end of function GenericArbiter::resize  ----- */

uint
GenericArbiter::pick_winner ()
{
    if ( !done )
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
    {
        return last_winner;
    }
    _DBG("GenericArbiter:: pick_winner error... dint find a winner %d", last_winner);
    exit(1);

    return -1;

}		/* -----  end of function GenericArbiter::pick_winner  ----- */

uint
GenericArbiter::pick_winner( vector<bool> ready )
{
    if (ready.size() != requests.size())
    {
        _DBG("\nInvalidReadySizeException GenericArbiter::pick_winner ready_size: %d req_size:%d", ready.size(), requests.size());
        exit(1);
    }

    if(!done)
    {
        done = true;
        for( uint i=last_winner+1; i<requests.size(); i++)
            if(requests[i] && ready[i])
            {
                last_winner = i;
                return i;
            }

        for ( uint i=0; i<last_winner+1; i++)
            if( requests[i] && ready[i] )
            {
                last_winner = i;
                return i;
            }
    }
    else
    {
        return last_winner;
    }

    _DBG("GenericArbiter:: NOREQUESTSEXCEPTION %d ", last_winner);
    return -1;
}


void
GenericArbiter::clear_winner ()
{
//    if( requests[last_winner])
//        delete flits[last_winner];

    requests[last_winner] = false;
    return ;
}		/* -----  end of function GenericArbiter::clear_winner  ----- */


bool
GenericArbiter::empty ()
{
    bool ty = true;
    for ( uint i=0 ; i<requests.size() ; i++ )
        ty = ty & !requests[i];

    return ty;
}		/* -----  end of function GenericArbiter::empty  ----- */

bool
GenericArbiter::empty ( vector<bool> ready)
{
    if( ready.size() != requests.size() )
    {
        _DBG(" InvalidReadySizeExp empty(ready) %d ", requests.size());
        exit(1);
    }

    bool ty = true;
    for ( uint i=0; i<requests.size(); i++ )
    {
        ty = ty & !(requests[i] & ready[i]);
    }
    return ty;
}		/* -----  end of function GenericArbiter::empty  ----- */

string
GenericArbiter::toString () const
{
    stringstream str;
    str << "GenericArbiter: "
        << "\t last_winner: " << last_winner
        << "\t no of requests: " << requests.size();
    return str.str();
}		/* -----  end of function GenericArbiter::toString  ----- */

#endif   /* ----- #ifndef _genericvcarbiter_cc_INC  ----- */

