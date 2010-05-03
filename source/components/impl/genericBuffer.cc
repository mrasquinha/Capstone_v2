/*
 * =====================================================================================
 *
 *       Filename:  genericOutputBuffer.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/21/2010 12:55:17 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mitchelle Rasquinha (), mitchelle.rasquinha@gatech.edu
 *        Company:  Georgia Institute of Technology
 *
 * =====================================================================================
 */
#ifndef  _genericoutputbuffer_cc_INC
#define  _genericoutputbuffer_cc_INC

#include	"genericBuffer.h"

GenericOutputBuffer::GenericOutputBuffer ()
{
    pull_channel = 0;
    push_channel = 0;
}		/* -----  end of function GenericOutputBuffer::GenericOutputBuffer  ----- */

GenericOutputBuffer::~GenericOutputBuffer ()
{
}

void
GenericOutputBuffer::push ( Flit* f )
{
    buffers[push_channel].push(f);
    return;
}		/* -----  end of function GenericOutputBuffer::push  ----- */

Flit*
GenericOutputBuffer::pull ()
{
    if( pull_channel > buffers.size() || buffers[pull_channel].size() == 0)
    {
        fprintf( stdout, "\nERROR: Invalid pull channel");
        exit(1);
    }
    Flit* f = buffers[pull_channel].front();
    buffers[pull_channel].pop();
    return f;
}		/* -----  end of function GenericOutputBuffer::pull  ----- */

uint
GenericOutputBuffer::get_occupancy ( uint ch ) const
{
    return buffers[ch].size();
}		/* -----  end of function GenericOutputBuffer::get_occupancy  ----- */

void
GenericOutputBuffer::set_no_vcs( uint v )
{
    /* 
    for ( uint i = vcs; i<buffers.size(); i++ )
        while( !buffers[i].empty())
        {
            delete buffers[i].front();
            buffers[i].pop();
        }
     * */
    vcs =v;
    buffers.resize(vcs);
    return;
}		/* -----  end of function GenericOutputBuffer::change_vcs  ----- */

uint
GenericOutputBuffer::get_no_vcs() const
{
    /*  should be return the pvt variable but for now using this to ensure
     *  init was right and not accessing member variable. */
    return buffers.size();
}

void
GenericOutputBuffer::change_pull_channel ( uint ch )
{
    pull_channel = ch;
    return;
}		/* -----  end of function GenericOutputBuffer::change_pull_channel  ----- */

void
GenericOutputBuffer::change_push_channel ( uint ch )
{
    push_channel = ch;
    return;
}		/* -----  end of function GenericOutputBuffer::change_pull_channel  ----- */


uint
GenericOutputBuffer::get_pull_channel () const
{
    return pull_channel;
}		/* -----  end of function GenericOutputBuffer::get_pull_channel  ----- */

uint
GenericOutputBuffer::get_push_channel () const
{
    return push_channel;
}		/* -----  end of function GenericOutputBuffer::get_push_channel  ----- */

bool
GenericOutputBuffer::is_channel_full ( uint ch ) const
{
    /* this is the buffer size that the router is configured for the implementation allow for a bigger buffer[i].size which is the simulation artifact and not the buffer size in the physical router */
    return buffers[ch].size() >= BUFFER_SIZE;  
}		/* -----  end of function GenericOutputBuffer::full  ----- */

bool
GenericOutputBuffer::is_empty (uint ch ) const
{
    return buffers[ch].empty();
}		/* -----  end of function GenericOutputBuffer::empty  ----- */

string
GenericOutputBuffer::toString () const
{
    stringstream str;
    str << "GenericBuffer"
        << "\t buffer_size: " << buffer_size
        << "\t No of buffers: " << buffers.size() << "\n";
    for( uint i=0; i<buffers.size() && !buffers[i].empty(); i++)
            str << buffers[i].front()->toString();
    return str.str();
}		/* -----  end of function GenericOutputBuffer::toString  ----- */

#endif   /* ----- #ifndef _genericoutputbuffer_cc_INC  ----- */

