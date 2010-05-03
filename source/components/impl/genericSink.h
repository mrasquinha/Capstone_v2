/*
 * =====================================================================================
 *
 *       Filename:  genericSink.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/21/2010 08:48:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mitchelle Rasquinha (), mitchelle.rasquinha@gatech.edu
 *        Company:  Georgia Institute of Technology
 *
 * =====================================================================================
 */
#ifndef  _genericsink_h_INC
#define  _genericsink_h_INC
#include	"../interfaces/processor.h"
#include	"../../data_types/impl/highLevelPacket.h"
#include	"genericEvents.h"
#include	"genericData.h"
#include	<deque>
#include	<fstream>

using namespace std;

/*
 * =====================================================================================
 *        Class:  GenericSink
 *  Description:  
 * =====================================================================================
 */
class GenericSink : public Processor
{
    public:
        GenericSink ();                             /* constructor */
        void setup();
        void process_event(IrisEvent* e);
        string toString() const;
        ofstream out_file;
        uint address;
        vector<bool> ready;

    protected:

    private:
        deque<HighLevelPacket*> out_packets;
        string out_filename;
        
        //Event handlers
        void handle_new_packet_event( IrisEvent* e);
        void handle_ready_event( IrisEvent* e);
        void handle_outpull_event( IrisEvent* e);

}; /* -----  end of class GenericSink  ----- */


#endif   /* ----- #ifndef -genericsink_h_INC  ----- */
