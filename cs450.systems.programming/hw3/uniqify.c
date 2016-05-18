/*THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - ALLEN HERRERA */

/*
In this version I have completed the extra-credit version as well,
with double pipes being written to, 2 sorting processes and then 
one suppressor that combines both pipes. I have a copy of my 
original non-extra credit version of this assignment saved as
uniqify.c under workspace/ in case that is needed.
*/

#include <sys/types.h> 
#include <fcntl.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

main(int argc, char **argv) {
	int i;  			/* generic counter */
	int pid[3];			/*pids of children */
	int pipefd[2];			/* fds for ends of pipe 1*/
	int pipe2fd[2];			/* fds for ends of pipe 2*/
	int pipe3fd[2];			/* fds for ends of pipe 3*/
	int pipe4fd[2];			/* fds for ends of pipe 4*/

	//make my 4 pipes
	if (pipe(pipefd) == -1) {
		perror("pipe1");
		exit(1);
	}
	if (pipe(pipe2fd) == -1) {
		perror("pipe2");
		exit(1);
	}
	if (pipe(pipe3fd) == -1) {
		perror("pipe3");
		exit(1);
	}
	if (pipe(pipe4fd) == -1) {
		perror("pipe4");
		exit(1);
	}
	
	//create my 3 children: 2 sorters, 1 supressor
	for (i=0; i<3; i++) {
		int save = dup(STDOUT_FILENO);
		if ((pid[i]=fork()) == -1) {
			perror("fork");
			exit (i+1);
			}
		
		if (pid[i] == 0) {
	
			/* this is the child */
			if (i==0) {  //sorter child 1
				//close immediately unused pipes
				close(pipe2fd[0]);
				close(pipe2fd[1]);
				close(pipe4fd[0]);
				close(pipe4fd[1]);

				//set standard in to be the read of pipe1
				dup2(pipefd[0],0);
				close(pipefd[0]);
				close(pipefd[1]);

				//set standard out to be the write of pipe3
				dup2(pipe3fd[1],1);
				close(pipe3fd[1]);
				close(pipe3fd[0]);

				execl("/bin/sort","sort",0);
				close(0);close(1);
			
				}
			if (i==1) { //sorter child 2
				//close immediately unused pipes
				close(pipefd[0]);
				close(pipefd[1]);
				close(pipe3fd[0]);
				close(pipe3fd[1]);

				//set standard in to be the read of pipe2
				dup2(pipe2fd[0],0);
				close(pipe2fd[0]);
				close(pipe2fd[1]);

				//set standard out to be the write of pipe4
				dup2(pipe4fd[1],1);
				close(pipe4fd[1]);
				close(pipe4fd[0]);
				
				execl("/bin/sort","sort",0);
				close(0);close(1);
			
				} 
			if (i==2) { /* suppress does this */
				
				FILE *pp;
				FILE *pp2;

				//open pipe3 and pipe4 for reading
				pp = fdopen(pipe3fd[0],"r");
				pp2 = fdopen(pipe4fd[0],"r");
				
				//close unused pipe endpoints
				close(pipefd[0]);
				close(pipefd[1]);
				close(pipe2fd[0]);
				close(pipe2fd[1]);
				close(pipe3fd[1]);
				close(pipe4fd[1]);
	
				char str[500];
				sprintf(str ,"");
				char str2[500];
				sprintf(str2 ,"");
				char prevWord[500];
				sprintf(prevWord ,"");
				int count=0;
				int stopFlag =0;
				int stopFlag2 =0;
				//stop condition if one of the pipes is empty
				while(stopFlag ==0 && stopFlag2==0){
					//if the word is a duplicate to the prevWord, discard and move on
					while(strcmp(prevWord,str) == 0 || strcmp(prevWord,str2) == 0  ){
						if(strcmp(prevWord,str) == 0 ) {
					
							if(fgets(str,500,pp)== NULL) {
			 
							
								stopFlag++;
								break;
							}
						}	
						if(strcmp(prevWord,str2) == 0 ) {	
							if(fgets(str2,500,pp2)== NULL) {
							
								stopFlag2++;
								break;
							} 
						}
						
					}
					
					//neither should be equal to prevword now
					int cmp = strcmp(str,str2);
					if(cmp < 0){cmp=-1;}
					if(cmp > 0){cmp=1;}
					
					switch (cmp) {
					    case -1  : //str is less than str2
					      printf("%d: %s",count, str);
					      count++;
					      sprintf(prevWord ,"%s",str);
					      if (fgets(str,500,pp)== NULL) {
					      	stopFlag++;
					      }
					      break; 
					    case 0  : //str and str2 are equal so print 1 but get 2 new words
					      if(strcmp(prevWord,str) != 0) {
						      printf("%d: %s",count, str);
						      count++;
						      sprintf(prevWord ,"%s",str);
					      }
					      if (fgets(str,500,pp)== NULL) {
					      	stopFlag++;
					      }
					      if (fgets(str2,500,pp2)== NULL) {
					      	stopFlag2++;
					      }
					      break; 
					    case 1  : //str2 is less than str1
					      printf("%d: %s",count, str2);
					      count++;
					      sprintf(prevWord ,"%s",str2);
					      if (fgets(str2,500,pp2)== NULL) {
					      	  stopFlag2++;
					      }
					      break; 
					}


				 }
				//since one of the pipes are empty, continue on with the other pipe
				if (stopFlag2 == 0) {
					if(strcmp(prevWord,str2) != 0) {
						printf("%d: %s",count, str2);
						count++;
						sprintf(prevWord ,"%s",str2);
					}
					while(fgets(str2,500,pp2)!= NULL ){ 
		
						while(strcmp(prevWord,str2) == 0){
							if(fgets(str2,500,pp2)== NULL) {
								stopFlag2++;
								break;
							} 
						}
						if (stopFlag2==0){	
							if(strcmp(prevWord,str2) != 0) {					
								printf("2%d: %s prev: %s",count, str2, prevWord);
								count++;
								sprintf(prevWord ,"%s",str2);
							}
						}
					}
				} else if (stopFlag == 0) {
					if(strcmp(prevWord,str) != 0) {
						printf("%d: %s",count, str);
						count++;
						sprintf(prevWord ,"%s",str);
					}
					while(fgets(str,500,pp)!= NULL ){ 
		
						while(strcmp(prevWord,str) == 0){
							if(fgets(str,500,pp)== NULL) {
								stopFlag++;
								break;
							} 
						}
						if (stopFlag==0){
							if(strcmp(prevWord,str) != 0) {						
								printf("%d: %s",count, str);
								count++;
								sprintf(prevWord ,"%s",str);
							}
						}
					}
				}
				//close pipes that were used now that we are done
				fclose(pp);
				close(pipe3fd[0]);
				fclose(pp2);
				close(pipe4fd[0]);
	
			}
		exit (0); /* either way exit */
		}
	} 

	//parent code	
	FILE *pp;
	FILE *pp2;

	//open pipe1 and pipe2 for writing
	pp = fdopen(pipefd[1],"w");
	pp2 = fdopen(pipe2fd[1],"w");

	//close unused pipe endpoints
	close(pipefd[0]);
	close(pipe2fd[0]);
	close(pipe3fd[0]);
	close(pipe3fd[1]);
	close(pipe4fd[0]);
	close(pipe4fd[1]);

	int buff;
	char word[100];
	sprintf(word ,"");
	int wordCount=0;

	while((buff=fgetc(stdin))!= EOF ) {
	
		//if uppercase, change to lowercase
		if ( buff >= 65 && buff <= 90) {
			sprintf(word ,"%s%c",word,(char)buff+32);
		} else if (buff >= 97 && buff <= 122) {
			sprintf(word ,"%s%c",word,(char)buff);
		} else {		
					
			if(strlen(word)>0) {
				//add new line char, sprintf add \0 on its own
				sprintf(word ,"%s\n",word);
				//put the word into the pipe
				if((wordCount%2)==0) {
					fputs(word,pp);	
					//printf("going in pipe1:%s ",word);
				} else {
					fputs(word,pp2);
					//printf("going in pipe2:%s ",word);	
				}
				wordCount++;
			}
			sprintf(word ,"");
		}
		
	}
	//close pipes so EOF can be read in children
	fclose(pp);
	close(pipefd[1]);
	fclose(pp2);
	close(pipe2fd[1]);

	int whom;	/* pid of dead child*/
	int status;	/* childs return status*/

	/* now parent waits */    
	waitpid(pid[0], &status, 0);  // Parent process waits here for child pid[i] to terminate.
	if(status == -1) printf("Error in sorting");
	waitpid(pid[1], &status, 0);
	if(status == -1) printf("Error in sorting2");
	waitpid(pid[2], &status, 0);
	if(status == -1) printf("Error in supressor");
	
	close(0);
	
}
