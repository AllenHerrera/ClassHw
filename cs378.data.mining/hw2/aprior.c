#include <stdlib.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <string.h>
#include <time.h>
#include <math.h>

#define MAXTRANSACTIONSIZE  30
#define MAXTRANSACTIONS  100000

/*************************************************************************/
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
 
// Alphabet size (# of symsbols)
#define ALPHABET_SIZE (300)

#define MOD_SIZE (300)

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) (hash(c)%MOD_SIZE )

/* definition of itemset counter */
typedef struct _ItemSet{  
	char itemset[MAXTRANSACTIONSIZE*5];    
	int  count;
}ItemSet;

// trie node
typedef struct trie_node{
    long value;
    int itemIndex;
    ItemSet *items;
    struct trie_node *children[ALPHABET_SIZE];
}trie_node_t;
 
// trie ADT
typedef struct trie {
    trie_node_t *root;
    int count;
}trie_t;

unsigned long hash(unsigned char *str)
    {
        unsigned long hash = 5381;
        int c;

        while (c = *str++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;
    }

// Returns new trie node (initialized to NULLs)
trie_node_t *getNode(int j)
{
    trie_node_t *pNode = NULL;
 
    pNode = (trie_node_t *)malloc(sizeof(trie_node_t));
 	
    if( pNode )
    {
        int i;
 
        pNode->value = 0;
	pNode->itemIndex = 0;
	//ItemSet *table; 	table = (ItemSet*)malloc(1000* sizeof(ItemSet));

 	pNode->items = (ItemSet*)malloc((1000/j)* sizeof(ItemSet));
	
        for(i = 0; i < ALPHABET_SIZE; i++)
        {
            pNode->children[i] = NULL;  //consider removing????
        }
    }
 
    return pNode;
}
 
// Initializes trie (root is dummy node)
void initialize(trie_t *pTrie)
{
    pTrie->root = getNode(1);
    pTrie->count = 0;
}
/***************************-Insert Only If Candidate-**********************************************/
void insertIF(trie_t *pTrie, char *key[], int arrIndex , ItemSet *table, int *tableIndex ,int supportCount , int j) {
	//if(j>4)printf("key[0]:%s \n",key[0]);
	int i = 0;
	while(i< arrIndex) {
			
			
			int index;
			trie_node_t *pCrawl;
		 
			pTrie->count++;
			pCrawl = pTrie->root;


			char * word;
			char buffer[MAXTRANSACTIONSIZE*5];
			
			strcpy(buffer,key[i]);
			
			word = strtok(buffer, " ");
			int skip =0;
			do {
				//test if taking out atoi(word) makes difference
				if(word == NULL || atoi(word)==0 ) { 
					//printf("found line end\n");
					break;
				}
	
				index = CHAR_TO_INDEX(word);
				
				if( !pCrawl->children[index] && pCrawl->value >=500 )
				{
				    pCrawl->children[index] = getNode(j);
					  pCrawl->value +=1;
				    pCrawl = pCrawl->children[index];
				  
				} else if (pCrawl->children[index] && pCrawl->value >=500 ) {
					  pCrawl->value +=1;
					 pCrawl = pCrawl->children[index];
				} else {
					skip=1;
					
					//printf("skipping: %s\n",key[i]);
				}


			word = strtok (NULL, " ");

		   } while (word != NULL);

		if(!skip) {
			int k;
			for (k=0; k<=pCrawl->itemIndex;k++) {

				if(strcmp(key[i],pCrawl->items[k].itemset) == 0) { //ItemSet exists, up counter
					pCrawl->value +=1;
					pCrawl->items[k].count+=1;
					if (pCrawl->items[k].count == supportCount) {
					ItemSet t;
					strcpy(t.itemset,key[i]);
					
					t.count = pCrawl->items[k].count;
					
					table[*tableIndex]= t;
	     				 *tableIndex+=1;
					}
			
				}
			}
			//dont add new items, just skip
		}

	i++;	  	
	}

return;
}

/***************************Single Insert**********************************************/
// lets me set nodes to include candidate sets, quick simple prune of candidates with subsets that dont have
// high enough support count and speed up combination inserting later
void insertSingle(trie_t *pTrie, char * temp, int j,int *duplicate) {
			
	int index;
	trie_node_t *pCrawl;

	pTrie->count++;
	pCrawl = pTrie->root;

	char * word;
	char buffer[MAXTRANSACTIONSIZE*5];

	strcpy(buffer,temp);

	word = strtok(buffer, " ");
	int done =0;
	int skip =0;
	do {
		//test if taking out atoi(word) makes difference
		if(word == NULL || atoi(word)==0 ) { 
			//printf("found line end\n");
			break;
		}
		index = CHAR_TO_INDEX(word);
	
		if( !pCrawl->children[index] && pCrawl->value >=500 )
		{
		    pCrawl->children[index] = getNode(j);
			//printf(":checknonfail:");
		    pCrawl = pCrawl->children[index];
		} else if (pCrawl->children[index] && pCrawl->value >=500 ) {
			 pCrawl = pCrawl->children[index];
		} else {
			skip=1;
		}
	
	word = strtok (NULL, " ");

	} while (word != NULL);

	if(!skip) { // for items that dont have a subset with high enough support- skip
		int k;
		for (k=0; k<=pCrawl->itemIndex;k++) {

			if(strcmp(temp,pCrawl->items[k].itemset) == 0) { //ItemSet exists, skip
				done = 1;
				*duplicate=1;
			}
		}

		if(!done) { // just trying to create items that dont already exist

			strcpy(pCrawl->items[pCrawl->itemIndex].itemset,temp);
			pCrawl->items[pCrawl->itemIndex].count=0;
			pCrawl->itemIndex+=1;
		}
	}
}


// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(trie_t *pTrie, char *key[], int arrIndex , ItemSet *table, int *tableIndex ,int supportCount , int j) {

	int i = 0;
	while(i< arrIndex) {

		int index;
		trie_node_t *pCrawl;
	 
		pTrie->count++;
		pCrawl = pTrie->root;

		char * word;
		char buffer[MAXTRANSACTIONSIZE*5];

		strcpy(buffer,key[i]);
		
		word = strtok(buffer, " ");
		
		do {
			//test if taking out atoi(word) makes difference
			if(word == NULL || atoi(word)==0 ) { 
				break;
			}
			index = CHAR_TO_INDEX(word);
			if( !pCrawl->children[index] ) {
			    pCrawl->children[index] = getNode(j);
			}
	 		pCrawl->value +=1;
			pCrawl = pCrawl->children[index];
			word = strtok (NULL, " ");

		 } while (word != NULL);
		
			// mark last node as leaf
		pCrawl->value +=1;
		
		int done =0;
		int k;
		for (k=0; k<=pCrawl->itemIndex;k++) {
			if(strcmp(key[i],pCrawl->items[k].itemset) == 0) { //ItemSet exists, up counter
				pCrawl->items[k].count+=1;
				if (pCrawl->items[k].count == supportCount) {
				ItemSet t;
				strcpy(t.itemset,key[i]);
				t.count = pCrawl->items[k].count;
				//printf("found one : %s\n",t.itemset,key[i]);
				table[*tableIndex]= t;
     				 *tableIndex+=1;
				}
				done = 1;
			}
		}
		if(!done) {
			strcpy(pCrawl->items[pCrawl->itemIndex].itemset,key[i]);
			pCrawl->items[pCrawl->itemIndex].count+=1;
			pCrawl->itemIndex+=1;
		}
	i++;	  	
	}

return;
}
 
