
#ifndef LIB_RANDOM_CPP_INCLUDED
#define LIB_RANDOM_CPP_INCLUDED

#include "libRandom.hpp"


namespace libRandom
{

	///////////////////////////////////////////////////////////////////////////
	// RANDOM NUMBER GENERATOR

	randomNumberGenerator::randomNumberGenerator()
	{
	
		seeded = false;
		lengthDist = uniform;
		delayDist = uniform;
		addressDist = uniform;
		
		lengthLamdaValue = 3.35;
		delayLamdaValue = 3.35;
		addressLamdaValue = 3.35;
		
		lengthNormal = Normal( 1, 25, INFINITE_VALUE );
		
		lengthPoisson = Uniform( 0.0, 1.0 );
		delayPoisson = Uniform( 0.0, 1.0 );		
		addressPoisson = Uniform( 0.0, 1.0 );
		
		addressUniform = Uniform( 0, 100 );
		addressUniform1 = Uniform( 0, 100 );
		
		addressUniform2 = Uniform( 43, 50 );
		
		delayUniform = Uniform( 0, 1000 );
		delayUniform1 = Uniform( 0, 1000 );
		delayUniform2 = Uniform( 10, 15 );
		
		lengthUniform = Uniform( 1, 25 );
		lengthUniform1 = Uniform( 1, 25 );
		lengthUniform2 = Uniform( 7, 10 );

		lengthNormal = Normal( 1, 25, INFINITE_VALUE );
		delayNormal = Normal( 0, 1000, INFINITE_VALUE );
		addressNormal = Normal( 0, 100, INFINITE_VALUE );	
		
	}

	void randomNumberGenerator::seed(unsigned int value, bool random)
	{
	
		if( !seeded)
		{
			seeded = true;
		
		}
			if( random )
			{
			
				Uniform seeder;
			
				value = ( unsigned int ) seeder.Value();
			
			}
		
			seedValue = value;
			
			
			lengthUniform.SetSeed(ConstantSeed(value));
			
			lengthUniform1.SetSeed(ConstantSeed(value));
			lengthUniform2.SetSeed(ConstantSeed(value));
			
			lengthNormal.SetSeed(ConstantSeed(value));
			
			lengthPoisson.SetSeed(ConstantSeed(value));
			
			value++;
			
			// delay
			
			
			delayUniform.SetSeed(ConstantSeed(value));
			
			delayUniform1.SetSeed(ConstantSeed(value));
			delayUniform2.SetSeed(ConstantSeed(value));
			
			delayNormal.SetSeed(ConstantSeed(value));
			
			delayPoisson.SetSeed(ConstantSeed(value));

			value++;
			// destination
			addressUniform.SetSeed(ConstantSeed(value));
			
			addressUniform1.SetSeed(ConstantSeed(value));
			addressUniform2.SetSeed(ConstantSeed(value));
			
			addressNormal.SetSeed(ConstantSeed(value));
			
			addressPoisson.SetSeed(ConstantSeed(value));
			
		
	
	}
	
	unsigned int randomNumberGenerator::address()
	{
		
		unsigned int result;
	
		switch( addressDist )
		{
		
			case gaussian:
					result = (unsigned int)ABS(addressNormal.Value());
				break;
				
			case poisson:
					
					double p;
					
					p = 0.0;
					result = 0;
					
					while(1)
					{
						p = p-log(addressPoisson.Value());
						
						if (p<addressLamdaValue) 
						{
							result++;
						}
						else 
						{
							break;
						}
					
					}
					
				break;
			
			case hotSpot:
					result = (unsigned int)addressUniform1.Value();
					result = addressHotSpots[result];
				break;
			
			default:
					result = (unsigned int)addressUniform.Value();
				break;
		
		}
	
		return result;
	
	}
	
	
	
