//I worked on this assignment alone, using only this semester's course materials.
//Allen Herrera, 1854183, aherre4@emory.edu

#include "main.c"
#include "header.h"
#include <stdio.h>
#include <stdlib.h>


void  setBit( int k )
{
   int i = k/32;
   int pos = k%32;

   unsigned int flag = 1;  // flag = 0000.....00001

   flag = flag << pos;     // flag = 0000...010...000   (shifted k positions)

   prime[i] = prime[i] | flag;     // Set the bit at the k-th position in prime[i]
 
}

void  clearAll()
{
	int i;
  for (i = 0; i < 1000000; i++ )	//set all positions equal to zero
   	 prime[i] = 0;       
   
}

int testBitIs0( int k )
{
   int i = k/32;
   int pos = k%32;

   unsigned int flag = 1;  // flag = 0000.....00001

   flag = flag << pos;     // flag = 0000...010...000   (shifted k positions)

   if ( prime[i] & flag )      // Test the bit at the k-th position in prime[i]
      return 1;
   else
      return 0;
}
void sieveOfE(int N) {
	clearAll();		//clear array to make every number a canditate
	prime[0] = 1;
	prime[1] = 1;		//we know 0 and 1 are not prime
	
	int k;
	int i;
	int j;			
	for(k=2; k<=N; k= i+1)		
	{	for(i=k; i<= N; i++)	
			if( testBitIs0(i)==0)	// if i is prime, break
				break;		//else continue incrementing i until a prime is found
			
		for ( j = 2*i; j <= N; j = j + i )//since i is prime,remove all future multiples
            		setBit(j);		// set those future multiples equal to 1
					
	}
    }

int countPrimes(int N) {
	int i;
	int counter;
	counter = 0;		// initialize counter
	for (i =2; i<= N;i++)	// go through entire array searching for primes
		{
		  if (testBitIs0(i)==0)	//for each prime found in the array add 1 to counter
			counter++;	
		}

	return counter;		// return thee counter
     }

void printPrimes(int N) {
	int i;
	for (i =2; i<= N;i++)	//search array for primes
	{ if (testBitIs0(i) == 0) // if prime found, print that prime number	
		printf(" %u is prime \n", i);
	}
}