// Returns support count, if key presents in trie
int search(trie_t *pTrie, char *key) {	
	int index;
	trie_node_t *pCrawl;
	pCrawl = pTrie->root;
	char * word;
	char buffer[50];
	strcpy(buffer,key);
    	word = strtok (buffer, " ");

	do {
		if(word == NULL || atoi(word)==0 ) { 
			break;
		}
		index = CHAR_TO_INDEX(word);
		if( !pCrawl->children[index] ) {
		   return 0;
		}
		pCrawl = pCrawl->children[index];
		word = strtok (NULL, " ");
	} while (word != NULL);

	int k;
	for (k=0; k<pCrawl->itemIndex;k++) {
		
		if(strcmp(key,pCrawl->items[k].itemset) == 0) {
			return pCrawl->items[k].count;
		}
	}
    	return (0);
}

void freeNodes(trie_node_t *Node) {
	int i;
	for(i=0; i<ALPHABET_SIZE;i++){

		if( Node->children[i] )
		{
			
		   freeNodes(Node->children[i]);
		}
	}
	free(Node);
}

void freeTree ( trie_t *pTrie) {
	trie_node_t *pCrawl;
	pCrawl = pTrie->root;
	freeNodes(pCrawl);
  }

/******************************-Line Search-******************************************/

