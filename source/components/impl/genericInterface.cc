/*
 * =====================================================================================
 *
 *       Filename:  genericInterface.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/21/2010 03:46:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mitchelle Rasquinha (), mitchelle.rasquinha@gatech.edu
 *        Company:  Georgia Institute of Technology
 *
 * =====================================================================================
 */

#ifndef  _genericinterface_cc_INC
#define  _genericinterface_cc_INC

#include	"genericInterface.h"
using namespace std;

GenericInterface::GenericInterface ()
{
    name = "Interface";
    ticking =false;
}		/* -----  end of function GenericInterface::GenericInterface  ----- */

GenericInterface::~GenericInterface ()
{
    
}		/* -----  end of function GenericInterface::~GenericInterface  ----- */

void
GenericInterface::setup ()
{
    vcs =1;
    credits = 1;
    /* All this is part of the init */
    address = myId();
//    convert_packet_cycles = DEFAULT_CONVERT_PACKET_CYCLES;

    in_buffer.resize(vcs, buffer_size);
    out_buffer.resize(vcs, buffer_size);
    downstream_credits.resize(vcs);

    out_packet_flit_index.resize(vcs);
    in_ready.resize(vcs);
    in_packets_flit_index.resize(vcs);

    in_arbiter.address = address;
    out_arbiter.address = address;
    in_arbiter.node_ip = node_ip;
    out_arbiter.node_ip = node_ip;
    out_arbiter.set_req_queue_size(vcs);
    in_arbiter.set_req_queue_size(vcs);

    in_packets.resize(vcs);
    in_packets_valid.resize(vcs);
    out_packets.resize(vcs);


    for ( uint i=0; i<vcs ; i++ )
    {
        out_packet_flit_index[i] = 0;
        in_ready[i] = true;
        in_packets[i].destination = address;
        in_packets[i].virtual_channel = i;
        downstream_credits[i] = credits;
    }

    /*  init stats */
    packets_out = 0;
    flits_out = 0;
    packets_in = 0;
    flits_in = 0;
    total_packets_in_time = 0;
    /* Init complete */

    /* Send a ready event for each vc 
    for ( uint i=0 ; i<vcs ; i++ )
    {
        IrisEvent* event = new IrisEvent();
        in_packets[i].virtual_channel = i;
        VirtualChannelDescription* vc = new VirtualChannelDescription();
        vc->vc = i;
        event->event_data.push_back(vc);
        event->type = READY_EVENT;
        event->vc = i;
        Simulator::Schedule(Simulator::Now(),&NetworkComponent::process_event, processor_connection, event); 
    }
    */

    return;
}		/* -----  end of function GenericInterface::setup  ----- */

void
GenericInterface::set_no_vcs( uint v )
{
    vcs = v;
}

void
GenericInterface::set_buffer_size( uint b )
{
    buffer_size = b;
}

/* We care about credits on the interface only for the output buffers ie on
 * the output side maintain credit info for the downstream buffers */
uint
GenericInterface::get_no_credits () const
{
    return credits;
}		/* -----  end of function GenericInterface::get_no_credits  ----- */

void
GenericInterface::set_no_credits ( int c)
{
    credits = c;
    return;
}		/* -----  end of function GenericInterface::set_no_credits  ----- */

string
GenericInterface::toString () const
{
    stringstream str;
    str << "GenericInterface: "
        << "\t VC: " << out_packets.size()
        << "\t address: " << address << " node_ip: " << node_ip
        << "\t OutputBuffers: " << out_buffer.toString()
        << "\t InputBuffer: " << in_buffer.toString()
        << "\t out_arbiter: " << out_arbiter.toString()
        << "\t in_arbiter: " << in_arbiter.toString()
        ;
    return str.str();
}		/* -----  end of function GenericInterface::toString  ----- */

void
GenericInterface::process_event(IrisEvent* e)
{
    switch(e->type)
    {
        case READY_EVENT:
            handle_ready_event(e);
            break;

        case LINK_ARRIVAL_EVENT:
            handle_link_arrival(e);
            break;

        case NEW_PACKET_EVENT:
            handle_new_packet_event(e);
            break;

        case TICK_EVENT:
            handle_tick_event(e);
            break;
            
        default:
            cout << "**Unkown event exception! " << e->type << endl;
            break;
    }
}		/* -----  end of function GenericInterface::process_event ----- */

void
GenericInterface::handle_ready_event( IrisEvent* e)
{
    /*! \brief  These are credits from the processor and hence do not update flow
     *  control state. Flow control state is updated at the link arrival event
     *  for a credit. */

    VirtualChannelDescription* vc = static_cast<VirtualChannelDescription*>(e->event_data.at(0));
#ifdef _DEBUG_INTERFACE
    _DBG(" handle_ready_event %d ", vc->vc);
#endif

    in_ready[vc->vc] = true;
    if(!ticking)
    { 
        ticking = true;
        IrisEvent* event = new IrisEvent();
        event->type = TICK_EVENT;
        event->vc = e->vc;
        Simulator::Schedule( floor(Simulator::Now())+1, &NetworkComponent::process_event, this, event);
    }

//        delete vc;
    delete e;
    return;
}		/* -----  end of function GenericInterface::handle_ready_event  ----- */

