/*THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - ALLEN HERRERA */

#include <sys/types.h> 
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <errno.h>
#include <ar.h>
#include <string.h>	
#include <utime.h>	

void appendFile( int archiveFD, char *file2) {
	
	struct stat statbuf;
	struct ar_hdr header1;
	
	if (stat(file2,&statbuf) == -1) {
		perror("stat");
		exit(1);
		}
	//set the header
	sprintf(header1.ar_name,"%s/", file2);
	sprintf(header1.ar_date,"%d",statbuf.st_mtime);
	sprintf(header1.ar_uid ,"%d", statbuf.st_uid);
	sprintf(header1.ar_gid,"%d",statbuf.st_gid);
	sprintf(header1.ar_mode,"%o", statbuf.st_mode);
	sprintf(header1.ar_size ,"%d", statbuf.st_size);
	sprintf(header1.ar_fmag  ,"`\n");
	
	char header[59];
	sprintf(header,"%-16s%-12s%-6s%-6s%-8s%-10s%-2s", header1.ar_name, header1.ar_date, header1.ar_uid, header1.ar_gid, header1.ar_mode, header1.ar_size, header1.ar_fmag);
	write(archiveFD,header,60);
	
	//set a proper buffer
	char buff [statbuf.st_blksize];
	int fd2 ,iosize;

	if ((fd2=open(file2,O_RDWR ,0666)) == -1) {
		perror("open2");
		printf("error in file: %s \n",file2);
		exit(1);
		}

	//set offset to end of thefile
	lseek(archiveFD,0,SEEK_END);
	int counter =0;
	while ((iosize=read(fd2,buff,sizeof(buff))) >0 ) {
		counter+=strlen(buff);
		write(archiveFD,buff,iosize);	
	}
	if (counter%2!=0) {
		//printf("its odd!!! adding a new line..\n");
		char temp[]="\n";
		write(archiveFD,temp,strlen(temp));
	}
	if (iosize == -1) {
		perror("read");
		exit(1);
		}
	
	close(fd2);
	
}

void extractNames( int archiveFD, char *file2) {
	char buff[15];
	int size;
	int test = lseek(archiveFD,8,SEEK_SET);
	while(read(archiveFD,buff,16)) {
		char *shortbuff;
		shortbuff = strtok(buff,"/");
		//search for the named file to extract
		if ( strcmp(file2,shortbuff) == 0) {
			struct ar_hdr newHead;
			struct stat statbuf;
			
			sprintf(newHead.ar_name,"%s", buff);
			
			read(archiveFD,buff,12);
			sprintf(newHead.ar_date,"%-12s",buff);
			
			read(archiveFD,buff,6);
			sprintf(newHead.ar_uid ,"%-6s", buff);
			
			read(archiveFD,buff,6);
			sprintf(newHead.ar_gid,"%-6s",buff);
			
			read(archiveFD,buff,8);
			sprintf(newHead.ar_mode,"%-8d", buff);
			int mode = atoi(buff);
			
			read(archiveFD,buff,10);
			int size = atoi(buff);
			char *biggerBuff[size+1];
			sprintf(newHead.ar_size ,"%s", buff);
			
			sprintf(newHead.ar_fmag  ,"`\n");
			lseek(archiveFD,2,SEEK_CUR);
			read(archiveFD,biggerBuff,size);
			
			//make the new file
			int newFileFD;
			if ((newFileFD=open(file2,O_CREAT | O_RDWR |O_TRUNC ,0666)) == -1) {
				perror("extract open failed! ");
				exit(1);
			}
			//recover the times
			struct utimbuf newt;
			newt.actime =  *newHead.ar_date;
			newt.modtime = *newHead.ar_date;
			umask(mode);
			setreuid(*newHead.ar_uid,*newHead.ar_uid);
			setregid(*newHead.ar_gid,*newHead.ar_gid);
			if (utime(file2,&newt) == -1) {
				perror("utime");
				exit(1);
			}
			//write the content
			write(newFileFD,biggerBuff,size);
			
			close(newFileFD);
			break;
		}
		lseek(archiveFD,32,SEEK_CUR);
		read(archiveFD,buff,10);
		size = atoi(buff);
		
		if (size%2!=0) {
			int check = lseek(archiveFD,1,SEEK_CUR);
		}
		lseek(archiveFD,(2+size),SEEK_CUR);	 
	}

	
}
void printTable (int archiveFD) {
	char buff[15];
	int size;
	lseek(archiveFD,8,SEEK_SET);
	while(read(archiveFD,buff,16)) {
		//get rid of slash
		char *shortbuff;
		shortbuff = strtok(buff,"/");
		write(STDOUT_FILENO,shortbuff,strlen(shortbuff));
		printf("\n");
		lseek(archiveFD,32,SEEK_CUR);
		read(archiveFD,buff,10);
		//get the size to check if odd
		size = atoi(buff);
		if (size%2!=0) {
			int check = lseek(archiveFD,1,SEEK_CUR);
		}
		lseek(archiveFD,(2+size),SEEK_CUR);	
	}
}

void main(int argc, char *argv[]) {
	
	// argv[0] = letter which represents what prog to run
		char prog[strlen(argv[0]-2)];
		strncpy(prog,argv[0]+2,strlen(argv[0]));
		char *operation = argv[1];
	// argv[1] = file name1
		char *file1 = argv[2];
	// argv[2] = [optional] file name2
		
		char *file2 = argv[3];
	//open and create archive
	int fd1a;
	if ((fd1a=open(file1, O_CREAT | O_RDWR ,0666)) == -1) {
		perror("Archive Confirm failed ");
		exit(1);
		}
	lseek(fd1a,0,SEEK_END);
	//set the magic 8 only on first write
	if (lseek(fd1a,0, SEEK_CUR) == 0) {
		//only actually create on q
		if(strcmp(operation,"q")==0) {
			lseek(fd1a,0,SEEK_SET);
			char magic[8] = "!<arch>\n";
 			write(fd1a, magic, 8);
		} else {
			remove(file1);
			perror("Archive does not exist");
			close(fd1a);
			exit(1);
		}
		
	}
		
	if (strcmp(operation,"q") == 0) {
		int i =3;
		while(argv[i]!=NULL) {
			appendFile( fd1a , argv[i] );
			i++;
		}
		close(fd1a);
	} else if (strcmp(operation,"x") == 0){
		extractNames(fd1a,file2);
		close(fd1a);	
	} else if (strcmp(operation,"t") == 0){
		printTable(fd1a);
		close(fd1a);
	} else if (strcmp(operation,"v") == 0){
	
	} else if (strcmp(operation,"d") == 0){
	
	} else if (strcmp(operation,"A") == 0){
		DIR *dir;
		struct dirent *dp;
		dir = opendir(".");
		while ((dp = readdir(dir)) != NULL) {
			//ignore dot files, this prog itself and the archive. only ordinary
			if (dp->d_name[0] != '.' && dp->d_type == 8 && strcmp(dp->d_name, argv[2])!=0 && strcmp(dp->d_name, prog)!=0) {
       				//printf("adding: %s   type: %d\n", dp->d_name, dp->d_type);
				appendFile( fd1a , dp->d_name );
    			}
			
		}
		
	} else {
		printf("%s is not a valid command - Allen\n", operation);
		exit(1);
	}
	//printf("end of program\n");
}


