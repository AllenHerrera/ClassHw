//I worked on this assignment alone, using only this semester's course materials.
//Allen Herrera, 1854183, aherre4@emory.edu


#include "header.h"
#include <stdio.h>
#include <stdlib.h>

void clearAll()
{	seg * p;
	p =head;

	int i;
	while ( p != NULL)	//until your at the final list 0 all
		{ 
		int i;
		for (i=0; i < 32; i++)
		p->bits[i] = 0; //set all positions equal to zero 
		    
		p = p->next;  // go to every element in the list
		
		}
	

}

void setBit( int k ) {
	seg * p;
	p =head;
   
   
   int number = (2*k)+1; 

   int i = k/32;
   int pos = k%32; //bit position
	
   unsigned int flag = 1;  // flag = 0000.....00001

   flag = flag << pos;     // flag = 0000...010...000   (shifted pos positions)

      


p->bits[i] = p->bits[i] | flag; // Set the bit at the pos-th position in bits[i]

}

int testBitIs0( int k )
{	
	seg * p;
	p =head;
	int r;
  int number = (2*k)+1;
	
  int i = k/32;
  int pos = k%32;
	
   unsigned int flag = 1;  // flag = 0000.....00001

   flag = flag << pos;     // flag = 0000...010...000   (shifted pos positions)
	r = p->bits[i] & flag;
	
   if ( r == 0 )      // Test the bit at the pos-th position in prime[i]
    { 
	return 1; }
   else
	{
      return 0;   }
}
void sieveOfE(int B) 
{
	printf(" \n");
	int N;
	if ( B%2 ==0)   // my make shift to include the number given
		N = B-1;
	else
		N = B;
	int k;
	int i;
	int j;			
	for(k=1; k<=(N/2); k= i+1)		
	{	for(i=k; i<= (N/2); i++)	
			{
			if( testBitIs0(i)==1)	// if i is prime, break
			{
				break;	}}//else continue incrementing i until a prime is found
			
			{for ( j = (2*i)+1+i; j <= (N/2); j = j + (2*i)+1 )//since i is prime,remove all future multiples		
			{
            			
				setBit(j);// set those future multiples bits equal to not 0
			
			}
			}		
	}
    }

int countPrimes(int B) {
	int i;
	int N;
	if ( B%2 ==0)
		N = B-1;
	else
		N = B;
	int counter;
	counter = 1;		        // initialize counter (including the base case of 2)
	for (i =1; i<= (N/2);i++)	// go through entire array searching for primes
		{
		  if (testBitIs0(i)==1)	//for each prime found in the array add 1 to counter
			counter++;	
		}

	return counter;		        // return the counter
     }

void printPrimes(int B) {
	int i;
	int N;
	if ( B%2 ==0)		// my make shift to include the number given
		N = B-1;
	else
		N = B;
	printf( "\n 2 is prime \n");
	for (i =1; i<= (N/2);i++)	//search array for primes
	{ if (testBitIs0(i) == 1) // if prime found, print that prime number	
		printf(" %u is prime \n", (2*i)+1);
	}
}

void factor (int B)
{	int i;
	if (B == 1)
	printf(" %d \n", B);

	while ( B%2 == 0)     // as long as the number is even divid by 2
		{ B = B/2;
	     	printf ( " 2 \n");
		}
	

	while ( B != 1)	     // as long as the number isnt 1(meaning we are done)
	{	for (i =1; i<= (B/2);i++) // increment through bit positions	
			if (testBitIs0(i)==1)	// search for the next prime number to test
				if ( B%((2*i)+1) == 0)	// if the prime factors into the number do it
					{ B= B/((2*i)+1); // do the actual division
					  printf(" %d \n", (2*i)+1);// print that number that was used to divide
					  break;
					}

	}
}



















