
#ifndef  _generictpg_cc_INC
#define  _generictpg_cc_INC

#include "genericTPG.h"

GenericTPG::GenericTPG ()
{
    name = "GenericTPG";
    sending = false;
    /* Do this in setup with the address or node_ip appended */
    out_filename = "traceOut.tr";
    last_vc = 0;
    interface_connections.resize(1);
}		/* -----  end of function GenericTPG::GenericTPG  ----- */

GenericTPG::~GenericTPG ()
{
}		/* -----  end of function GenericTPG::~GenericTPG  ----- */

void
GenericTPG::set_trace_filename( string filename )
{
    trace_name = filename;
    cout<<"TraceName: "<<trace_name<<endl;
}

void
GenericTPG::set_no_vcs ( uint v)
{
    vcs = v;
}
void
GenericTPG::setup ()
{
    vcs =1;
    packets = 0;
    address = myId();
    
    ready.resize( vcs );
    ready.insert( ready.begin(), ready.size(), false );
    for(unsigned int i = 0; i < ready.size(); i++)
        ready[i] = false;
	
    trace_filename.open(trace_name.c_str(),ios::in);
    if(!trace_filename.is_open())
    {
        cout << "Err opening trace " << endl;
        exit(1);
    }


    /* send ready events for each virtual channel*/
    for( unsigned int i = 0; i < vcs; i++ )
    {
        VirtualChannelDescription* vc = new VirtualChannelDescription();
        vc->vc = i;

        IrisEvent* event = new IrisEvent();
        event->type = READY_EVENT;
        event->vc = i;
        event->event_data.push_back(vc);
        Simulator::Schedule(Simulator::Now()+1, &NetworkComponent::process_event,this, event);
//        interface_connections[0], event);
    }

    // open the output trace file
    stringstream str;
    str << "tpg_" << address << "_trace_out.tr";
    out_filename = str.str();
    out_file.open(out_filename.c_str());
    if( !out_file.is_open() )
    {
        stringstream stream;
        stream << "Could not open output trace file " << out_filename << ".\n";
        timed_cout(stream.str());
    }	
    return ;
}		/* -----  end of function GenericTPG::setup  ----- */

void
GenericTPG::finish ()
{
    out_file.close();
    trace_filename.close();
    return ;
}		/* -----  end of function GenericTPG::finish  ----- */

void
GenericTPG::process_event (IrisEvent* e)
{
    switch(e->type)
    {
        case NEW_PACKET_EVENT:
            handle_new_packet_event(e);
            break;
        case OUT_PULL_EVENT:
            handle_out_pull_event(e);
            break;
        case READY_EVENT:
            handle_ready_event(e);
            break;
        default:
            cout << "\nTPG: " << address << "process_event: UNK event type" << endl;
            break;
    }
    return ;
}		/* -----  end of function GenericTPG::process_event  ----- */

void
GenericTPG::handle_new_packet_event ( IrisEvent* e)
{
    // get the packet data
    HighLevelPacket* hlp = static_cast< HighLevelPacket* >( e->event_data.at(0));
    _DBG( "-------------- GOT NEW PACKET ---------------\n pkt_latency: %f", ( Simulator::Now() - hlp->sent_time));

    // write out the packet data to the output trace file
    if( !out_file.is_open() )	
        out_file.open( out_filename.c_str(), std::ios_base::app );		

    if( !out_file.is_open() )
    {
        cout << "Could not open output trace file " << out_filename << ".\n";
    }
        
        out_file << hlp->toString();
        out_file << "\tPkt latency: " << Simulator::Now() - hlp->sent_time << endl;

        delete hlp;
    // send back a ready event
    IrisEvent* event = new IrisEvent();
    event->type = READY_EVENT;
    VirtualChannelDescription* vc = new VirtualChannelDescription();
    vc->vc = hlp->virtual_channel;
    event->event_data.push_back(vc);
    Simulator::Schedule( Simulator::Now()+1, &NetworkComponent::process_event, interface_connections[0], event);

    delete e;
    return ;
}		/* -----  end of function GenericTPG::handle_new_packet_event  ----- */