	unsigned int randomNumberGenerator::length()
	{
	
		unsigned int result;
	
		switch( lengthDist )
		{
		
			case gaussian:
					result = (unsigned int)ABS(lengthNormal.Value());
				break;
				
			case poisson:
					
					double p;
					
					p = 0.0;
					result = 0;
					
					while(1)
					{
						p = p-log(lengthPoisson.Value());
						
						if (p<lengthLamdaValue) 
						{
							result++;
						}
						else 
						{
							break;
						}
					
					}
					
				break;
			
			case hotSpot:
					result = (unsigned int)lengthUniform1.Value();
					result = lengthHotSpots[result];
				break;
			
			default:
					result = (unsigned int)lengthUniform.Value();
				break;
		
		}
	
		return result;
	
	}
	
	unsigned int randomNumberGenerator::delay()
	{

		unsigned int result;
	
		switch( delayDist )
		{
		
			case gaussian:
					result = (unsigned int)ABS(delayNormal.Value());
				break;
				
			case poisson:
					
					double p;
					
					p = 0.0;
					result = 0;
					
					while(1)
					{
						p = p-log(delayPoisson.Value());
						
						if (p<delayLamdaValue) 
						{
							result++;
						}
						else 
						{
							break;
						}
					
					}
					
				break;
			
			case hotSpot:
					result = (unsigned int)delayUniform1.Value();
					result = delayHotSpots[result];
				break;
			
			default:
					result = (unsigned int)delayUniform.Value();
				break;
		
		}
	
		return result;	
	
	}

	void randomNumberGenerator::delayRange( unsigned int min, unsigned int max )
	{
	
		delayUniform = Uniform( min, max );
		delayUniform1 = Uniform( min, max );
		delayUniform.SetSeed(ConstantSeed(seedValue + 1));
		delayUniform1.SetSeed(ConstantSeed(seedValue + 1));
		
	}
	
	void randomNumberGenerator::lengthRange( unsigned int min, unsigned int max )
	{
	
		lengthUniform = Uniform( min, max );
		lengthUniform1 = Uniform( min, max );
		lengthUniform.SetSeed(ConstantSeed(seedValue));
		lengthUniform1.SetSeed(ConstantSeed(seedValue));
	
	}
	
	void randomNumberGenerator::addressRange( unsigned int min, unsigned int max )
	{
	
		addressUniform = Uniform( min, max );
		addressUniform1 = Uniform( min, max );
		addressUniform.SetSeed(ConstantSeed(seedValue + 2));	
		addressUniform1.SetSeed(ConstantSeed(seedValue + 2));	

	}
	
	void randomNumberGenerator::addressLamda( double l )
	{
	
		addressLamdaValue = l;
	
	}
	
	void randomNumberGenerator::lengthLamda( double l )
	{
	
		lengthLamdaValue = l;
	
	}
	
	void randomNumberGenerator::delayLamda( double l )
	{
	
		delayLamdaValue = l;
	
	}
	
	void randomNumberGenerator::addressHotSpotRange( unsigned int min, unsigned int max, unsigned int number )
	{
	
		addressUniform2 = Uniform( min, max );
		addressUniform2.SetSeed(ConstantSeed(seedValue + 2));
		
		addressHotSpots.resize( number );
		
		newAddressHotSpots();
			
	}
	
	
	void randomNumberGenerator::delayHotSpotRange( unsigned int min, unsigned int max, unsigned int number )
	{
	
		delayUniform2 = Uniform( min, max );
		delayUniform2.SetSeed(ConstantSeed(seedValue + 1));

		newDelayHotSpots();
			
	}
	
	void randomNumberGenerator::lengthHotSpotRange( unsigned int min, unsigned int max, unsigned int number )
	{
	
		lengthUniform2 = Uniform( min, max );
		lengthUniform2.SetSeed(ConstantSeed(seedValue));
			
		newLengthHotSpots();
				
	}
	
	void randomNumberGenerator::addressDistribution( distribution type )
	{
	
		addressDist = type;
		
	}
	
	
	void randomNumberGenerator::delayDistribution( distribution type )
	{
	
		delayDist = type;
	
	}
	