void
GenericInterface::handle_link_arrival ( IrisEvent* e)
{
    //Find out if it was a flit or a credit
    LinkArrivalData* uptr = static_cast<LinkArrivalData* >(e->event_data.at(0));
    uint next_tick_time = -1;

#ifdef _DEBUG_INTERFACE
    _DBG(" handle_link_arrival %d ", uptr->type);
#endif

    if(uptr->type == FLIT_ID)
    {
        flits_in++;
        in_buffer.change_push_channel(uptr->vc);
        in_buffer.push(uptr->ptr);
        if( uptr->ptr->type == TAIL )
        {
            packets_in++;
            total_packets_in_time += (Simulator::Now() - static_cast<TailFlit*>(uptr->ptr)->packet_originated_time);
        }
        uptr->valid = false;

            //Send a credit back since you cleared the in_buffer
            LinkArrivalData* arrival = new LinkArrivalData();
            VirtualChannelDescription* cr = new VirtualChannelDescription();
            cr->vc = uptr->vc;

            arrival->vc = uptr->vc;
            arrival->type = CREDIT_ID;
            

            IrisEvent* event = new IrisEvent();
            event->type = LINK_ARRIVAL_EVENT;
            event->vc = uptr->vc;
            event->event_data.push_back(arrival);
            event->src_id = address;
            Simulator::Schedule( ceil(Simulator::Now())+1, 
                                 &NetworkComponent::process_event, input_connection, event);
    }
    else if ( uptr->type == CREDIT_ID)
    {
        downstream_credits[uptr->vc]++;
#ifdef _DEBUG_INTERFACE
        _DBG(" got a credit vc: %d ftype: %d no_of_credits: %d ", uptr->vc, uptr->type, downstream_credits[uptr->vc] );
#endif
        delete uptr;
    }
    else
    {
        cout << "Exception: Unk link arrival data type! " << endl;
    }

    if(!ticking)
    {
        ticking = true;
        IrisEvent* new_event = new IrisEvent();
        new_event->type = TICK_EVENT;
        new_event->vc = e->vc;
        Simulator::Schedule( ceil(Simulator::Now())+1, &GenericInterface::process_event, this, new_event);
    }
    delete e;
    return;
}		/* -----  end of function GenericInterface::handle_link_arrival  ----- */

void
GenericInterface::handle_new_packet_event(IrisEvent* e)
{
    HighLevelPacket* pkt = static_cast<HighLevelPacket*>(e->event_data.at(0));
    LowLevelPacket* llp = new LowLevelPacket();
    pkt->to_low_level_packet(llp);
    out_packets[pkt->virtual_channel] = *llp;
    out_packets[pkt->virtual_channel].flits.clear();
    for ( uint i=0; i<llp->flits.size(); i++)
        out_packets[pkt->virtual_channel].flits.push_back(llp->flits[i]);
    delete llp;

    out_packet_flit_index[ pkt->virtual_channel ] = 0;

#ifdef _DEBUG_INTERFACE
    _DBG("handle_new_packet_event vc: %d ", static_cast<unsigned int >(pkt->virtual_channel) );
#endif

    if( !ticking)
    {
        ticking = true;
        IrisEvent* event = new IrisEvent();
        event->type = TICK_EVENT;
        event->vc = e->vc;
        Simulator::Schedule(floor(Simulator::Now())+1, &NetworkComponent::process_event, this, event);
    }

    delete e;
    return;
}		/* -----  end of function GenericInterface::handle_new_packet_event  ----- */

