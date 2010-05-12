
#ifndef  _generictpg_h_INC
#define  _generictpg_h_INC

#include        "genericInterface.h"
#include        "genericEvents.h"
#include        "genericData.h"
#include        "../interfaces/processor.h"
#include        "../../data_types/impl/highLevelPacket.h"
#include	"../../tests/MersenneTwister.h"
#include	"../../MemCtrl/request.h"
#include        <fstream>
#include        <deque>
#include        "../../MemCtrl/mshr.h"
#include	"../../MemCtrl/constants.h"

#define DEFAULT_RAN_MAX_TIME 100
#define MAX_ADDRESS 3
#define MAX(a,b) (((a)<(b))?(b):(a))
#define MIN(a,b) (((a)<(b))?(a):(b))

class GenericTPG : public Processor
{

    private:
        uint vcs;
        uint no_nodes;
        unsigned long long int max_sim_time;
        deque< HighLevelPacket > out_packets;
        deque< HighLevelPacket > sent_packets;
        string out_filename;
        string trace_name;
        ofstream out_file;
        ifstream *trace_filename;
        vector< bool > ready;
        unsigned int last_vc;
        bool sending;
        Request* GetNextRequest();
        bool GetNewRequest(Request *req);
        Request* GetRequest();
        void convertToBitStream(Request* req, HighLevelPacket* hlp);
	void convertFromBitStream(Request* req, HighLevelPacket *hlp);
        void handle_new_packet_event(IrisEvent* e);
        void handle_ready_event(IrisEvent* e);
        void handle_out_pull_event(IrisEvent* e);

    public :
        GenericTPG();
        ~GenericTPG();
        /* stats variables */
        unsigned int packets;
        double min_pkt_latency;

        MSHR_H *mshrHandler;
        unsigned long long int max_time;
        void setup(uint no_nodes, uint vcs, uint max_sim_time);
        void finish();
        void process_event(IrisEvent* e);
        string toString() const;
        string print_stats() const;
        void set_trace_filename( string filename );
        void set_no_vcs ( uint v );
        bool compare();
        set< HighLevelPacket > get_all_sent();
        set< HighLevelPacket > get_all_recv();
};



#endif   /* ----- #ifndef _generictpg_h_INC  ----- */

