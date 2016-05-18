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

 struct memshare { //shared memory struct
	int managePid;
	int bitmap[8000];
	int perfectNumbers[20];
	struct process processArray[20];
};
	int myRow;		/* index in process array table */
	struct memshare *array;	/* pointer to shared array, no storage yet*/

//message queue key
	//types 1 = manage: add compute pid
	//	2 = manage: add magic number
	//	5 = compute: read assigned offset for process structure row

main(int args, char *argv[]) {

	int sid;	/* segment id of shared memory segment */
	int qid;	/* message queue id */

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

	struct  {
		long type;
		int data;
		} my_msg;
		
	/* connect to queue */
	if ((qid=msgget(KEY,IPC_CREAT |0660))== -1) {
		perror("msgget");
		exit(1);
		}

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

	//get my row info
	my_msg.type= 1;
	my_msg.data=getpid();
	msgsnd(qid,&my_msg,sizeof(my_msg.data),0);
	msgrcv(qid,&my_msg,sizeof(my_msg.data),5,0);
	myRow = my_msg.data;
	if(myRow>=20) {printf("\nCompute pid: %d exiting: too many computes running\n",getpid());exit(1);}
	int i,sum;

	int n= atoi(argv[1]);
	if (n<2) { n=2;}

	while (n<256002) {
		sum=1;
		//after or'ing with the bit pos set to one, if its changed that means the number wasnt turned on
		if((array->bitmap[((n-2)/32)]|1<<((n-2)%32)) != array->bitmap[((n-2)/32)]) {

			
			array->processArray[myRow].tested++;
			
			
			for (i=2;i<n;i++) {
				if (!(n%i)) sum+=i;
			}

		} else {
			array->processArray[myRow].skipped++;
		}
		//test if found magic number	    
		if (sum==n){
			
			
			my_msg.type= 2;
			my_msg.data=n;
			
			array->processArray[myRow].found++;
			msgsnd(qid,&my_msg,sizeof(my_msg.data),0);		

		}
		
		array->bitmap[((n-2)/32)] =array->bitmap[((n-2)/32)]|1<<((n-2)%32);
		
		n++;
		
	}
	
}

void cleanUp(signum) { 
	

	array->processArray[myRow].pid=0;
	array->processArray[myRow].tested=0;
	array->processArray[myRow].skipped=0;
	array->processArray[myRow].found=0;
	
	//printf("Compute pid:%d myRow:%d Shutdown Complete\n", getpid(),myRow);
	exit(1);

}