void lineSearch(char*list[],int listCounter, ItemSet *candTable, int *candIndex, int itemSetSize, trie_t *trie, int supportCount,ItemSet *table, int *tableIndex) {
	//candTable is the table of itemsets we are searching for to keep the count of
	int i=0;

	while(i<*candIndex)  {

		char buffer[MAXTRANSACTIONSIZE*5];
	
		strcpy(buffer,candTable[i].itemset);
		//printf("checking: %s target: %d\n",candTable[i].itemset,itemSetSize);
		char *save;
		
		save= strtok(buffer, " ");

		char *charArray[MAXTRANSACTIONSIZE];
		int w;
		for(w=0;w<MAXTRANSACTIONSIZE;w++){
			charArray[w]=malloc(4);
		}		
	
		int charCounter =1;
		charArray[0]=save;

		while((save= strtok(NULL, " "))!=NULL) {
		
			strcpy(charArray[charCounter],save);
			
			charCounter++;
		}
	
		//charArray is the array of items that make up the candItem set to keep count of

		int compareCount=0;
		//follow through line searching for item match
		int qq=0;
		while( qq<listCounter) {

			int candidate=1;
			if(strcmp(charArray[compareCount],list[qq])==0){ // do i need a target restriction
			/*found first item match*/
		
				compareCount++;
				qq++;
				while(qq<listCounter && compareCount<=itemSetSize) {
				
					if(strcmp(charArray[compareCount],list[qq])==0){
				
					candidate+=1;
					compareCount++;
					}
					qq+=1;
				
				}
				
				if(candidate==itemSetSize) {
		
				char **arr= malloc(*candIndex*16*(itemSetSize+1));
				arr[0]=malloc(16*(itemSetSize+1));
				strcpy(arr[0] , candTable[i].itemset);
				int arrIndex =1;
				insertIF( trie, arr, arrIndex , table, tableIndex , supportCount ,itemSetSize); 
				free(arr);
				break;
					
				}
				
			}
			compareCount=0;
			qq++;
			if(candidate==itemSetSize) {
				break;
			}
		}
		i++;
		
		
		
	}
	//insertIF(trie, char *key[], int arrIndex , ItemSet *table, int *tableIndex ,int supportCount , int j) 
}

void combinationUtil(char *list[], char *data[], int start, int end, int index, int r, char *arr[], int* arrIndex, trie_t *trie);
/*************************************************************************/

// The main function that prints all combinations of size r
// in arr[] of size n. This function mainly uses combinationUtil()
void printCombination(char *list[], int n, int r, char *arr[] ,int* arrIndex, trie_t *trie) {
	
    // A temporary array to store all combination one by one
    char *data[r];
    // -idea-sort backwards to eliminate a bunch

    // Print all combination using temprary array 'data[]'
    combinationUtil(list, data, 0, n-1, 0, r, arr, arrIndex,trie);
	return ;
}
/******************************-Combinations-******************************************/

/* arr[]  ---> Input Array
   data[] ---> Temporary array to store current combination
   start & end ---> Staring and Ending indexes in arr[]
   index  ---> Current index in data[]
   r ---> Size of a combination to be printed */
void combinationUtil(char *arr[], char *data[], int start, int end, int index, int r, char *arrr[], int* arrIndex, trie_t *trie) {
 
   char *combination = (char *) malloc(sizeof(char)*r*4);

    // Current combination is ready to be printed, print it
    if (index == r)  {	
	int j = 0;
	int skip=0;
	if(r>=1){strcat(combination,data[j]);}
        for (j=1; j<r; j++){

           strcat(combination," ");
	   strcat(combination,data[j]);

		if(j==3)
		if(search(trie,combination)<500 && j+1!=r) {
			//printf("low count: %s r: %d\n",combination,r);
			skip=1;
			break;
		}
	}
	if(!skip) {
	     	arrr[(int)*arrIndex]= combination;
		*arrIndex += 1;
	}
        return ;
    }
    free(combination);
    // replace index with all possible elements. The condition
    // "end-i+1 >= r-index" makes sure that including one element
    // at index will make a combination with remaining elements
    // at remaining positions
    int i;
    for (i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];

	
        combinationUtil(arr, data, i+1, end, index+1, r, arrr, arrIndex,trie);
    }
}