Request*
GenericTPG::GetNextRequest()
{
    Addr_t addr =0;
    UInt thread_id = 0;
    Time time = 0;
    UInt cmd;

    if (trace_filename.eof())
       return NULL;

    else
    {

	Request* tempRequest = new Request();
    	trace_filename >> hex >> addr;
    	trace_filename>> thread_id;	
    	trace_filename>>dec>> time;
    	trace_filename>>dec>> cmd;
	
    	tempRequest->cmdType = (Command_t)cmd;
    	tempRequest->address = addr;
    	tempRequest->arrivalTime = time;
    	tempRequest->threadId = thread_id;
	
#ifdef _DEEP_DEBUG
        cout << "\n Created Req: "
            << "\t cmd: " << cmd
            << "\t thr_id: " << thread_id
            << "\t time: " << time
            << "\t addr: " << addr
            << endl;
#endif

	return tempRequest;
    }
    
} 

bool
GenericTPG::GetNewRequest(Request *req)
{
    if (!mshrHandler->writeQueue.empty())
    {   
        if (mshrHandler->writeQueue[0].arrivalTime <= Simulator::Now())
        {
            vector<Request>::iterator bufferIndex = mshrHandler->writeQueue.begin();
            *req = mshrHandler->writeQueue[0];
            mshrHandler->writeQueue.erase(bufferIndex);
            return true;
        }
    }
    else if (!mshrHandler->mshr.empty() && mshrHandler->lastScheduledIndex <= mshrHandler->mshr.size())
    {   
        if (mshrHandler->mshr[mshrHandler->lastScheduledIndex].arrivalTime <= Simulator::Now())
        {         
            *req = mshrHandler->mshr[mshrHandler->lastScheduledIndex];
            mshrHandler->lastScheduledIndex++;
            return true;
        }
    }
    return false;
}

Request*
GenericTPG::GetRequest()
{
    Request *req = new Request();
    if (GetNewRequest(req))          
    {
        return req;    
    }
    return NULL;
}

