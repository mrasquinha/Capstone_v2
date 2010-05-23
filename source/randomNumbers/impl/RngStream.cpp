// GENERAL PUBLIC LICENSE AGREEMENT
// 
// PLEASE READ THIS DOCUMENT CAREFULLY BEFORE UTILIZING THE PROGRAM
// 
// BY UTILIZING THIS PROGRAM, YOU AGREE TO BECOME BOUND BY THE TERMS OF
// THIS LICENSE.  IF YOU DO NOT AGREE TO THE TERMS OF THIS LICENSE, DO
// NOT USE THIS PROGRAM OR ANY PORTION THEREOF IN ANY FORM OR MANNER.
// 
// This Program is licensed, not sold to you by GEORGIA TECH RESEARCH
// CORPORATION ("GTRC"), owner of all code and accompanying documentation
// (hereinafter "Program"), for use only under the terms of this License,
// and GTRC reserves any rights not expressly granted to you.
// 
// 1.  This License allows you to:
// 
// (a) make copies and distribute copies of the Program's source code
// provide that any such copy clearly displays any and all appropriate
// copyright notices and disclaimer of warranty as set forth in Article 5
// and 6 of this License.  All notices that refer to this License and to
// the absence of any warranty must be kept intact at all times.  A copy
// of this License must accompany any and all copies of the Program
// distributed to third parties.
// 
// A fee may be charged to cover the cost associated with the physical
// act of transferring a copy to a third party.  At no time shall the
// program be sold for commercial gain either alone or incorporated with
// other program(s) without entering into a separate agreement with GTRC.
//  
// 
// (b) modify the original copy or copies of the Program or any portion
// thereof ("Modification(s)").  Modifications may be copied and
// distributed under the terms and conditions as set forth above,
// provided the following conditions are met:
// 
//     i) any and all modified files must be affixed with prominent
// notices that you have changed the files and the date that the changes
// occurred.
// 		
//     ii) any work that you distribute, publish, or make available, that
// in whole or in part contains portions of the Program or derivative
// work thereof, must be licensed at no charge to all third parties under
// the terms of this License.
// 
//    iii) if the modified program normally reads commands interactively
// when run, you must cause it, when started running for such interactive
// use in the most ordinary way, to display and/or print an announcement
// with all appropriate copyright notices and disclaimer of warranty as
// set forth in Article 5 and 6 of this License to be clearly displayed.
// In addition, you must provide reasonable access to this License to the
// user.
// 
// Any portion of a Modification that can be reasonably considered
// independent of the Program and separate work in and of itself is not
// subject to the terms and conditions set forth in this License as long
// as it is not distributed with the Program or any portion thereof.
// 
// 
// 2. This License further allows you to copy and distribute the Program
//    or a work based on it, as set forth in Article 1 Section b in
//    object code or executable form under the terms of Article 1 above
//    provided that you also either:
// 
//    i) accompany it with complete corresponding machine-readable source
// code, which must be distributed under the terms of Article 1, on a
// medium customarily used for software interchange; or,
// 
//   ii) accompany it with a written offer, valid for no less than three
// (3) years from the time of distribution, to give any third party, for
// no consideration greater than the cost of physical transfer, a
// complete machine-readable copy of the corresponding source code, to be
// distributed under the terms of Article 1 on a medium customarily used
// for software interchange; or,
// 
// 
// 3.  Export Law Assurance.
// 
// You agree that the Software will not be shipped, transferred or
// exported, directly into any country prohibited by the United States
// Export Administration Act and the regulations thereunder nor will be
// used for any purpose prohibited by the Act.
//  
// 4.  Termination.
// 
// If at anytime you are unable to comply with any portion of this
// License you must immediately cease use of the Program and all
// distribution activities involving the Program or any portion thereof.
// 
// 
// 5.  Disclaimer of Warranties and Limitation on Liability.
// 
// YOU ACCEPT THE PROGRAM ON AN "AS IS" BASIS.  GTRC MAKES NO WARRANTY
// THAT ALL ERRORS CAN BE OR HAVE BEEN ELIMINATED FROM PROGRAM.  GTRC
// SHALL NOT BE RESPONSIBLE FOR LOSSES OF ANY KIND RESULTING FROM THE USE
// OF PROGRAM AND ITS ACCOMPANYING DOCUMENT(S), AND CAN IN NO WAY PROVIDE
// COMPENSATION FOR ANY LOSSES SUSTAINED, INCLUDING BUT NOT LIMITED TO
// ANY OBLIGATION, LIABILITY, RIGHT, CLAIM OR REMEDY FOR TORT, OR FOR ANY
// ACTUAL OR ALLEGED INFRINGEMENT OF PATENTS, COPYRIGHTS, TRADE SECRETS,
// OR SIMILAR RIGHTS OF THIRD PARTIES, NOR ANY BUSINESS EXPENSE, MACHINE
// DOWNTIME OR DAMAGES CAUSED TO YOU BY ANY DEFICIENCY, DEFECT OR ERROR
// IN PROGRAM OR MALFUNCTION THEREOF, NOR ANY INCIDENTAL OR CONSEQUENTIAL
// DAMAGES, HOWEVER CAUSED.  GTRC DISCLAIMS ALL WARRANTIES, BOTH EXPRESS
// AND IMPLIED RESPECTING THE USE AND OPERATION OF PROGRAM AND ITS
// ACCOMPANYING DOCUMENTATION, INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR PARTICULAR PURPOSE AND ANY IMPLIED
// WARRANTY ARISING FROM COURSE OF PERFORMANCE, COURSE OF DEALING OR
// USAGE OF TRADE.  GTRC MAKES NO WARRANTY THAT PROGRAM IS ADEQUATELY OR
// COMPLETELY DESCRIBED IN, OR BEHAVES IN ACCORDANCE WITH ANY
// ACCOMPANYING DOCUMENTATION.  THE USER OF PROGRAM IS EXPECTED TO MAKE
// THE FINAL EVALUATION OF PROGRAM'S USEFULNESS IN USER'S OWN
// ENVIRONMENT.
// 
// GTRC represents that, to the best of its knowledge, the software
// furnished hereunder does not infringe any copyright or patent.
// 
// GTRC shall have no obligation for support or maintenance of Program.
// 
// 6.  Copyright Notice.
// 
// THE SOFTWARE AND ACCOMPANYING DOCUMENTATION ARE COPYRIGHTED WITH ALL
// RIGHTS RESERVED BY GTRC.  UNDER UNITED STATES COPYRIGHT LAWS, THE
// SOFTWARE AND ITS ACCOMPANYING DOCUMENTATION MAY NOT BE COPIED EXCEPT
// AS GRANTED HEREIN.
// 
// You acknowledge that GTRC is the sole owner of Program, including all
// copyrights subsisting therein.  Any and all copies or partial copies
// of Program made by you shall bear the copyright notice set forth below
// and affixed to the original version or such other notice as GTRC shall
// designate.  Such notice shall also be affixed to all improvements or
// enhancements of Program made by you or portions thereof in such a
// manner and location as to give reasonable notice of GTRC's copyright
// as set forth in Article 1.
// 
// Said copyright notice shall read as follows:
// 
// Copyright 2004
// Dr. George F. Riley
// Georgia Tech Research Corporation
// Atlanta, Georgia 30332-0415
// All Rights Reserved
//
// $Id: RngStream.cc,v 1.6 2006/08/14 15:31:24 dheeraj Exp $