/****************************-Permutate-********************************************/
void permutate(char* transaction[], int itemSetSize, trie_t *trie, ItemSet *table, int *tableIndex, int supportCount, int transactionID, ItemSet *candTable, int *candIndex) {   
	int counter =0;
	while(transaction[counter]!=NULL) {
		counter++;
	}

	

	if(itemSetSize==1) {
		//no need to combinate since its single item sets
	
		insert(trie, transaction, counter, table, tableIndex, supportCount, itemSetSize);
		
		char *arr[(int)pow(counter,2)];
       		int arrIndex = 0;
		
        	printCombination(transaction, counter, 2, arr, &arrIndex,trie);
		//printf("%d made: %d from %d comapred to %d\n",itemSetSize,arrIndex,(numerator/denominator)+1,*candIndex);
		insert(trie, arr, arrIndex, table, tableIndex, supportCount, 2);
		
	} else {
		int l; int numerator =1; int denominator = 1;
		for(l=0;l<itemSetSize;l+=1) {
			numerator *=(counter-l);
			denominator*=(l+1);
		}
		
		if(*candIndex>(numerator/denominator)+1) {
			char *arr[(int)(numerator/denominator)+1];

		       	int arrIndex = 0;

			printCombination(transaction, counter, itemSetSize, arr, &arrIndex,trie);
			//printf("%d made: %d from %d comapred to %d\n",itemSetSize,arrIndex,(numerator/denominator)+1,*candIndex);
			insertIF(trie, arr, arrIndex, table, tableIndex, supportCount, itemSetSize);
		} else {
		//printf("using line search\n");
		lineSearch(transaction,counter,candTable, candIndex, itemSetSize, trie, supportCount, table, tableIndex);
		}
	}

}

/****************************-Self Join-*********************************************/
// dont need candtable and candcount anymore if work
void selfJoin(ItemSet *table, int *tableIndex, int target,ItemSet *candtable, int *candCounter,trie_t *trie) {
	

	int i=0;
	while(i<*tableIndex)  {
		//printf("\n-------------------i = %d--------------------------\n", i); 
		char buffer[MAXTRANSACTIONSIZE*5];
	
		strcpy(buffer,table[i].itemset);
		
		char *save;
		
		save= strtok(buffer, " ");

		char *charArray[MAXTRANSACTIONSIZE];
		int w;
		for(w=0;w<MAXTRANSACTIONSIZE;w++){
			charArray[w]=malloc(4);
		}		
	
		int charCounter =1;
		charArray[0]=save;

		while((save= strtok(NULL, " "))!=NULL) {

		strcpy(charArray[charCounter],save);
			
		charCounter++;
		}

		int compareCount=0;
		int qq=i+1;
		while( qq<*tableIndex) {
			//printf(" q = %d ", qq); 
			char * strptr;
			strcpy(buffer,table[qq].itemset);
			save= strtok_r(buffer, " ",&strptr);
			//comapre first item
			if(strcmp(charArray[compareCount],save)==0 && compareCount<target){
				char temp[MAXTRANSACTIONSIZE*5];
				strcpy(temp,save); // save the first char they share
				
				int candidate=1;
				compareCount++;
				while((save= strtok_r(NULL, " ",&strptr))!=NULL && compareCount<target-2) {
								
					if(strcmp(charArray[compareCount],save)==0){
					strcat(temp," "); strcat(temp,save);
	
					compareCount++;
					continue;
					} else {
					candidate=0;
					}
					
				}
				if(candidate==1) {
						int duplicate=0;
						if(strcmp(charArray[compareCount],save)>0) {
							//printf("1:  chararray: %s save: %s\n",charArray[compareCount],save);
							strcat(temp," ");
							strcat(temp,save);
							if(search(trie,temp)>499 ) {
							/* insert takes in tmp and places in trie only if k-1 is frequent*/
								strcat(temp," ");
								strcat(temp,charArray[compareCount]);
								
								insertSingle(trie, temp,target-1,&duplicate);
								if(duplicate==0) {
									strcpy(candtable[*candCounter].itemset,temp);
									*candCounter+=1;
								}
							} 
							
						} else {
							//printf("2:  chararray: %s save: %s\n",charArray[compareCount],save);
							strcat(temp," ");
							strcat(temp,charArray[compareCount]);
							if(search(trie,temp)>499 ) {
							/* insert takes in tmp and places in trie only if k-1 is frequent*/
								strcat(temp," ");
								strcat(temp,save);
								insertSingle(trie, temp,target-1,&duplicate);
								if(duplicate==0) {
									strcpy(candtable[*candCounter].itemset,temp);
									*candCounter+=1;
								}
							} 
					
						}
					
				}
				
			}
			compareCount=0;
			qq+=1;
		}
		i+=1;	
	}
//printf("candCounter: %d item: %s \n",*candCounter,candtable[*candCounter-1].itemset);

//printf("candCounter: %d \n",*candCounter);

}
/****************************-Generate and Print-*********************************************/

