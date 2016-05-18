/*THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - ALLEN HERRERA */

#include <signal.h>
#include <errno.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define KEY (key_t) 83938	/*key for shared memory segment */

struct process {  /* definition of new type "process" */
	int pid;
  	int tested;
	int skipped;
	int found;       
      };

 struct memshare {
	int managePid;
	int bitmap[8000];
	int perfectNumbers[20];
	struct process processArray[20];
};

//message queue key
	//types 1 = manage: add compute pid
	//	2 = manage: add magic number
	//	5 = compute: read assigned offset for process structure row

main(int args, char *argv[]) {

	int sid;	/* segment id of shared memory segment */
	struct memshare * array;	/* pointer to shared array, no storage yet*/
	int qid;	/* message queue id */
	
	struct  {
		long type;
		int data;
		} my_msg;
		
	/* create queue if necessary */
	if ((qid=msgget(KEY,IPC_CREAT |0660))== -1) {
		perror("msgget");
		exit(1);
		}
//printf("size: %d\n",sizeof(struct memshare));
	/* create shared segment if necessary */
	if ((sid=shmget(KEY,sizeof(struct memshare),IPC_CREAT |0660))== -1) {
		perror("shmget");
		exit(1);
		}

	/* map it into our address space*/
	if ((array=((struct memshare *) shmat(sid,0,0)))== (struct memshare *)-1) {
		perror("shmat");
		exit(2);
		}
	
	if (args>1 && strcmp(argv[1],"-k") == 0) {

		kill(array->managePid,SIGINT);
		
		exit(1);
	} else { 
		int offset = 0;
		printf("----------------------------------------\n");
		while(array->processArray[offset].pid!=0 && offset<20) {

			printf("Pid: %d  Tested: %d  Skipped: %d  Found: %d\n", array->processArray[offset].pid , array->processArray[offset].tested , array->processArray[offset].skipped , array->processArray[offset].found);
			
				offset+=1;
			}
		int n = 2;
		int counter = 0;
		while(n<256002) {

			if ((array->bitmap[((n-2)/32)]|1<<((n-2)%32)) == array->bitmap[((n-2)/32)]){
				counter++;
			}
		n++;
		}
		printf("----------total tested: %d------------\n",counter);
		
		exit(1);
	}
	
}
