void lineSearch(char*list[],int listCounter,ItemSet *table,int *tableIndex,ItemSet *candTable, int *candIndex, int itemSetSize) {
	
	int i=0;
	while(i<*candIndex)  {
		if(i%10000==0)
		printf("i: %d\n",i);
		char buffer[150];
	
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
		//printf("again checking999: \n");
	//	int g;
	//	for(g=0;g<charCounter;g+=1) {
	//	printf("%s-",charArray[g]);
	//	}
		//printf("made it\n");
		int compareCount=0;
		//follow through line searching for item match
		int qq=0;
		while( qq<listCounter) {
			//char * strptr;
			//strcpy(buffer,table[qq].itemset);
			//save= strtok_r(buffer, " ",&strptr);
			//comapre first item
			int candidate=1;
			if(strcmp(charArray[compareCount],list[qq])==0){ // do i need a target restriction
			/*found first item match*/
		
				//char temp[150];
				//strcpy(temp,save);
				//printf("they are the same %s  | %s count: %d\n",charArray[compareCount],list[qq],compareCount);
				
				compareCount++;
				qq++;
				while(qq<listCounter && compareCount<=itemSetSize) {
					//printf("CC count: %d ",compareCount);
					//printf("not here\n");
					//strcat(temp," "); strcat(temp,save);
					
				
					if(strcmp(charArray[compareCount],list[qq])==0){
					//printf("+++CHECK %s  | %s count: %d ++++\n",charArray[compareCount],list[qq],compareCount);
					candidate+=1;
					}
					qq+=1;
					compareCount++;
				}
				/*	if(candidate!=1){
					printf("\ncand value: %d tried matching:cand- %s    \nfrom:",candidate,candTable[i].itemset);
					int g;
					for(g=0;g<listCounter;g+=1) {
					printf("%s ",list[g]);
					}
					printf(" \n");
					}   */
				if(candidate==itemSetSize) {
					//printf("cand: %s qq: %d CCcount: %d i: %d imax: %d\n list:",candTable[i].itemset,qq,compareCount,i,*candIndex);
				//	int g;
				//	for(g=0;g<listCounter;g+=1) {
				//	printf("%s ",list[g]);
				//	}
				//	printf(" \n\n");
					   
					candTable[i].count+=1;
					if(candTable[i].count==500){

						strcpy(table[*tableIndex].itemset,candTable[i].itemset);
						*tableIndex+=1;
					}
					break;
					//printf("temp: %s candCounter: %d i:%d \n\n",temp,*candCounter,i);
					//strcpy(candtable[*candCounter].itemset, temp);
					//*candCounter+=1;
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
}