/***********************************************************************\
 *
 * File:           RngStream.cpp for multiple streams of Random Numbers
 * Language:       ISO-C++
 * Copyright:      Pierre L'Ecuyer, University of Montreal
 * Notice:         This code can be used freely for personnal, academic,
 *                 or non-commercial purposes. For commercial purposes, 
 *                 please contact P. L'Ecuyer at: lecuyer@iro.umontreal.ca
 * Date:           14 August 2001
 *
\***********************************************************************/


#include <cstdlib>
#include <iostream>
#include "RngStream.hpp"
using namespace std;

namespace
{
const double m1   =       4294967087.0;
const double m2   =       4294944443.0;
const double norm =       1.0 / (m1 + 1.0);
const double a12  =       1403580.0;
const double a13n =       810728.0;
const double a21  =       527612.0;
const double a23n =       1370589.0;
const double two17 =      131072.0;
const double two53 =      9007199254740992.0;
const double fact =       5.9604644775390625e-8;     /* 1 / 2^24  */

// The following are the transition matrices of the two MRG components
// (in matrix form), raised to the powers -1, 1, 2^76, and 2^127, resp.

const double InvA1[3][3] = {          // Inverse of A1p0
       { 184888585.0,   0.0,  1945170933.0 },
       {         1.0,   0.0,           0.0 },
       {         0.0,   1.0,           0.0 }
       };

const double InvA2[3][3] = {          // Inverse of A2p0
       {      0.0,  360363334.0,  4225571728.0 },
       {      1.0,          0.0,           0.0 },
       {      0.0,          1.0,           0.0 }
       };

const double A1p0[3][3] = {
       {       0.0,        1.0,       0.0 },
       {       0.0,        0.0,       1.0 },
       { -810728.0,  1403580.0,       0.0 }
       };

const double A2p0[3][3] = {
       {        0.0,        1.0,       0.0 },
       {        0.0,        0.0,       1.0 },
       { -1370589.0,        0.0,  527612.0 }
       };

const double A1p76[3][3] = {
       {      82758667.0, 1871391091.0, 4127413238.0 },
       {    3672831523.0,   69195019.0, 1871391091.0 },
       {    3672091415.0, 3528743235.0,   69195019.0 }
       };

const double A2p76[3][3] = {
       {    1511326704.0, 3759209742.0, 1610795712.0 },
       {    4292754251.0, 1511326704.0, 3889917532.0 },
       {    3859662829.0, 4292754251.0, 3708466080.0 }
       };

const double A1p127[3][3] = {
       {    2427906178.0, 3580155704.0,  949770784.0 },
       {     226153695.0, 1230515664.0, 3580155704.0 },
       {    1988835001.0,  986791581.0, 1230515664.0 }
       };

const double A2p127[3][3] = {
       {    1464411153.0,  277697599.0, 1610723613.0 },
       {      32183930.0, 1464411153.0, 1022607788.0 },
       {    2824425944.0,   32183930.0, 2093834863.0 }
       };



//-------------------------------------------------------------------------
// Return (a*s + c) MOD m; a, s, c and m must be < 2^35
//
double MultModM (double a, double s, double c, double m)
{
    double v;
    long a1;

    v = a * s + c;

    if (v >= two53 || v <= -two53) {
        a1 = static_cast<long> (a / two17);    a -= a1 * two17;
        v  = a1 * s;
        a1 = static_cast<long> (v / m);     v -= a1 * m;
        v = v * two17 + a * s + c;
    }

    a1 = static_cast<long> (v / m);
    /* in case v < 0)*/
    if ((v -= a1 * m) < 0.0) return v += m;   else return v;
}


//-------------------------------------------------------------------------
// Compute the vector v = A*s MOD m. Assume that -m < s[i] < m.
// Works also when v = s.
//
void MatVecModM (const double A[3][3], const double s[3], double v[3],
                 double m)
{
    int i;
    double x[3];               // Necessary if v = s

    for (i = 0; i < 3; ++i) {
        x[i] = MultModM (A[i][0], s[0], 0.0, m);
        x[i] = MultModM (A[i][1], s[1], x[i], m);
        x[i] = MultModM (A[i][2], s[2], x[i], m);
    }
    for (i = 0; i < 3; ++i)
        v[i] = x[i];
}


//-------------------------------------------------------------------------
// Compute the matrix C = A*B MOD m. Assume that -m < s[i] < m.
// Note: works also if A = C or B = C or A = B = C.
//
void MatMatModM (const double A[3][3], const double B[3][3],
                 double C[3][3], double m)
{
    int i, j;
    double V[3], W[3][3];

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j)
            V[j] = B[j][i];
        MatVecModM (A, V, V, m);
        for (j = 0; j < 3; ++j)
            W[j][i] = V[j];
    }
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j)
            C[i][j] = W[i][j];
}