	void randomNumberGenerator::lengthDistribution( distribution type )
	{
	
		lengthDist = type;
	
	}


	void randomNumberGenerator::newDelayHotSpots()
	{

		unsigned int number;

		number = delayHotSpots.size();
	
		for( unsigned int i = 0; i < number; i++ )
		{
		
			delayHotSpots[i] = (unsigned int) delayUniform2.Value();
		
		}
	
	}
	
	void randomNumberGenerator::newLengthHotSpots()
	{

		unsigned int number;

		number = lengthHotSpots.size();
	
		for( unsigned int i = 0; i < number; i++ )
		{
		
			lengthHotSpots[i] = (unsigned int) lengthUniform2.Value();
		
		}
	
	}
	
	void randomNumberGenerator::newAddressHotSpots()
	{

		unsigned int number;
	
		number = addressHotSpots.size();
	
		for( unsigned int i = 0; i < number; i++ )
		{
		
			addressHotSpots[i] = (unsigned int) addressUniform2.Value();
		
		}
	
	}

	////////////////////////////////////////////////////////////////////////////



	int poisson(double lamda, unsigned int seed)
	{
	
		double p;
		int r;
		p=0;
		r=0;
		
		Uniform ran( 0.0, 1.0);
		ran.SetSeed(ConstantSeed(seed));
		
		while (1) {
		
			p = p-log(ran.Value());
		
			if (p<lamda) {
				r++;
			}
			else {
				break;
			}
		
		}
	
		return r;
	}

	int length(int type, unsigned int seed, double min, double max, double lamda)
	{
	
		//	double lamda;
		Random_t x;
	
		Uniform ran_uni(min, max); //MIN and MAX to entered by the user. default values 10.0 and 100.0 respectively
	
		Normal ran_norm(min, max, INFINITE_VALUE); //MIN and MAX to entered by the user. default values 10.0 and 100.0 respectively
	
		ran_uni.SetSeed(ConstantSeed(seed));
		ran_norm.SetSeed(ConstantSeed(seed));
	
		switch(type){
		
		case 0:
			x = ran_uni.Value();
			return (int) x;
			break;
		
		case 1:
			x = ran_norm.Value();
		
			if(x<0)
				x = -x;
			return (int) x;
			break;
		
		default:
			x = poisson(lamda, seed); // lamda to be entered by user. Default 3.0
			return (int) x;
			break;
		
		
		}
		
		return 0;
	
	}

	std::vector<int> hot_spot(unsigned int node, unsigned int addresses, unsigned int seed) // node to be entered by user, default set to 3
	{
		//double nMAX;
		std::vector<int> a;
		Random_t j;
		a.resize(node);
		Uniform random1(0, addresses); // nMAX:ID of MAX node, to be entered by the user. default set to 100.0
		random1.SetSeed(ConstantSeed(seed));
		// default set to 100.0. 
		for(unsigned int i = 0; i<node; i++)
		{
			j = random1.Value();
			a[i] = (int) j;
		}
		return a;
	}

	int destination(int type, unsigned int seed, unsigned int nodes,unsigned int addresses)
	{
		//double MIN, MAX;
		Random_t x;
		Uniform ran_dest(0, nodes); // this is for selecting the destination uniformly
		ran_dest.SetSeed(ConstantSeed(seed));
	
		// UNIFORM
		if(type == 0) 
		{ 
			x = ran_dest.Value();
			return (int) x;
		}


		// HOT SPOT
		else 
		{   //int node;
			int x,y;
			
			std::vector<int> p;
			
			p = hot_spot(nodes, addresses, seed);           // node to be entered by user. This value specifies, how many nodes to  
							        // select for hot spot. Default set to 3

			Uniform random2(0.0, nodes-1);// this selects one particular node for hot spot from total # entered by the user 
							       // above	
							       
			random2.SetSeed(ConstantSeed(seed));
			y = (int)random2.Value();
			x = p[y];
			return x;
		}
			  
			  
	}





}



#endif
