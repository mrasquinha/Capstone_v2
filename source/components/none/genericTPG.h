
#ifndef  _generictpg_h_INC
#define  _generictpg_h_INC

#include        "genericInterface.h"
#include        "genericEvents.h"
#include        "genericData.h"
#include        "../interfaces/processor.h"
#include        "../../data_types/impl/highLevelPacket.h"
#include	"../../tests/MersenneTwister.h"
#include	"../../memctrl/request.h"
#include        <fstream>
#include        <deque>
#include        "mshr.h"

#define DEFAULT_RAN_MAX_TIME 100
#define MAX_ADDRESS 3
#define MAX(a,b) (((a)<(b))?(b):(a))
#define MIN(a,b) (((a)<(b))?(a):(b))

class GenericTPG : public Processor
{

    private:
        uint vcs;
        deque< HighLevelPacket > out_packets;
        deque< HighLevelPacket > sent_packets;
        string out_filename;
        string trace_name;
        ofstream out_file;
        fstream trace_filename;
        vector< bool > ready;
        unsigned int last_vc;
        bool sending;
        Request* GetNextRequest();
        void convertToBitStream(Request* req, HighLevelPacket* hlp);
        void handle_new_packet_event(IrisEvent* e);
        void handle_ready_event(IrisEvent* e);
        void handle_out_pull_event(IrisEvent* e);

    public :
        GenericTPG();
        ~GenericTPG();
        /* stats variables */
        unsigned int packets;
        MSHR_H *mshrHandler;
        unsigned long long int max_time;
        void setup();
        void finish();
        void process_event(IrisEvent* e);
        string toString() const;
        void set_trace_filename( string filename );
        void set_no_vcs ( uint v );
        bool compare();
        set< HighLevelPacket > get_all_sent();
        set< HighLevelPacket > get_all_recv();
        bool GetNewRequest(Request *req);
        Request* GetRequest();
};



#endif   /* ----- #ifndef _generictpg_h_INC  ----- */