void generateCandidates(trie_t *trie, ItemSet *table, int *tableIndex,int j,ItemSet *candTable, int *candIndex, int *done,char *fileOutput,FILE **outPTR) {
	
	ItemSet *newTable= (ItemSet*)malloc(10000*(j+1)* sizeof(ItemSet));
	if(j==2) {
		
		int i;
		int newCounter =0;
		
		for(i=0;i<*tableIndex;i++) {
			char buffer[MAXTRANSACTIONSIZE*5];
			strcpy(buffer,table[i].itemset);
			char *save;
			save= strtok(buffer, " ");
			save= strtok(NULL, " ");
		
			if(!save) {
			//single item	
				sprintf(buffer,"%s (%d) \n",table[i].itemset,search(trie,table[i].itemset));
				fputs(buffer,*outPTR);
			} else {	
				strcpy(newTable[newCounter].itemset,table[i].itemset);
				
				sprintf(buffer,"%s (%d) \n",table[i].itemset,search(trie,table[i].itemset));
				fputs(buffer,*outPTR);
				newCounter+=1;
			}
		} // end for through table
		//printf("starting selfjoin\n");
		//items that are 2 item frequent combinations go to newTable
		
		if(newCounter==0){*done=1; return;}
		//printf("j: %d  done: %d \n",j,*done);
		selfJoin(newTable,&newCounter,3,candTable, candIndex, trie);
		/*candidates have been added to trie*/
		//cand table should be empty
		
	} else {
		int i;
		
		for(i=0;i<*tableIndex;i++) {
			char buffer[MAXTRANSACTIONSIZE*5];
			sprintf(buffer,"%s (%d) \n",table[i].itemset,search(trie,table[i].itemset));
			fputs(buffer,*outPTR);
			
		} // end for through table
	//printf("j: %d  done: %d \n",j,*done);
	
	if(*tableIndex==0){*done=1; return;}
	//printf("22222j: %d  done: %d \n",j,*done);
	selfJoin(table,tableIndex,j+1,candTable, candIndex, trie);
	//printf("candCounter: %d \n",*candIndex);

	}

	//fclose(*outPTR);
}
/****************************-Main-*******************************************/

