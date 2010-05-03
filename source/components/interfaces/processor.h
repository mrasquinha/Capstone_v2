/*
 * =====================================================================================
 *
 *       Filename:  processor.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/19/2010 12:12:04 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mitchelle Rasquinha (), mitchelle.rasquinha@gatech.edu
 *        Company:  Georgia Institute of Technology
 *
 * =====================================================================================
 */

#ifndef  _processor_h_INC
#define  _processor_h_INC

#include	"networkComponent.h"
#include	"../../data_types/impl/irisEvent.h"
#include	"interface.h"

/*
 * =====================================================================================
 *        Class:  Processor
 *  Description:  
 * =====================================================================================
 */
class Processor : public NetworkComponent
{
    public:
        Processor ();                             /* constructor */
        vector < Interface* > interface_connections;
        virtual ~Processor();
        void init();
        virtual string toString() const;
        virtual void process_event(IrisEvent* e) = 0;
        virtual void setup() = 0;
        virtual void set_no_vcs( uint v ) = 0;

    protected:

    private:

}; /* -----  end of class Processor  ----- */

#endif   /* ----- #ifndef _processor_h_INC  ----- */