//-------------------------------------------------------------------------
// Compute the matrix B = (A^(2^e) Mod m);  works also if A = B. 
//
void MatTwoPowModM (const double A[3][3], double B[3][3], double m, long e)
{
   int i, j;

   /* initialize: B = A */
   if (A != B) {
      for (i = 0; i < 3; ++i)
         for (j = 0; j < 3; ++j)
            B[i][j] = A[i][j];
   }
   /* Compute B = A^(2^e) mod m */
   for (i = 0; i < e; i++)
      MatMatModM (B, B, B, m);
}


//-------------------------------------------------------------------------
// Compute the matrix B = (A^n Mod m);  works even if A = B.
//
void MatPowModM (const double A[3][3], double B[3][3], double m, long n)
{
    int i, j;
    double W[3][3];

    /* initialize: W = A; B = I */
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j) {
            W[i][j] = A[i][j];
            B[i][j] = 0.0;
        }
    for (j = 0; j < 3; ++j)
        B[j][j] = 1.0;

    /* Compute B = A^n mod m using the binary decomposition of n */
    while (n > 0) {
        if (n % 2) MatMatModM (W, B, B, m);
        MatMatModM (W, W, W, m);
        n /= 2;
    }
}
} // end of anonymous namespace


//-------------------------------------------------------------------------
// Check that the seeds are legitimate values. Returns true if legal seeds,
// false otherwise.
//
bool RngStream::CheckSeed (const unsigned long seed[6])
{
    int i;

    for (i = 0; i < 3; ++i) {
        if (seed[i] >= m1) {
            cerr << "****************************************\n\n"
                 << "ERROR: Seed[" << i << "] >= 4294967087, Seed is not set."
                 << "\n\n****************************************\n\n";
            return (false);
        }
    }
    for (i = 3; i < 6; ++i) {
        if (seed[i] >= m2) {
	  cout << "Seed[" << i << "] = " << seed[i] << endl; 
            cerr << "*****************************************\n\n"
                 << "ERROR: Seed[" << i << "] >= 4294944443, Seed is not set."
                 << "\n\n*****************************************\n\n";
            return (false);
        }
    }
    if (seed[0] == 0 && seed[1] == 0 && seed[2] == 0) {
         cerr << "****************************\n\n"
              << "ERROR: First 3 seeds = 0.\n\n"
              << "****************************\n\n";
         return (false);
    }
    if (seed[3] == 0 && seed[4] == 0 && seed[5] == 0) {
         cerr << "****************************\n\n"
              << "ERROR: Last 3 seeds = 0.\n\n"
              << "****************************\n\n";
         return (false);
    }
    return true;
}




