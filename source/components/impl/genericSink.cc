/*
 * =====================================================================================
 *
 *       Filename:  genericSink.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/21/2010 08:48:12 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mitchelle Rasquinha (), mitchelle.rasquinha@gatech.edu
 *        Company:  Georgia Institute of Technology
 *
 * =====================================================================================
 */

#ifndef  _genericsink_cc_INC
#define  _genericsink_cc_INC

#include	"genericSink.h"

/*
 *--------------------------------------------------------------------------------------
 *       Class:  GenericSink
 *      Method:  GenericSink
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
GenericSink::GenericSink ()
{
    out_filename = "trace_out.tr";
    name = "GenericSink";
    interface_connections.resize(1);
    out_file.open(out_filename.c_str());
}  /* -----  end of method GenericSink::GenericSink  (constructor)  ----- */

void
GenericSink::setup ()
{
    address = myId();
    ready.resize(1);
    /* Send ready events for each virtual channel */
    for ( uint i = 0; i < ready.size(); i++ )
    {
        IrisEvent* e = new IrisEvent();
        VirtualChannelDescription* vc = new VirtualChannelDescription();
        vc->vc = i;
        e->event_data.push_back(vc);
        e->type = READY_EVENT;
        Simulator::Schedule(Simulator::Now()+1, &Interface::process_event, interface_connections[0], e);
        ready[i] = false;
        
        cout	<< "GenericSink:: Sending ready event to interface" << endl;
    }
        return;
}		/* -----  end of function GenericSink  ----- */

void
GenericSink::process_event (IrisEvent* e)
{
    switch(e->type)
    {
        case NEW_PACKET_EVENT:
            handle_new_packet_event(e);
            break;
        case OUT_PULL_EVENT:
            handle_outpull_event(e);
            break;
        case READY_EVENT:
            handle_ready_event(e);
            break;
        default:
            cout << "Unk event type" <<endl;
            break;
    }

    return ;
}		/* -----  end of function GenericSink::process_event  ----- */

void
GenericSink::handle_new_packet_event ( IrisEvent* e )
{
    HighLevelPacket* hlp = static_cast<HighLevelPacket*>(e->event_data.at(0));
    cout << " GenericSink:: ********** GOT NEW PACKET ************" << endl;
    cout << hlp->toString()<< " Latency: " << Simulator::Now() - hlp->sent_time << endl;
    out_file << hlp->toString()<< " Latency: " << Simulator::Now() - hlp->sent_time << endl;
    /* Event handled now delete it */
    delete e;

    return ;
}		/* -----  end of function GenericSink::handle_new_packet_event  ----- */

void
GenericSink::handle_outpull_event ( IrisEvent* e )
{
    return ;
}		/* -----  end of function GenericSink::handle_outpull_event  ----- */

void
GenericSink::handle_ready_event ( IrisEvent* e )
{
    cout << " GenericSink:: got ready event at time " << Simulator::Now() << endl;
    return ;
}		/* -----  end of function GenericSink::handle_ready_event  ----- */

string
GenericSink::toString () const
{
    stringstream str;
    str << "GenericSink" 
        << "\t addr: " << address
        << "\toutput file = " << out_filename;
    return str.str();
}		/* -----  end of function GenericSink::toString  ----- */

#endif   /* ----- #ifndef _genericsink_cc_INC  ----- */

