/*
 * =====================================================================================
 *
 *       Filename:  myrouter.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/11/2010 08:56:06 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mitchelle Rasquinha (), mitchelle.rasquinha@gatech.edu
 *        Company:  Georgia Institute of Technology
 *
 * =====================================================================================
 */

#ifndef  _myrouter_h_INC
#define  _myrouter_h_INC

#include	"../interfaces/router.h"
#include	"genericBuffer.h"
#include	"genericAddressDecoder.h"
#include	"genericVcArbiter.h"
#include	"myArbiter.h"
//#include	"pvtop_swa.h"
#include	"genericCrossbar.h"
#include	"genericEvents.h"
#include	"genericData.h"
#include	"genericLink.h"

enum MyRouterPipeStage { INVALID, EMPTY,IB, FULL, ROUTED, SWA_REQUESTED, SW_ALLOCATED, ST, REQ_OUTVC_ARB };

class MessageState
{
    public:
        MessageState();
        ~MessageState(){}
        uint input_port;
        uint input_channel;
        uint output_port;
        uint output_channel;
        double arrival_time;
        int length;
        int credits_sent;
        vector < uint > possible_ovcs;
        vector < uint > possible_oports;
        MyRouterPipeStage pipe_stage;
        bool clear_message;
        uint flits_in_ib;
        string toString () const;

};

class MyRouter: public Router
{
    public:
        MyRouter ();                             /* constructor */
        ~MyRouter();
        void init();
        void set_no_ports( uint p);
        void set_no_vcs( uint v);
        void set_no_credits ( int c);
        void set_buffer_size( uint b);

        void set_no_nodes( uint nodes);
        void set_grid_x_location ( uint a, uint b, uint c);
        void set_grid_y_location ( uint a, uint b, uint c);
        void send_credit_back( uint i);

        void process_event(IrisEvent* e);
        string toString() const;
        string print_stats();
        vector< vector<uint> > downstream_credits;

        /* These are the statistics variables */
        uint packets;
        uint flits;
        double total_packet_latency;
        double last_flit_out_cycle;

    protected:

    private:
        uint ports;
        uint vcs;
        int credits;
        uint buffer_size;

        vector <GenericOutputBuffer> in_buffers;
        vector <GenericAddressDecoder> decoders;
        vector <GenericVcArbiter> out_arbiters;
        vector <MessageState> mstate;
        MyArbiter swa;
        GenericCrossbar xbar;

        bool ticking;
        void handle_link_arrival_event(IrisEvent* e);
        void handle_tick_event(IrisEvent* e);

}; /* -----  end of class MyRouter  ----- */

#endif   /* ----- #ifndef _myrouter_h_INC  ----- */