//-------------------------------------------------------------------------
// Generate the next random number.
//
double RngStream::U01 ()
{
    long k;
    double p1, p2, u;

    /* Component 1 */
    p1 = a12 * Cg[1] - a13n * Cg[0];
    k = static_cast<long> (p1 / m1);
    p1 -= k * m1;
    if (p1 < 0.0) p1 += m1;
    Cg[0] = Cg[1]; Cg[1] = Cg[2]; Cg[2] = p1;

    /* Component 2 */
    p2 = a21 * Cg[5] - a23n * Cg[3];
    k = static_cast<long> (p2 / m2);
    p2 -= k * m2;
    if (p2 < 0.0) p2 += m2;
    Cg[3] = Cg[4]; Cg[4] = Cg[5]; Cg[5] = p2;

    /* Combination */
    u = ((p1 > p2) ? (p1 - p2) * norm : (p1 - p2 + m1) * norm);

    return (anti == false) ? u : (1 - u);
}


//-------------------------------------------------------------------------
// Generate the next random number with extended (53 bits) precision.
//
double RngStream::U01d ()
{
    double u;
    u = U01();
    if (anti) {
        // Don't forget that U01() returns 1 - u in the antithetic case
        u += (U01() - 1.0) * fact;
        return (u < 0.0) ? u + 1.0 : u;
    } else {
        u += U01() * fact;
        return (u < 1.0) ? u : (u - 1.0);
    }
}


//*************************************************************************
// Public members of the class start here


//-------------------------------------------------------------------------
// The default seed of the package; will be the seed of the first
// declared RngStream, unless SetPackageSeed is called.
//
#ifdef NO_LONGER_USED
double RngStream::nextSeed[6] =
{
   12345.0, 12345.0, 12345.0, 12345.0, 12345.0, 12345.0
};
#endif

