/*
 * =====================================================================================
 *
 *       Filename:  temp.cc
 *
 *    Description:  Generate address traces
 *
 *        Version:  1.0
 *        Created:  05/10/2010 04:39:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mitchelle Rasquinha (), mitchelle.rasquinha@gatech.edu
 *        Company:  Georgia Institute of Technology
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <iostream>

int
main ( int argc, char *argv[] )
{
    unsigned long long int address = 0xff00a;
    unsigned long long int time = 0;
    unsigned int time_incr = 50;
    while (time<1000000000)
    {
        std::cout <<"0x" <<std::hex <<address << std::dec <<" 0 "<< time << " 1" << std::endl;
        time += time_incr;
    }
    return 0;
}				/* ----------  end of function main  ---------- */
