/*
 * =====================================================================================
 *
 *       Filename:  myFullyVirtualArbiter.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/27/2010 01:52:11 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mitchelle Rasquinha (), mitchelle.rasquinha@gatech.edu
 *        Company:  Georgia Institute of Technology
 *
 * =====================================================================================
 */

#ifndef  _myarbiter_h_INC
#define  _myarbiter_h_INC

#include	"../interfaces/genericComponentHeader.h"
#include	"../../data_types/impl/flit.h"
#include	<vector>

class VCA_unit
{
    public:
        VCA_unit();
        uint port;
        uint ch;
        uint inport;
        uint inch;
};

class MyArbiter
{
    public:
        MyArbiter ();                             /* constructor */
        ~MyArbiter();
        void resize(uint p, uint c);
        bool is_requested(uint inp, uint inch, uint p, uint c);
        void request(uint p, uint c, uint inp, uint inch);
        VCA_unit pick_winner( uint p, uint c);
        void clear_winner( uint p, uint c, uint ip, uint ic);
        bool is_empty();
        bool is_empty_for_ch(uint ch);
        uint no_requests_ch(uint ch);
        string toString() const;
        uint address;
        uint name;
        uint node_ip;

    protected:

    private:
        uint PORTS;
        uint CHANNELS;
        vector < vector<bool> > locked;
        vector < vector<bool> > done;
        vector < vector<bool> > requested;
        vector < bool> port_locked;
        vector < vector<VCA_unit> > requesting_inputs;
        vector < vector<VCA_unit> > last_winner;
        vector < vector<uint> > last_port_winner;
        vector < vector<uint> > last_ch_winner;


}; /* -----  end of class MyArbiter  ----- */

#endif   /* ----- #ifndef myarbiter_INC  ----- */