//-------------------------------------------------------------------------
// constructor
//
RngStream::RngStream ()
{
   anti = false;
   incPrec = false;

#ifdef NO_LONGER_USED
   // Deprecated.  All instances of RngStream EXPLICITLY call SetSeed()
   /* Information on a stream. The arrays {Cg, Bg, Ig} contain the current
   state of the stream, the starting state of the current SubStream, and the
   starting state of the stream. This stream generates antithetic variates
   if anti = true. It also generates numbers with extended precision (53
   bits if machine follows IEEE 754 standard) if incPrec = true. nextSeed
   will be the seed of the next declared RngStream. */

   for (int i = 0; i < 6; ++i) {
      Bg[i] = Cg[i] = Ig[i] = nextSeed[i];
   }

   MatVecModM (A1p127, nextSeed, nextSeed, m1);
   MatVecModM (A2p127, &nextSeed[3], &nextSeed[3], m2);
#endif
}


//-------------------------------------------------------------------------
// Reset Stream to beginning of Stream.
//
void RngStream::ResetStartStream ()
{
   for (int i = 0; i < 6; ++i)
      Cg[i] = Bg[i] = Ig[i];
}


//-------------------------------------------------------------------------
// Reset Stream to beginning of SubStream.
//
void RngStream::ResetStartSubstream ()
{
   for (int i = 0; i < 6; ++i)
      Cg[i] = Bg[i];
}


//-------------------------------------------------------------------------
// Reset Stream to NextSubStream.
//
void RngStream::ResetNextSubstream ()
{
   MatVecModM(A1p76, Bg, Bg, m1);
   MatVecModM(A2p76, &Bg[3], &Bg[3], m2);
   for (int i = 0; i < 6; ++i)
       Cg[i] = Bg[i];
}


#ifdef NO_LONGER_USED
//-------------------------------------------------------------------------
bool RngStream::SetPackageSeed (const unsigned long seed[6])
{
  if (!CheckSeed (seed)) return false;
  for (int i = 0; i < 6; ++i)
    nextSeed[i] = seed[i];
  return true;
}
#endif


//-------------------------------------------------------------------------
bool RngStream::SetSeed (const unsigned long seed[6])
{
  if (!CheckSeed (seed)) return false;
   for (int i = 0; i < 6; ++i)
      Cg[i] = Bg[i] = Ig[i] = seed[i];
   return true;
}


//-------------------------------------------------------------------------
// if e > 0, let n = 2^e + c;
// if e < 0, let n = -2^(-e) + c;
// if e = 0, let n = c.
// Jump n steps forward if n > 0, backwards if n < 0.
//
void RngStream::AdvanceState (long e, long c)
{
    double B1[3][3], C1[3][3], B2[3][3], C2[3][3];

    if (e > 0) {
        MatTwoPowModM (A1p0, B1, m1, e);
        MatTwoPowModM (A2p0, B2, m2, e);
    } else if (e < 0) {
        MatTwoPowModM (InvA1, B1, m1, -e);
        MatTwoPowModM (InvA2, B2, m2, -e);
    }

    if (c >= 0) {
        MatPowModM (A1p0, C1, m1, c);
        MatPowModM (A2p0, C2, m2, c);
    } else {
        MatPowModM (InvA1, C1, m1, -c);
        MatPowModM (InvA2, C2, m2, -c);
    }

    if (e) {
        MatMatModM (B1, C1, C1, m1);
        MatMatModM (B2, C2, C2, m2);
    }

    MatVecModM (C1, Cg, Cg, m1);
    MatVecModM (C2, &Cg[3], &Cg[3], m2);
}


//-------------------------------------------------------------------------
void RngStream::GetState (unsigned long seed[6]) const
{
   for (int i = 0; i < 6; ++i)
      seed[i] = static_cast<unsigned long> (Cg[i]);
}


//-------------------------------------------------------------------------
void RngStream::IncreasedPrecis (bool incp)
{
   incPrec = incp;
}


//-------------------------------------------------------------------------
void RngStream::SetAntithetic (bool a)
{
   anti = a;
}


//-------------------------------------------------------------------------
// Generate the next random number.
//
double RngStream::RandU01 ()
{
   if (incPrec)
      return U01d();
   else
      return U01();
}


//-------------------------------------------------------------------------
// Generate the next random integer.
//
long RngStream::RandInt (long low, long high)
{
    return low + static_cast<long> ((high - low + 1) * RandU01 ());
}

