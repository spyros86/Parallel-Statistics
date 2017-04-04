/* 
 * File:  searcher.c
 * Author: Spyros Vlachos
 * Created on December 9, 2011, 9:32 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "definitions.h"
#include "secondary_functions.h"
#include <sys/times.h>


int main(int argc, char** argv)
{
	int depth;
	int fd_UP;

	char msg[READSIZE];
	int i;
	int c;
	int start, end;
	int block;
	int ar_pediou;
	FILE *fp;
	record rec;
	int numberofrecs;
	char pedio_arxeiou[20];
	int pedio_arxeiou_num;
	int timh_num;
	double t1, t2, cpu_time;
	struct tms tb1, tb2;
	double ticspersec;
	
	
	ticspersec = (double) sysconf(_SC_CLK_TCK);
	
	
	// argv[x]
	//  1		2        3				4 			5			 6			7		    8		9
	//depth, pipe, aukswn_arithmos, blocksize, RECORDFILE,arithmos_pediou, telesths, timh, numofrecs
	
	
	depth = atoi(argv[1]);
	
	fd_UP = open(argv[2],O_WRONLY); //anoigw to pipe pros ta epanw.
	if(fd_UP < 0)
	{
		perror("open error searcher");
		exit(1);
	}
	
	
	
	c = atoi(argv[3]); //arithmos pou xrhsimopoiw gia na parw to diasthma anazhthshs
	block = atoi(argv[4]);
	ar_pediou = atoi(argv[6]);
	numberofrecs = atoi(argv[9]);
	
	
	start = c * block;
	if(c!=0) //gia na mhn arxizw apo thn teleutaia tou prohgoumenou alla apo +1;
		start+=1;
	end = (c+1) * block +1;
	if(end>numberofrecs) //epeidh pairnw to ceil twn records ana searcher, bgainw sto telos me liga pio polla. opote ta kobw.
		end = numberofrecs;
	
	//printf("*Searcher process %d Depth of tree= %d c: %d start: %d end: %d\n",getpid(),depth,c,start,end);
	//printf("File: %s AP: %d TEL: %s TIMH: %s\n",argv[5],ar_pediou,argv[7],argv[8]);
	//printf("start: %d end: %d end-start: %d\n",start,end,end-start);
	
	fp =  FILE_OPEN_FILE(argv[5],"rb"); //anoigw to arxeio
	
	
	//ksekinw xronometrhsh
	t1 = (double) times(&tb1);
	
	
	fseek(fp,(start)*sizeof(record),SEEK_SET);//paw apo thn arxh tou arxeiou sto shmeio pou thelw na psaksw
	
	
	for(i=0;i<(end-start);i++)
	{
		fread(&rec,sizeof(record),1,fp);
		
		if(ar_pediou == 1)
		{
			pedio_arxeiou_num = rec.id;
		}
		else if (ar_pediou == 2)
		{
			sprintf(pedio_arxeiou,"%s",rec.firstName);
		}
		else if (ar_pediou == 3)
		{
			sprintf(pedio_arxeiou,"%s",rec.lastName);
		}
		else if (ar_pediou == 4)
		{
			pedio_arxeiou_num = rec.age;
		}
		else if (ar_pediou == 5)
		{
			sprintf(pedio_arxeiou,"%s",rec.job);
		}
		else if (ar_pediou == 6)
		{
			pedio_arxeiou_num = rec.salary;
		}
		else if (ar_pediou == 7)
		{
			printf("Lathos pedio!!!\n");
			exit(1);
		}
		
		if((ar_pediou == 2) || (ar_pediou == 3) || (ar_pediou == 5)) //compare gia string values
		{	
			if(COMPARE(argv[7],pedio_arxeiou,argv[8]))
			{
				sprintf(msg,"%d %s %s %d %s %d",rec.id, rec.firstName, rec.lastName, rec.age, rec.job, rec.salary);
				write(fd_UP,msg,READSIZE);
			}
		}
		else //compare gia numbers
		{
			timh_num = atoi(argv[8]);
			if(COMPARENUM(argv[7],pedio_arxeiou_num,timh_num))
			{
				sprintf(msg,"%d %s %s %d %s %d",rec.id, rec.firstName, rec.lastName, rec.age, rec.job, rec.salary);
				write(fd_UP,msg,READSIZE);
			}
		}	
		
		
		
	}
	
	t2 = (double) times(&tb2);
	
	cpu_time = (double) ((tb2.tms_utime + tb2.tms_stime) - (tb1.tms_utime + tb1.tms_stime));
	
	
	//printf("SEARCHER %d STATS\n",getpid());
	sprintf(msg,"__STATS %.2lf %.2lf",(t2-t1)/ticspersec, cpu_time/ticspersec);
			write(fd_UP,msg,READSIZE);
	
	close(fd_UP);
	FILE_CLOSE_FILE(fp);
	//printf("searcher %d\n",getpid());
	exit(100);
}
