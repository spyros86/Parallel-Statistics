/* 
 * File:  merger.c
 * Author: Spyros Vlachos
 * Created on December 9, 2011, 9:32 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>
#include <math.h>
#include "definitions.h"




int main(int argc, char** argv)
{
	// 0 			1 			   2		3			4		5		6					7		8		9
	//merger		pipe	 	block	    c	 RECORD_FILE, sdepth, ok_arithmos_pediou, telesths, timh, numofrecs
				
	
	
	
	int depth;
	int fd_UP;
	int fd_DOWN[2];
	int ret_val;
	char input_buffer[READSIZE];
	int status;
	pid_t pid[2];
	char sdepth[10];
	char pipename[2][20];
	int i;
	int id;
	
	char sc[10];
	int c;
	/*
	 * pipe argv[1]
	 * block argv[2]
	 * c argv[3]
	 * RECORD_FILE argv[4]
	 * sdepth argv[5]
	 * ok_arithmos_pediou argv[6]
	 * telesths argv[7]
	 * timh argv[8]
	 */
	
	depth = atoi(argv[5]);
	fd_UP = open(argv[1],O_WRONLY);//anoikse to panw pipe
	
	
	
	c = atoi(argv[3]);
	id = (int)getpid();
	sprintf(pipename[0],"pipe%d",id);//ftiakse pseuto monadika onomata gia 2 named pipes
	sprintf(pipename[1],"pipe%d",id + id);
	//printf("**Merger process %d realDepth of tree= %d block: %s \n",getpid(),depth,argv[2]);
	//printf("c= %d merger: %d pipename1: %s pipename2: %s realDepth of tree= %d\n",c,getpid(),pipename[0],pipename[1],depth);
	
	
	ret_val = mkfifo(pipename[0],0666);//ftiakse 2 pipes
	if((ret_val == -1) && (errno != EEXIST))
	{
		perror("Named pipe error. Main node");
		exit(1);
	}
	
	ret_val = mkfifo(pipename[1],0666);
	if((ret_val == -1) && (errno != EEXIST))
	{
		perror("Named pipe error. Main node");
		exit(1);
	}
	
	//printf("**Merger process %d realDepth of tree= %d block: %s \n",getpid(),depth,argv[2]);
	//printf("depth= %d pipe UP: %d DownW: %d DownR%d\n",depth,fd_UP,fd_DOWN[WRITE],fd_DOWN[READ]);
	if(depth >=0)
	{
		depth-=1;
		
		for(i=0;i<2;i++) //kane 2 fork
		{
							
			switch(pid[i]=fork())
			{
				case -1:
					{
						perror("merger fork");
						exit(1);
					}
				case 0: //paidi
					{
						if(depth == 0) //searcher an eimai katw katw. To depth einai to ypsos ousiastika...
						{
							if(i==0) //arithmish twn searcher gia na briskw ta diasthmata.
							{
								c <<= 1;
								c += 0x0;								
							}
							else if(i==1)
							{
								c <<= 1;
								c += 0x1;								
							}							 
							sprintf(sc,"%d",c);							
							sprintf(sdepth,"%d",depth);
							
							//printf("exec search: %s, %s, %s %s %s %s %s %s\n",sdepth,sfd,sc,argv[2],argv[4],argv[6],argv[7],argv[8]);		
							if(execlp("./searcher","searcher",sdepth,pipename[i],sc,argv[2],argv[4],argv[6],argv[7],argv[8],argv[9],NULL) < 0)//depth, pipe, aukswn arithmos, blocksize, RECORDFILE,arithmos pediou, telesths, timh
							{
								perror("merger EXEC search");
								exit(1);
								
							}
							break; //de tha ftasei pote edw.
						}
						else //merger					
						{
							sprintf(sdepth,"%d",depth);
							
							//printf("depth= %d pipe UP: %d DownW: %d DownR%d\n",depth,fd_UP,fd_DOWN[WRITE],fd_DOWN[READ]);
							
							// 0 			1 			   2		3			4		5		6					7		8		9
							//merger		pipe	 	block	    c	 RECORD_FILE, sdepth, ok_arithmos_pediou, telesths, timh, numofrecs							
							if(i==0) //arithmish twn merger. Metraei o arithmos mono otan depth ==1
							{
								c <<= 1;
								c += 0x0;
								
							}
							else if(i==1)
							{
								c <<= 1;
								c += 0x1;
								
							}
							 
							sprintf(sc,"%d",c);
							if(execlp("./merger","merger",pipename[i],argv[2],sc,argv[4],sdepth,argv[6],argv[7],argv[8],argv[9],NULL) < 0)
							{
								perror("merger EXEC merge");
								exit(1);
								
							}
							break; //de tha ftasei pote edw
						}
					}
				default: //pateras
					{//afou sta parapanw to poly poly na kanei exit, to default tou patera to afhnw keno kai ekmetaleuomai to oti bgainw apo to for apo katw  gia na kanw ta read.
						
						//an ekana edw klasika wait de tha mporousa na kanw read kai an ekana read tha pigainan oi searchears
						
						break;
					}
	
			}
		}
		
		
						fd_DOWN[0] = open(pipename[0],O_RDONLY); //anoigw ta 2 pipes gia diabasma
						if(fd_DOWN[0] < 0)
						{
							perror("open error merger_node0");
							exit(1);
						}
						fd_DOWN[1] = open(pipename[1],O_RDONLY);
						if(fd_DOWN[1] < 0)
						{
							perror("open error merger_node1");
							exit(1);
						}
						
						
						while(read(fd_DOWN[0],input_buffer,READSIZE)) //diabazw apo ta pipes.
						{						
								write(fd_UP,input_buffer,READSIZE);				
														
						}	
						while(read(fd_DOWN[1],input_buffer,READSIZE))
						{						
								write(fd_UP,input_buffer,READSIZE);				
														
						}				
						
												
						close(fd_DOWN[0]);//kleinw eisodo apo katw
						close(fd_DOWN[1]);//kleinw eisodo apo katw 2
						remove(pipename[0]);//remove ta named pipes.
						remove(pipename[1]);
						
						
						while(waitpid(pid[0],&status,WNOHANG) == 0); //kanw wait tous searchers kai tous mergers
						if(WIFEXITED(status))
						{			
							//printf("Exit status from searcher %d was %d\n",pid,WEXITSTATUS(status));
							if(WEXITSTATUS(status) != 100) //an den einai to anamenomeno exit status
								printf("Exit status from searcher or merger %d was not normal: %d\n",pid[0],WEXITSTATUS(status));
						}
						while(waitpid(pid[1],&status,WNOHANG) == 0); //kanw wait tous searchers kai tous mergers
						if(WIFEXITED(status))
						{			
							//printf("Exit status from searcher %d was %d\n",pid,WEXITSTATUS(status));
							if(WEXITSTATUS(status) != 100) //an den einai to anamenomeno exit status
								printf("Exit status from searcher or merger %d was not normal: %d\n",pid[1],WEXITSTATUS(status));
						}
							
		
						close(fd_UP);
	}

	
	
	
	
	
	exit(100);
	
}
