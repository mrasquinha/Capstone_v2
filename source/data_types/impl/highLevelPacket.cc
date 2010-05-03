/*
 * =====================================================================================
 *
 *       Filename:  HighLevelPacket.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/09/2010 08:22:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mitchelle Rasquinha (), mitchelle.rasquinha@gatech.edu
 *        Company:  Georgia Institute of Technology
 *
 * =====================================================================================
 */

#ifndef  _highlevelpacket_cc_INC
#define  _highlevelpacket_cc_INC

#include	"highLevelPacket.h"

/*
 *--------------------------------------------------------------------------------------
 *       Class:  HighLevelPacket
 *      Method:  HighLevelPacket
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
HighLevelPacket::HighLevelPacket ()
{
    source = -1;
    destination = -1;
    vn = VN0;
    mc = NCS;
    transaction_id = 0;
    virtual_channel = 0;
    data_payload_length = 0;
    sent_time = Simulator::Now();
    recv_time = 0;
}  /* -----  end of method HighLevelPacket::HighLevelPacket  (constructor)  ----- */

HighLevelPacket::~HighLevelPacket()
{
    data.clear();
}

string HighLevelPacket::toString() const
{
    stringstream str;
    str << " Creation time: " << sent_time 
        << " Source: " << source 
        << " Dest: " << destination 
        << " transaction_id: " << transaction_id
        << " VC: " << virtual_channel
        << "\t";
    return str.str();
}  /* -----  end of method HighLevelPacket::toString::HighLevelPacket::toString  (constructor)  ----- */

simTime HighLevelPacket::get_transit_time()
{
    return recv_time - sent_time;
}

bool HighLevelPacket::operator==( const HighLevelPacket* p )
{
    if( transaction_id == p->transaction_id &&
        source == p->source)
        return true;
    else
        return false;
}

/* This function instantiates a low level packet. One needs to explicitly
 * destroy it if used */
void
HighLevelPacket::to_low_level_packet(LowLevelPacket* pkt)
{
    pkt->source = source;
    pkt->destination = destination;
    pkt->transaction_id = transaction_id;
    pkt->sent_time = sent_time;
    pkt->length = ((this->data_payload_length+0.0)/max_phy_link_bits) + 2; // data_payload_length is the number of bits of data;
    pkt->virtual_channel = virtual_channel;

    HeadFlit *hf = new HeadFlit();

    /*  Create the mask based on message class and vc and virtual network */
    uint mask = (virtual_channel&0x03) | (( vn & 0x03)<<2) | ((mc & 0x0f)<<4);
    for ( uint i=0 ; i< pkt->control_bits.size() ;i++ )
    {
        pkt->control_bits[i] = ( mask >> i ) & 0x01;
        hf->control_bits[i] = ( mask >> i ) & 0x01;
    }

    hf->src_address = source;
    hf->dst_address = destination;
    hf->transaction_id = transaction_id;
    hf->length = pkt->length;
    hf->vc = virtual_channel;
    hf->populate_head_flit();
    pkt->flits.push_back(hf);

    vector< bool> temp;
    uint no_of_body_flits = this->data.size()/max_phy_link_bits;
    for ( uint i=0 ; i<no_of_body_flits ; i++ )
    {
        BodyFlit* bf = new BodyFlit();
        for ( uint j=0 ; j<max_phy_link_bits && (i*max_phy_link_bits + j)< data.size() ; j++ )
            temp.push_back(this->data[i*max_phy_link_bits + j]);

        bf->populate_body_flit(temp);
        pkt->flits.push_back(bf);
        temp.clear();
    }

    TailFlit* tf = new TailFlit();
    tf->packet_originated_time = pkt->sent_time;
    tf->populate_tail_flit();
    pkt->flits.push_back(tf);

    /* Compute the number of head flits required based on source addr dest
     * addr, transaction id and control bits and phit size */

    return ;
}

void
HighLevelPacket::from_low_level_packet ( LowLevelPacket* llp )
{
    source = llp->source;
    destination = llp->destination;
    transaction_id = llp->transaction_id;
    data_payload_length = llp->length;
    sent_time = llp->sent_time;
    virtual_channel = llp->virtual_channel;

    uint mask = 0;
    for (uint i=0; i<llp->control_bits.size(); i++)
        mask = (mask<<1) | llp->control_bits[i];

    /*  Need to check this mask propagation: The VC aint right */
    //virtual_channel = (mask & 0x00c0)>>6;
    switch ((mask & 0x0030) >> 4)
    {
        case 0:
            vn = VN0;
            break;
        case 1:
            vn = VN1;
            break;
        default:
            vn = VN2;
            break;
    }

    switch(mask&0x000f)
    {
        case 0:
            mc = HOM;
            break;
        case 1:
            mc = SNP;
            break;
        case 2:
            mc = DRS;
            break;
        case 3:
            mc = NCB;
            break;
        case 4:
            mc = NCS;
            break;
        default:
            mc = NCS;
            break;
    }

    for (uint i=1; i<llp->flits.size()-2; i++) /* this is assuming one head and one tail flit */
        for ( uint j=0 ; j< llp->flits[i]->phits.size() ; j++ )
            for ( uint k=0 ; k< llp->flits[i]->phits[j].data.size() ; k++ )
                data.push_back(llp->flits[i]->phits[j].data[k]);

    llp->flits.clear();
    return ;
}		/* -----  end of function HighLevelPacket::from_low_level_packet  ----- */

#endif   /* ----- #ifndef _highlevelpacket_cc_INC  ----- */

