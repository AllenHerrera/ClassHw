/*THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - ALLEN HERRERA */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct _seg {  /* definition of new type "seg" */
    int  bits[256];
    struct _seg  *next,*prev;        
      }seg ;

#define BITSPERSEG  (8*256*sizeof(int))
// returns a pointer to the linked segment with the number j in it
// ex. j=16387  means its in the 2nd linked segment
seg* whichseg( int j , seg* head) {
	
	seg* pt;
	int p = ((j-3)/16384)+1;
	int i;

	pt=head;
	//traverse to the correct segment
	for(i=1; i<p;i++) {
		pt=pt->next;	
	}
	return pt;
}
//what int (a set of 32 bits) is the number j in
int whichint(int j) {
	
	return ((j-3)%16384)/64;
}
//which bit (in a set of 32) is the one im looking for
int whichbit (int j) {
	return (((j-3)%16384)%64)/2;
}

void main(int argc, char *argv[]) {

	seg *head,*pt;
	int	 i;
	int howmany, upto;

	//goldbach sample from class only worked if arg was sent in with the ./goldbach
	if (argc == 2) sscanf(argv[1],"%d",&howmany);
		else return;
	upto = howmany;
	howmany = ((howmany/2) +BITSPERSEG -1)/BITSPERSEG;

	head = (  seg * ) malloc(sizeof(seg));
	pt=head;
	
	//link the segments created
	for (i=1;i<howmany;i++) {
		pt->next = (  seg *) malloc(sizeof (seg)); 
		pt->next->prev = pt;
		pt=pt->next;	
	}
	//printf("Done allocating %d nodes\n",i);
	int j;
	pt=head;
	//clear int's at a time for each segment
	for (i=1;i<=howmany;i++) {
		for(j=0;j<255;j++) {
		pt->bits[j] = 0;
		}
	pt=pt->next;
	//printf("Done clearing node %d \n",i);
	}

	//find the primes
printf("Calculating odd primes up to %d...\n",upto);
	//sqrt() wasnt working so used i^2
	
	for(i = 3 ; (i*i)<=upto ; i+=2) {
		seg* myPT = whichseg(i,head);
		int myInt = whichint(i);
		int myBit = whichbit(i);
	//after or'ing with the bit pos set to one, if its unchanged that means the number was turned on 
		if((myPT->bits[myInt]|(1<<myBit)) == myPT->bits[myInt]) {
			//the number isnt prime
			continue;
		} else {
			//we have a prime so remove its multiples!!!
			int j;
			for( j = i+i; j<=upto; j+=i) {
				if((j%2)!=0) {
					seg* nonprimePT = whichseg(j,head);
					int nonprimeInt = whichint(j);
					int nonprimeBit = whichbit(j);	
					nonprimePT->bits[nonprimeInt] = nonprimePT->bits[nonprimeInt]|(1<<nonprimeBit);	
				}
			}
		}
	}

	//count the primes
	int countPrimes =0;
	pt=head;
	int finalInt = whichint(upto);
	int finalBit = whichbit(upto);
	int segment =1;
	int num = 3;
	for(segment=1; segment<=howmany; segment++) {
		for(i = 0 ; i<=255 ; i++) {
			for(j = 0 ; j<32;j++) {
				if (((pt->bits[i]|(1<<j))) == pt->bits[i]) {
					//printf(" number not prime: %d: data:i- %d and j- %d \n", num,i,j);
					num+=2;
					continue;
				} else {
					if(num>upto) {
					//done counting
					break;
					} else {
					//found a prime!
					countPrimes++;
					}
				}
				num+=2;
			}
		}
	pt= pt->next;
	}
	printf("The number of odd primes less than or equal to %d is:  %d \n",upto,countPrimes);
	
//now from prime numbers calc the possible pair sums
	printf("Enter Even Numbers >5 for Goldbach Tests\n");
	int even;
	scanf("%d",&even);
	int lasteven = 0;
	while(even) {
		int sumCounter = 0;
		int lasti = 0;
		//when a non-int was entered, my program would freakout.
		if(even == lasteven) {break;}
		//end on EOF
		if(even == EOF) { break;}
		//must be even number and greater than 5 and less than that to which i calc primes for
		if(even >= 6 & even <= upto & even%2==0)	{
			int lowerNum = 3;
			seg* lowerPT = whichseg(lowerNum,head);
			int lowerInt = whichint(lowerNum);
			int lowerBit = whichbit(lowerNum);
			
			int higherNum = even-3;
			seg* higherPT = whichseg(higherNum,head);
			int higherInt = whichint(higherNum);
			int higherBit = whichbit(higherNum);
			//while statement
			while(lowerNum <= higherNum) {
			if((lowerPT->bits[lowerInt]|(1<<lowerBit)) == lowerPT->bits[lowerInt]) {
					//lower is not prime
						//rise lowerbit/ lower higherbit
						if(lowerBit==31) {
							lowerBit=0;
							lowerInt++;
							if(lowerInt==256) {
								lowerInt =0;
								lowerPT=lowerPT->next;
							}
							lowerNum+=2;
						} else {
							lowerBit++;
							lowerNum+=2;
						}
						if(higherBit==0) {
							higherBit=31;
							higherInt--;
							if(higherInt==-1) {
								higherInt =255;
								higherPT=higherPT->prev;
							}
							higherNum-=2;
						} else {
							higherNum-=2;
							higherBit--;
						}
						/////// end of bit manipulation
					continue;
				} else {
					if((higherPT->bits[higherInt]|(1<<higherBit)) == higherPT->bits[higherInt]) {
					//higher is not prime
						//rise lowerbit/ lower higherbit
						if(lowerBit==31) {
							lowerBit=0;
							lowerInt++;
							if(lowerInt==256) {
								lowerInt =0;
								lowerPT=lowerPT->next;
							}
							lowerNum+=2;
						} else {
							lowerBit++;
							lowerNum+=2;
						}
						if(higherBit==0) {
							higherBit=31;
							higherInt--;
							if(higherInt==-1) {
								higherInt =255;
								higherPT=higherPT->prev;
							}
							higherNum-=2;
						} else {
							higherNum-=2;
							higherBit--;
						}
						/////// end of bit manipulation
					continue;
					} else {
						sumCounter++;
						lasti = lowerNum;
						//printf("solution %d: lowerNum- %d, higherNum %d \n",sumCounter,lowerNum, higherNum);
						//rise lowerbit /lower higherbit
						if(lowerBit==31) {
							lowerBit=0;
							lowerInt++;
							if(lowerInt==256) {
								lowerInt =0;
								lowerPT=lowerPT->next;
							}
							lowerNum+=2;
						} else {
							lowerBit++;
							lowerNum+=2;
						}
						if(higherBit==0) {
							higherBit=31;
							higherInt--;
							if(higherInt==-1) {
								higherInt =255;
								higherPT=higherPT->prev;
							}
							higherNum-=2;
						} else {
							higherNum-=2;
							higherBit--;
						}
						/////// end of bit manipulation
					}
				}
			
			} //end while
		//calc the middle term using the value
		printf("Largest %d = %d + %d out of %d solutions \n", even ,lasti, even-lasti,sumCounter);
		}
		lasteven = even;
		scanf("%d",&even);
	} // outer while
}





