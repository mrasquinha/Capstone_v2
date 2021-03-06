/*
 * =====================================================================================
 *
 *       Filename:  routerfourstagevcs.h
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

#ifndef  _routerfourstagevcs_h_INC
#define  _routerfourstagevcs_h_INC

#include	"../interfaces/router.h"
#include	"genericBuffer.h"
#include	"genericAddressDecoder.h"
#include	"genericArbiter.h"
#include	"genericPortArbiter.h"
#include	"genericCrossbar.h"
#include	"genericEvents.h"
#include	"genericData.h"
#include	"genericLink.h"

/*
 * =====================================================================================
 *        Class:  RouterFourStageVcs
 *  Description:  
 * =====================================================================================
 */
class RouterFourStageVcs: public Router
{
    public:
        RouterFourStageVcs ();                             /* constructor */
        ~RouterFourStageVcs();
        void init();
        void set_no_ports( uint p);
        void set_no_vcs( uint v);
        void set_no_credits ( int c);
        void set_buffer_size( uint b);
        void process_event(IrisEvent* e);
        uint check_all_conditions();
        void set_no_nodes( uint nodes);
        void set_grid_x_location ( uint a, uint b, uint c);
        void set_grid_y_location ( uint a, uint b, uint c);
        string toString() const;
        string print_stats();

        /* These are the statistics variables */
        uint packets;
        uint flits;
        double total_packet_latency;

    protected:

    private:
        uint ports;
        uint vcs;
        int credits;
        uint buffer_size;

        vector <GenericOutputBuffer> in_buffers;
        vector <GenericArbiter> in_arbiters;
        vector <GenericPortArbiter> port_arbiters;
        vector <GenericAddressDecoder> decoders;
        GenericCrossbar xbar;

        bool ticking;
        void handle_link_arrival_event(IrisEvent* e);
        void handle_tick_event(IrisEvent* e);
        bool check_tick();

}; /* -----  end of class RouterFourStageVcs  ----- */

#endif   /* ----- #ifndef _routerfourstagevcs_h_INC  ----- */