void
GenericInterface::handle_tick_event(IrisEvent* e)
{
    ticking = false;
    /*---------- This is on the output side. From processor out to network --------- */
    //Request to arbitrate for flits in out_buffer
    for ( uint i=0; i<out_packets.size(); i++ )
        if( !out_buffer.is_empty(i) 
            && !out_arbiter.is_requested(i) && downstream_credits[i]>0 )
        {
       out_buffer.change_pull_channel(i);
       Flit* f= out_buffer.pull();
            out_arbiter.request(f,i);
            ticking = true;

#ifdef _DEBUG_INTERFACE
    _DBG("Req out_arb vc:%d ",i);
#endif
        }

    // out out_arbiter to next link
    if(!out_arbiter.empty() )
    {
        uint winner = out_arbiter.pick_winner();
        if( downstream_credits[winner]>0)
    {
       IrisEvent* event = new IrisEvent();
       LinkArrivalData* arrival =  new LinkArrivalData();
       arrival->type = FLIT_ID;
       arrival->vc = winner;
       Flit* f = out_arbiter.pull_winner();
       downstream_credits[arrival->vc]--; 

       if( f->type == TAIL )
           packets_out++;
       flits_out++;

       arrival->ptr = f;

       event->event_data.push_back(arrival);
       event->type = LINK_ARRIVAL_EVENT;
       event->src_id = address;
       event->vc = arrival->vc;

       ticking = true;

       Simulator::Schedule(Simulator::Now()+1, &NetworkComponent::process_event, output_connection, event);
#ifdef _DEBUG_INTERFACE
    _DBG(" FLIT_OUT_EVENT Type: vc: %d fty:%d", arrival->vc, arrival->ptr->type);
#endif
    }
    }

    //out packet to out buffer
    for ( uint i=0; i<out_packets.size(); i++ )
        if ( out_packets[i].size() > 0 && out_packet_flit_index[i] < out_packets[i].length && !out_buffer.is_channel_full(i))
        {
            out_buffer.change_push_channel(i);
            Flit* ptr = out_packets[i].get_next_flit();
            out_buffer.push( ptr);
            out_packet_flit_index[i]++;

#ifdef _DEBUG_INTERFACE
    _DBG("Flit->OutBuffer vc:%d ftype:%d outpkt_len:%d index:%d",i, ptr->type, out_packets[i].length, out_packet_flit_index[i]);
#endif

            if(out_packet_flit_index[i] == out_packets[i].length )
            {
                out_packet_flit_index[i] = 0;
                out_packets[i].clear();

                if( out_packets[i].size()<1)
                {

                IrisEvent* event = new IrisEvent();
                event->type = READY_EVENT;
                VirtualChannelDescription* vcd = new VirtualChannelDescription();
                vcd->vc = i;
                event->event_data.push_back(vcd);
                event->vc = i;
                Simulator::Schedule(floor(Simulator::Now())+1, &NetworkComponent::process_event, processor_connection, event);
                }

            }
            ticking = true;
        }


    /*---------- This is on the output side. From processor out to ntwk --------- */
    // in packets to processor
    for ( uint i=0; i<in_packets.size(); i++ )
        if ( in_ready[i]  && in_packets_flit_index[i]!=0 && in_packets_flit_index[i] == in_packets[i].length)
        {
            in_ready[i] = false;

            _DBG_NOARG( "Interface got a complete llp: " );
            cout << in_packets[i].toString();
            HighLevelPacket* pkt = new HighLevelPacket();
            pkt->from_low_level_packet(&in_packets[i]);

            in_packets[i].clear();
            in_packets_flit_index[i] = 0;
            ticking = true;

            IrisEvent* event = new IrisEvent();
            event->type = NEW_PACKET_EVENT;
            event->event_data.push_back(pkt);
            event->vc = i;
            Simulator::Schedule(floor(Simulator::Now())+ 1, 
                                &NetworkComponent::process_event, processor_connection, event);

#ifdef _DEBUG_INTERFACE
    _DBG("Packet to Processor vc: %d", i);
#endif
             
        }

    // arbitrate for the winner and push packets to in_buffer
    for ( uint i=0; i<in_packets.size(); i++ )
        if( !in_arbiter.empty()) 
        {
        uint winner = in_arbiter.pick_winner();
            if( winner == i )
                if( in_packets[i].size() == 0 || in_packets_flit_index[i] < in_packets[i].length)
                {
                    Flit* ptr = in_arbiter.pull_winner();
                    in_packets[i].add(ptr);

                    in_packets_flit_index[i]++;
                    ticking = true;
#ifdef _DEBUG_INTERFACE
_DBG("InArbitrate vc:%d ftype:%d", i, ptr->type);
#endif
                    if( ptr->type == HEAD && static_cast<HeadFlit*>(ptr)->dst_address != node_ip)
                    {
                        _DBG("ERROR IncorrectDestinationException pkt_dest: %d node_ip: %d", in_packets[i].destination, node_ip); 
                    }

                }
        }

    // Request arbitration for in buffer
    for ( uint i=0; i<in_packets.size(); i++ )
        if ( !in_arbiter.is_requested(i) && !in_buffer.is_empty(i) )
        {

            in_buffer.change_pull_channel(i);
            Flit* ptr = in_buffer.pull();
            in_arbiter.request( ptr, i);
            ticking = true;
#ifdef _DEBUG_INTERFACE
_DBG("handle_in_arbitration vc:%d ftype:%d", i, ptr->type);
#endif

        }
                    

    if(ticking)
    {
        ticking = true;
        IrisEvent* new_event = new IrisEvent();
        new_event->type = TICK_EVENT;
        new_event->vc = e->vc;
        Simulator::Schedule( floor(Simulator::Now())+1, &GenericInterface::process_event, this, new_event);
    }

}


string
GenericInterface::print_stats()
{
    stringstream str;
    str << "\n interface[" << node_ip <<"] flits_in: " << flits_in
        << "\n interface[" << node_ip <<"] packets_in: " << packets_in
        << "\n interface[" << node_ip <<"] flits_out: " << flits_out
        << "\n interface[" << node_ip <<"] packets_out: " << packets_out
        << "\n interface[" << node_ip <<"] total_packet_latency(In packets): " << total_packets_in_time;
    if(packets_in != 0)
    str << "\n interface[" << node_ip <<"] avg_packet_latency(In packets): " << (total_packets_in_time+0.0)/packets_in
        ;
    return str.str();

}

#endif   /* ----- #ifndef _genericinterface_cc_INC  ----- */

