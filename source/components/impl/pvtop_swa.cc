/*
 * =====================================================================================
 *
 *       Filename:  myFullyVirtualArbiter.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/27/2010 12:58:11 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mitchelle Rasquinha (), mitchelle.rasquinha@gatech.edu
 *        Company:  Georgia Institute of Technology
 *
 * =====================================================================================
 */

#ifndef  _myarbiter_cc_INC
#define  _myarbiter_cc_INC

#include	"pvtop_swa.h"

PVToPArbiter::PVToPArbiter()
{

}

PVToPArbiter::~PVToPArbiter()
{

}

void
PVToPArbiter::resize(uint port, uint ch)
{
    PORTS = port;
    CHANNELS = ch;
    requested.resize(PORTS);
    locked.resize(PORTS);
    done.resize(PORTS);
    last_port_winner.resize(PORTS);
    last_ch_winner.resize(PORTS);
    requesting_inputs.resize(PORTS);
    last_winner.resize(PORTS);
    port_locked.resize(PORTS);

    for ( uint i=0; i<PORTS; i++)
    {
        requested[i].resize(PORTS*CHANNELS);
        requesting_inputs[i].resize(PORTS*CHANNELS);
    }

//    for ( uint i=0; i<PORTS; i++)
//    {
//        done[i].resize(CHANNELS);
//        locked[i].resize(CHANNELS);
//        last_port_winner[i].resize(CHANNELS);
//        last_ch_winner[i].resize(CHANNELS);
//        last_winner[i].resize(CHANNELS);
//        port_locked[i] = false;
//    }

    for ( uint i=0; i<PORTS; i++)
        for ( uint j=0; j<PORTS*CHANNELS; j++)
        {
            requested[i][j]=false;
        }

    for ( uint i=0; i<PORTS; i++)
//        for ( uint j=0; j<CHANNELS; j++)
        {
            locked[i] = false;
            done[i] = false;
            last_port_winner[i] = 0;
            last_ch_winner[i] = 0;
        }
}

bool
PVToPArbiter::is_requested( uint oport, uint och, uint inport )
{
    return requested[oport][inport*CHANNELS+och];
}

void
PVToPArbiter::request(uint oport, uint och, uint inport )
{
    requested[oport][inport*CHANNELS+och] = true;
    done[oport] = false;
    requesting_inputs[oport][CHANNELS*inport+och].inport = inport;
    requesting_inputs[oport][CHANNELS*inport+och].inch = och;

    return;
}

VCA_unit::VCA_unit()
{
    port = -1;
    ch = -1;
    inport = -1;
    inch = -1;
}

VCA_unit
PVToPArbiter::pick_winner( uint oport)
{
    if(!done[oport]) 
    {
        done[oport] = true;
        if(locked[oport] ) //|| port_locked[oport])
            return last_winner[oport];

        else
        {
            locked[oport]= true;

                /* Now look at contesting input ports on this channel and pick
                 * a winner*/
                bool winner_found = false;
                for( uint i=last_port_winner[oport]+1; i<(PORTS*CHANNELS); i++)
                    if(requested[oport][i])
                    {
                        last_port_winner[oport] = i;
                        winner_found = true;
                        last_winner[oport].inport = requesting_inputs[oport][i].inport;
                        last_winner[oport].inch = requesting_inputs[oport][i].inch;
//                        port_locked[oport] = true;
                        return last_winner[oport];
                    }

                if(!winner_found)
                for( uint i=0; i<=last_port_winner[oport]; i++)
                {
                    if(requested[oport][i])
                    {
                        last_port_winner[oport] = i;
                        winner_found = true;
                        last_winner[oport].inport = requesting_inputs[oport][i].inport;
                        last_winner[oport].inch = requesting_inputs[oport][i].inch;
//                        port_locked[oport] = true;
                        return last_winner[oport];
                    }
                }
                if(!winner_found)
                {
                    printf("ERROR: Cant find port winner" );
                    exit(1);
                }

            }
    }

    return last_winner[oport];
}

void
PVToPArbiter::clear_winner( uint oport, uint och, uint inport)
{
    done[oport]= false;
    locked[oport] = false;

    requested[oport][inport*CHANNELS+och] = false;
    return;
}

bool
PVToPArbiter::is_empty()
{

    for( uint i=0; i<PORTS; i++)
        for( uint j=0; j<CHANNELS*PORTS; j++)
            if(requested[i][j] )
            {
                return false;
            }
    return true;
    
}

bool
PVToPArbiter::is_empty_for_ch( uint ch)
{
    for( uint i=0; i<requested[ch].size(); i++)
        if(requested[ch][i] )
            return true;
   return false; 
}

uint
PVToPArbiter::no_requests_ch( uint ch)
{
    uint count = 0;
    for( uint i=0; i<requested[ch].size(); i++)
        if(requested[ch][i] )
        {
            count++;
        }
   return count; 
}

string
PVToPArbiter::toString() const
{
    stringstream str;
    str << "PVToPArbiter: "
        << "\t requested_qu row_size: " << requested.size();
    if( requested.size())
       str << " col_size: " << requested[0].size()
        ;
    return str.str();
}
#endif   /* ----- #ifndef _myarbiter_cc_INC  ----- */