void main(int argc, char *argv[]) {
	
	clock_t start, lap, end;
     	double cpu_time_used;
      
     	start = clock();

	if(argc != 4) {printf("need only 3 params, got %d - Allen\n", argc-1); return; }
	char *fileInput = argv[1];// argv[0] = dataset file name

	int supportCount = atoi(argv[2]); // argv[1] = support count

	char *fileOutput = argv[3]; // argv[2] = output file name

	int done = 0;
	FILE * fp;
	char buffer[200];
	if ((fp = fopen(fileInput, "r+")) == NULL) {                            
	      printf("Unable to open file\n");                                          
	      exit(1);                                                                  
	}
	
	FILE *outPTR= fopen(fileOutput, "w+");
	if ( outPTR == NULL) {                            
	      printf("Unable to open file\n");                                          
	      exit(1);                                                                  
	}  

	int newCounter=0;
	ItemSet *newTable;

	trie_t trie;
	initialize(&trie);
	
	char ***allTransaction= (char ***)malloc(MAXTRANSACTIONS*MAXTRANSACTIONSIZE*8);
	int y;
	for(y=0;y<MAXTRANSACTIONS;y+=1) {
		allTransaction[y] =(char **)malloc(MAXTRANSACTIONSIZE*8);
		//memset(allTransaction[y],0,sizeof(allTransaction[y]));
		int u;
		for(u=0;u<MAXTRANSACTIONSIZE;u+=1) {
			allTransaction[y][u]=malloc(8);
			//allTransaction[y][u]=NULL;
		}
	}
//for more dynamic need a while statment here and a counter to keep track of # transactions
	for(y=0;y<MAXTRANSACTIONS;y+=1) {
			//printf(" y: %d\n",y);
			while( fgets(buffer,200,fp)!= NULL) {
				//printf("saving: %s in %d\n",buffer, y);

				char *word;
				
				word = strtok (buffer, " ");
				strcpy(allTransaction[y][0],word);

				int counter =1;
	
				do {
					word = strtok (NULL, " ");
					if(word == NULL || atoi(word)==0) { 
						break;
					}
					//printf("++saving: %s in %d size:%d\n",word, counter,sizeof(word));
					strcpy(allTransaction[y][counter],word);
					counter++;
				} while (word != NULL);		
				while(counter!=MAXTRANSACTIONSIZE) {
					allTransaction[y][counter]=NULL;
					counter++;
				}
				break;

			}	
	}


	lap = clock();
     	cpu_time_used = ((double) (lap - start)) / CLOCKS_PER_SEC;
	printf("LAP setting in memory: %lf \n", cpu_time_used );
	
	int j=1;
	//for (j=1; j< 6; j++) {
	while(!done) {

		int transactionID =0;

		ItemSet *table; 	
		table = (ItemSet*)malloc((MAXTRANSACTIONS/20)* sizeof(ItemSet));
		
		int tableIndex =0;
	
		int trans = 0;
		while(trans<MAXTRANSACTIONS) {
	
			permutate(allTransaction[trans], j, &trie, table, &tableIndex, supportCount,transactionID, newTable,&newCounter);
			
			/* permuatations have been added to the trie */

			transactionID+=1;

			if(transactionID%25000==0)
			printf("j: %d id: %d \n",j,transactionID);

			trans+=1;
		}
		
		//table should have all itemsets above support count

		//------ clean clean transactions! -----//
		
		if(j==1 && supportCount<1001){
		//printf("cleaning...\n");
			trans =0;
			while(trans<MAXTRANSACTIONS) {
			
				int counter =0;
			
				while(allTransaction[trans][counter]!=NULL) {

					if(search(&trie, allTransaction[trans][counter])<supportCount){ 
						
						int k=counter;
						while(k<MAXTRANSACTIONSIZE && allTransaction[trans][k+1]!=NULL) {
							strcpy(allTransaction[trans][k],allTransaction[trans][k+1]);
							k+=1;
						}
						allTransaction[trans][k]=NULL;

					}
				counter++;
				}

				//if(trans%25000==0)
				//printf("Cleaning: %d \n",trans);

				trans+=1;
			}
		j+=1;
		}
	/********* generate candidate items and print *************/
	//if(j==1){ j++;}


		if(j>2){ free(newTable);}
		
		//was used for candidate table if im correct
		newCounter=0;
		newTable= (ItemSet*)malloc((MAXTRANSACTIONS/10)*(j+1)* sizeof(ItemSet));
		//printf("pre-gen-cand j: %d  done: %d tableIndex: %d\n",j,done,tableIndex);
	
		generateCandidates( &trie, table, &tableIndex, j,newTable ,&newCounter,&done,fileOutput,&outPTR);
		//printf("newCounter: %d \n",newCounter);
		printf("%d:---------------- %d done: %d \n",j,tableIndex,done);
		/* table index now has the item candidates */
	
		
		rewind(fp);
		lap = clock();
     		cpu_time_used = ((double) (lap - start)) / CLOCKS_PER_SEC;
		
		printf("LAP: %lf \n", cpu_time_used );
		
		free(table);

	j+=1;
	}
	fclose(outPTR);
	fclose(fp);
    	end = clock();
     	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time: %lf \n", cpu_time_used );
}
