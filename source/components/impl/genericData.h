/*
 * =====================================================================================
 *
 *       Filename:  genericData.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/21/2010 04:59:48 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mitchelle Rasquinha (), mitchelle.rasquinha@gatech.edu
 *        Company:  Georgia Institute of Technology
 *
 * =====================================================================================
 */
#ifndef  _genericdata_h_INC
#define  _genericdata_h_INC

#include	"../../data_types/impl/flit.h"

using namespace std;

/*
 * =====================================================================================
 *        Class:  LinkArrivalData
 *  Description:  
 * =====================================================================================
 */
class LinkArrivalData
{
    public:
        LinkArrivalData ();                             /* constructor */
        ~LinkArrivalData ();                             /* constructor */
        uint type;
        uint vc;
        Flit* ptr;
        bool valid;

    protected:

    private:

}; /* -----  end of class LinkArrivalData  ----- */

/*
 * =====================================================================================
 *        Class:  VirtualChannelDescription
 *  Description:  
 * =====================================================================================
 */
class VirtualChannelDescription
{
    public:
        VirtualChannelDescription ();                             /* constructor */
        uint vc;
        uint port;

    protected:

    private:

}; /* -----  end of class VirtualChannelDescription  ----- */

/*
 * =====================================================================================
 *        Class:  RouteEntry
 *  Description:  
 * =====================================================================================
 */
class RouteEntry
{
    public:
        RouteEntry ();                             /* constructor */
        uint destination;
        vector< vector<uint> > ports;
        vector< vector<uint> > channels;

    protected:

    private:

}; /* -----  end of class RouteEntry  ----- */

#endif   /* ----- #ifndef _genericdata_h_INC  ----- */

