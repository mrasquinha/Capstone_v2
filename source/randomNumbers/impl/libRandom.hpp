#ifndef  LIB_RANDOM_HPP_INCLUDED
#define  LIB_RANDOM_HPP_INCLUDED

#include <stdio.h>
#include <math.h>
#include "rng.hpp"
#include <iostream>
#include <sstream>
//#include "../../libGreg/implementation/libGreg.hpp"

#include <vector>

#ifndef ABS
#define ABS(x) ( (x ) > 0 ? (x):(-(x)) )
#endif

namespace libRandom
{
	#define RMIN 10.0
	#define RMAX 100.0
	#define LAMDA 3.0
	#define NODE 3
	#define RN 100.0
	#define TYPE 2
	#define DEFAULT_SEED 5
	#define ADDRESSES 10


	class randomNumberGenerator
	{
	
		public:
			enum distribution{ uniform, gaussian, poisson, hotSpot };
	
		private:
			bool seeded;
			unsigned int seedValue;
			
			// time
			Uniform lengthUniform;
			
			Uniform lengthUniform1;
			Uniform lengthUniform2;
			
			Normal lengthNormal;
			
			Uniform lengthPoisson;
			double lengthLamdaValue;
			
			distribution lengthDist;
			
			std::vector< unsigned int > lengthHotSpots;
				
			// delay
			Uniform delayUniform;
			
			Uniform delayUniform1;
			Uniform delayUniform2;
			
			Normal delayNormal;
			
			Uniform delayPoisson;
			double delayLamdaValue;
			
			distribution delayDist;

			std::vector< unsigned int > delayHotSpots;

			// address
			Uniform addressUniform;
			
			Uniform addressUniform1;
			Uniform addressUniform2;
			
			Normal addressNormal;
			
			Uniform addressPoisson;
			double addressLamdaValue;

			distribution addressDist;
			
			std::vector< unsigned int > addressHotSpots;

			
		public:
		
			randomNumberGenerator();
		
			void seed(unsigned int value, bool random = false);
			
			unsigned int address();
			unsigned int length();
			unsigned int delay();
	
			void delayRange( unsigned int min, unsigned int max );
			void lengthRange( unsigned int min, unsigned int max );
			void addressRange( unsigned int min, unsigned int max );
			
			void addressLamda( double l );
			void lengthLamda( double l );
			void delayLamda( double l );
			
			void addressHotSpotRange( unsigned int min, unsigned int max, unsigned int number );
			void delayHotSpotRange( unsigned int min, unsigned int max, unsigned int number );
			void lengthHotSpotRange( unsigned int min, unsigned int max, unsigned int number );
			
			void newDelayHotSpots();
			void newLengthHotSpots();
			void newAddressHotSpots();
			
			void addressDistribution( distribution type );
			void delayDistribution( distribution type );
			void lengthDistribution( distribution type );

	};



	int poisson(double lamda, unsigned int seed = DEFAULT_SEED); // poisson distribuion
	int length(int type, unsigned int seed = DEFAULT_SEED, double min = RMIN, double max = RMAX, double lamda = LAMDA);
	std::vector<int> hot_spot(unsigned int node, unsigned int addresses, unsigned int seed = DEFAULT_SEED);
	int destination(int type, unsigned int seed = DEFAULT_SEED, unsigned int nodes = NODE, unsigned int addresses = ADDRESSES);

}

#endif  
