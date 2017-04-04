/* 
 * File:  main_node.c
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
#include <sys/wait.h>
#include <string.h>
#include <math.h>
#include "definitions.h"
#include "secondary_functions.h"



int main(int argc, char** argv)
{
	// 0 			1 				2			3		4					5		6
	//main_node snumofrecords, RECORD_FILE, sdepth, ok_arithmos_pediou, telesths, timh
	
	int depth;
	int fd;
	int status;
	pid_t pid;
	char input_buffer[READSIZE];
	char sdepth[10];
	char pipename[10];
	double stat1 = 0;
	double stat2 = 0;
	double stats1 = 0;
	double stats2 = 0;
	int ret_val;
	int num_AP;
	char sarg[15];
	char sarg2[15];	
	int expected = 0;
	int num_of_searchers;
	int NUM_OF_RECORDS;
	char block[10]; //posa tha diabazei o kathe searcher.
    int c = 0x0;
    char sc[10];
    FILE* fp;
    int counter = 0;
  
    
    NUM_OF_RECORDS = atoi(argv[1]);
    
    
    
   
    
	
	
	
	if(argc != 7)
		exit(1);
		
		
		
	depth = atoi(argv[3]);
	//printf("*Main process %d Depth of tree= %d snumrecs: %s file: %s AP: %s Tel: %s timh: %s \n",getpid(),depth,argv[1], argv[2], argv[4], argv[5], argv[6]);
	//printf("start: %s end: %s\n",start,end);
	
	
	num_of_searchers = pow(2,depth);
	
	expected = num_of_searchers * 4;
	

	sprintf(block,"%d",(int)ceil((float)NUM_OF_RECORDS/(float)num_of_searchers)); //tha koitaksw kapoia mia fora akoma alla de tha xasw kanena.
	
	sprintf(pipename,"pipe000");//ftiaxnw to onoma tou pipe.
	
	ret_val = mkfifo(pipename,0666);//ftiaxnw to pipe
	if((ret_val == -1) && (errno != EEXIST))
	{
		perror("Named pipe error. Main node");
		exit(1);
	}
	
	switch(pid=fork())
	{
		case -1:
			{
				perror("main fork");
				exit(1);
			}
		case 0:
			{
				sprintf(sdepth,"%d",depth);
				
				sprintf(sc,"%d",c);
				// 0 			1 				2		  3		    4					5		6
				//main_node	snumofrecords, RECORD_FILE, sdepth, ok_arithmos_pediou, telesths, timh
				// 0 			1 			   2		3			4		5		6					7		8
				//merger		pipe	 	block	    c	 RECORD_FILE, sdepth, ok_arithmos_pediou, telesths, timh
				
				if(execlp("./merger","merger",pipename,block,sc,argv[2],argv[3],argv[4],argv[5],argv[6],argv[1],NULL) < 0)
				{
					perror("MAIN EXEC");
					exit(1);
					
				}
				break;
			}
		default: //pateras
			{
				fd = open(pipename,O_RDONLY);
				if(fd < 0)
				{
					perror("open error main_node");
					exit(1);
				}
				
				
				fp = FILE_OPEN_FILE("_tmp_1234","w");
				
				while(read(fd,input_buffer,READSIZE))
				{
					if(strncmp(input_buffer,"__STATS",7)) 
					{
							fprintf(fp,"%s\n",input_buffer);
							//fprintf(stdout,"%s\n",input_buffer);
					}
					if(!strncmp(input_buffer,"__STATS",7)) 
					{
						sscanf(input_buffer,"%*s %lf %lf",&stat1,&stat2);
						//printf("Run time was: %.2lf sec (REAL TIME)\n although the CPU time was %.2lf sec (CPU time)\n",stat1,stat2);
				
						stats1+=stat1;
						stats2+=stat2;
						
					}
						
				}
				

				
				
				close(fd);
				FILE_CLOSE_FILE(fp);
				remove(pipename);
				
				while(waitpid(pid,&status,WNOHANG) == 0);
				
				if(WIFEXITED(status))
					if(WEXITSTATUS(status) != 100) //an den einai to anamenomeno exit status
						printf("Exit status from main merger %d was not normal: %d\n",pid,WEXITSTATUS(status));
						
				

				switch(pid=fork()) //exec to sort
				{
					case -1:
					{
						perror("main fork2");
						exit(1);
					}
					case 0:
					{	//Arithmos pediou = argv[4].
						num_AP = atoi(argv[4]);
						if((num_AP == 1)||(num_AP == 4)||(num_AP == 6)) //an einai pedio arithmitiko.
						{
							sprintf(sarg,"--key=+%d",num_AP);
							sprintf(sarg2,"-n");


							if(execlp("sort","sort",sarg2,sarg,"-o_sorted","_tmp_1234",NULL) < 0)
							{
								perror("MAIN sort EXEC");
								exit(1);
					
							}
							break;
						}
						else
						{
							sprintf(sarg,"--key=+%d",num_AP);
							if(execlp("sort","sort",sarg,"-o_sorted","_tmp_1234",NULL) < 0)
							{
								perror("MAIN sort EXEC");
								exit(1);
					
							}
							break;
						}		
						


						
						
					}
					default: //pateras
					{
						while(waitpid(pid,&status,WNOHANG) == 0);
						if(WIFEXITED(status))
							if(WEXITSTATUS(status) != 0) //an den einai to anamenomeno exit status
								printf("Exit status from sorter %d was not normal: %d\n",pid,WEXITSTATUS(status));
							
							
						
						
						
						break;
					}
					
				}
				
						//getchar();
						fp = FILE_OPEN_FILE("_sorted","r");
						printf("\n\n-----------------------------------------------------------------------\n\n");
						
						while(fgets(input_buffer,READSIZE,fp) != NULL )						
						{
							printf("%s",input_buffer);
							counter++;
							
						}
						printf("\n-----------------------------------------------------------------------\n");	
					
						printf("\nTotal records searched counter: %d\n\n",counter);	
						
						FILE_CLOSE_FILE(fp);
				
						printf("Median run time was: %.2lf sec (REAL TIME)\n although the median CPU time was %.2lf sec (CPU time)\n\n",stats1/num_of_searchers,stats2/num_of_searchers);
						
						
						
				
				
				
				break;
			}
	
	}
	
	
	return 0;
}