void
GenericTPG::convertToBitStream(Request* req, HighLevelPacket* hlp)
{
    for ( uint i=0 ; i < NETWORK_ADDRESS_BITS ; i++ )
    {
	bool bit = (bool)((req->address >> i) & 0x1); 
        hlp->data.push_back(bit);
    }
    for ( uint i=0 ; i < NETWORK_COMMAND_BITS ; i++ )
    {
	bool bit = (bool)((req->cmdType >> i) & 0x1); 
        hlp->data.push_back(bit);
    }
    for ( uint i=0 ; i < NETWORK_THREADID_BITS ; i++ )
    {
	bool bit = (bool)((req->cmdType >> i) & 0x1); 
        hlp->data.push_back(bit);
    }
    if (req->cmdType == CACHE_WRITEBACK)
	for ( uint i=0 ; i < 8*WRITEBACK_SIZE ; i++ )
	{
	    bool bit = true;	// sending 1's as data 
            hlp->data.push_back(bit);
        }
	        
    hlp->data_payload_length = ceil(hlp->data.size() *1.0 / max_phy_link_bits);
    hlp->data_payload_length = hlp->data_payload_length * max_phy_link_bits;

    for ( uint i=0 ; i < hlp->data_payload_length - hlp->data.size(); i++ )
    {
	bool bit = false; 
        hlp->data.push_back(bit);
    } 
}
void
GenericTPG::handle_out_pull_event ( IrisEvent* e )
{
    bool found = false;
    for( unsigned int i = last_vc ; i < ready.size(); i++ )
        if( ready[i] )
        {
            found = true;
            last_vc= i;
            break;
        }
	
    if(!found )
        for( unsigned int i = 0; i < last_vc ; i++ )
            if( ready[i] )
            {
                found = true;
                last_vc = i;
                break;
            }
		
    Request* next_req = GetNextRequest();
    MTRand mtrand1;
    if( found  && next_req)
    {
        packets++;
        unsigned int current_packet_time = 0;
        HighLevelPacket* hlp = new HighLevelPacket();
        hlp->virtual_channel = last_vc;
        last_vc++;
        hlp->source = address;
        hlp->destination = mtrand1.randInt(MAX_ADDRESS); //MIN( generator.address(), MAX_ADDRESS);
        hlp->transaction_id = mtrand1.randInt(1000);
//        if( hlp->destination == node_ip )
//            hlp->destination = (hlp->destination + 1) % (MAX_ADDRESS + 1);
        if ( node_ip == 0)
            hlp->destination = 1;
        else
            hlp->destination = 0;

	convertToBitStream(next_req, hlp);      
        hlp->sent_time = Simulator::Now() ; //MAX(generator.delay() , 1);

        _DBG( " Sending pkt: no of packets %d ", packets );
        /* 
        out_file << "Sending packet: " << next_req->toString() << endl;
        out_file << "HLP: " << hlp->toString() << endl;
         * */
//        delete next_req;

        ready[ hlp->virtual_channel ] = false;
        IrisEvent* event = new IrisEvent();
        event->type = NEW_PACKET_EVENT;
        event->event_data.push_back(hlp);
        current_packet_time = hlp->sent_time; /* Making a copy so we dont depend on hlp deletionMaking a copy so we dont depend on hlp deletion. May be needed later if the functions are broken. */
        Simulator::Schedule( hlp->sent_time, &NetworkComponent::process_event, interface_connections[0], event );
                
        /*  Check for an empty vc and call yourself as long as it is not the
         *  MAX_SIM_TIME or last packet. If you were to do Run() till all
         *  events in the system are complete. This will probably determine
         *  the end of the simulation */
        found = false;
        for( unsigned int i = 0; i < ready.size(); i++ )
            if( ready[i] && current_packet_time < MAX_SIM_TIME ) 
            {
                found = true;
                break;
            }
    
            if( found )
            {
                IrisEvent* event = new IrisEvent();
                event->type = OUT_PULL_EVENT;
                event->vc = e->vc;
                Simulator::Schedule( Simulator::Now()+1, &NetworkComponent::process_event, this, event);
                sending = true;
            }
            else
                sending = false;
            
        }
        else
            sending = false;

//    delete e;
    return ;
}		/* -----  end of function GenericTPG::handle_out_pull_event  ----- */

void
GenericTPG::handle_ready_event ( IrisEvent* e)
{

    // send the next packet if it is less than the current time
    VirtualChannelDescription* vc = static_cast<VirtualChannelDescription*>(e->event_data.at(0));
    ready[vc->vc] = true;
#ifdef _DEBUG_TPG
    _DBG_NOARG(" handle_ready_event ");
#endif

    if( !sending && Simulator::Now() < MAX_SIM_TIME )
    {
        IrisEvent* event = new IrisEvent();
        event->type = OUT_PULL_EVENT;
        event->vc = e->vc;
        /* Need to be careful with the same cycles scheduling. Can result in
         * events of the past. Need to test this. */
        Simulator::Schedule(Simulator::Now()+1, &NetworkComponent::process_event, this, event); 
        sending = true;
    }

//    delete e;
    return ;
}		/* -----  end of function GenericTPG::handle_ready_event  ----- */

string
GenericTPG::toString () const
{
    stringstream str;
    str << "GenericTPG: "
        << "\t trace: " << trace_filename
        << "\t vcs: " << ready.size()
        << "\t address: " <<address
        << "\t node_ip: " << node_ip
        ;
    return str.str();
}		/* -----  end of function GenericTPG::toString  ----- */

#endif   /* ----- #ifndef _generictpg_cc_INC  ----- */

