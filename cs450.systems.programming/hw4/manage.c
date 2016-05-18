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

	int sid;	/* segment id of shared memory segment */
	struct memshare *array;	/* pointer to shared array, no storage yet*/
		
	int qid;	/* message queue id */

main() {
	struct  {
		long type;
		int data;
		} my_msg;
		
	/* create queue if necessary */
	if ((qid=msgget(KEY,IPC_CREAT |0660))== -1) {
		perror("msgget");
		exit(1);
		}
	//printf("created queue\n");


	void cleanUp();

	sigset_t mask;
	struct sigaction action;
	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGHUP);
	sigaddset(&mask, SIGQUIT);
	action.sa_flags=0;
	action.sa_mask=mask;
	
	action.sa_handler=cleanUp;
	sigaction(SIGINT,&action,NULL);
	sigaction(SIGHUP,&action,NULL);
	//action.sa_handler= 'other handler name';
	sigaction(SIGQUIT,&action,NULL);


	/* create shared segment if necessary */
	if ((sid=shmget(KEY, sizeof(struct memshare),IPC_CREAT |0660)) == -1) {
		perror("shmget");
		exit(1);
		}

	/* map it into our address space*/
	if ((array=((struct memshare *) shmat(sid,0,0)))== (struct memshare *)-1) {
		perror("shmat");
		exit(2);
		}
	array->managePid = getpid();
	//loop through waiting for messages via message queue until signal to break and shutdown
	//types 1 = manage: add compute pid
	//	2 = manage: add magic number
	//	5 = compute: read assigned offset for process structure row

	while(1) {
		
		//printf("searching for messages\n");
		msgrcv(qid,&my_msg,sizeof(my_msg.data),1,IPC_NOWAIT );
		if (my_msg.type == 1) {

			int offset=0;
			while(offset<20 && array->processArray[offset].pid!=0) {
				offset+=1;
			}
			if(offset<20) {
				
				array->processArray[offset].pid = my_msg.data;
			
			} 

			my_msg.type= 5;
			my_msg.data=offset;
			msgsnd(qid,&my_msg,sizeof(my_msg.data),0);

		} 

		msgrcv(qid,&my_msg,sizeof(my_msg.data),2,IPC_NOWAIT );
		if (my_msg.type == 2) {
			//printf("Manage: recieved message type: 2 number: %d  pid:%d \n",my_msg.data,my_msg.pid);
			int j=0;
			int flag =0;
			while(array->perfectNumbers[j]!=0 && j<20) {
				if (array->perfectNumbers[j]==my_msg.data) {
					//duplicate magic number found - flag it
					flag =1;
					break;
				}
			j++;
			}

			if(flag) {
				//printf("Manage: recieved duplicate magic num: %d from pid: %d\n",my_msg.data,my_msg.pid);	
			} else { 
				//new perfect number!
				array->perfectNumbers[j]=my_msg.data;
			}

	
		}
		my_msg.type = 0;
	}
	
}

void cleanUp(signum) { 
	printf("\n cleaning up \n");
/*	if (signum == SIGINT) printf("Interrupt \n");
	if (signum == SIGHUP) printf("Hup \n");
	if (signum == SIGQUIT) printf("Quit \n");
*/
	int j = 0;
	while(array->processArray[j].pid!=0 && j<20) {
		
		//printf("killing pid: %d\n",array->processArray[j].pid);
		kill(array->processArray[j].pid,SIGINT);
		if(array->processArray[j+1].pid == 0 && array->processArray[j+2].pid!= 0) { j+=1;}
		j+=1;
	}

	printf("sleeping for 5...\n");

	sleep(5);
	if (shmdt(array) == -1) {
		perror("shmdt\n");
		exit(3);
	}
	if (shmctl(sid,IPC_RMID,0) == -1) {
		perror("shmctl\n");
		exit(3);
	}
// maybe msgctl doesnt need 0
	if (msgctl(qid,IPC_RMID,0) == -1) {
		perror("shmctl\n");
		exit(3);
	}
	printf("done\n");
	exit(1);

}
