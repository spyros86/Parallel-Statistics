/* 
 * File:  secondary_functions.c
 * Author: Spyros Vlachos
 * Created on December 9, 2011, 9:32 PM
 */

#include "definitions.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

FILE* FILE_OPEN_FILE(char* RECORD_FILE, char* mode)
{

    FILE *fp; //deikths sto arxeio input
    if ((fp = fopen(RECORD_FILE, mode)) == NULL) //anoikse to arxeio.
    {
        perror("cannot open file!");
        exit(EXIT_FAILURE);
    }
    return fp;


}



int FILE_CLOSE_FILE(FILE* fp)
{

    if (!fclose(fp)) //success 0
        return 0;
    else
        return 1; //den ekleise to arxeio. 


}

int START_SEARCH(int NUM_OF_RECORDS, char* RECORD_FILE, int DEPTH_OF_BINARY_TREE, char* ok_arithmos_pediou, char* telesths, char* timh)
{
    int status;
    pid_t pid;
    char sdepth[10];
    char snumofrecords[25];


    sprintf(sdepth, "%d", DEPTH_OF_BINARY_TREE);
    sprintf(snumofrecords, "%d", NUM_OF_RECORDS);

    printf("START_SEARCH: \nNum of records is: %d Record file is: %s Depth is %d\n", NUM_OF_RECORDS, RECORD_FILE, DEPTH_OF_BINARY_TREE);
    printf("OKAP: .%s. TELEST: .%s. TIMH: .%s.\n", ok_arithmos_pediou, telesths, timh);


    switch (pid = fork()) //kanw fork to main_node
    {
    case -1:
    {
        perror("START_SEARCH fork");
        exit(1);
    }
    case 0:
    {

        if (execlp("./main_node", "main_node", snumofrecords, RECORD_FILE, sdepth, ok_arithmos_pediou, telesths, timh, NULL) < 0)
        {
            perror("START_SEARCH EXEC");
            exit(1);

        }
        break;
    }
    default: //pateras
    {


        while (waitpid(pid, &status, WNOHANG) == 0);
        if (WIFEXITED(status))
            printf("Exit status from main_node %d was %d\n", pid, WEXITSTATUS(status));




        break;
    }

    }




}

int COMPARE(char* telesths, char* pedio_arxeiou, char* pedio_prompt) //epistrefei 1 an tairiazoun, 0 an oxi
{
    int symbol = 0;

    if (!strncmp(telesths, "=",strlen(telesths))) //h timh tou symbol analogh tou telesth
        symbol = 1;
    else if (!strncmp(telesths, "!=",strlen(telesths)))
        symbol = 2;
    else if (!strncmp(telesths, "<",strlen(telesths)))
        symbol = 3;
    else if (!strncmp(telesths, ">",strlen(telesths)))
        symbol = 4;
    else if (!strncmp(telesths, "<=",strlen(telesths)))
        symbol = 5;
    else if (!strncmp(telesths, ">=",strlen(telesths)))
        symbol = 6;

    switch (symbol) //elegxos timwn
    {
    case 0:
    {
        printf("Lathos telesths\n");
        exit(1);        
    }
    case 1://=
    {
        if(!strncmp(pedio_arxeiou,pedio_prompt,strlen(pedio_prompt)))
            return 1;
        else
            return 0;
    }
    case 2://!=
    {
        if(strncmp(pedio_arxeiou,pedio_prompt,strlen(pedio_prompt)))
            return 1;
        else
            return 0;
    }
    case 3://<
    {
        if(strncmp(pedio_arxeiou,pedio_prompt,strlen(pedio_prompt))<0)
            return 1;
        else
            return 0;
    }
    case 4://>
    {
        if(strncmp(pedio_arxeiou,pedio_prompt,strlen(pedio_prompt))>0)
            return 1;
        else
            return 0;
    }
    case 5://<=
    {
         if((strncmp(pedio_arxeiou,pedio_prompt,strlen(pedio_prompt))<0) || !strncmp(pedio_arxeiou,pedio_prompt,strlen(pedio_prompt)))
            return 1;
        else
            return 0;
    }
    case 6://>=
    {
        if((strncmp(pedio_arxeiou,pedio_prompt,strlen(pedio_prompt))>0) || !strncmp(pedio_arxeiou,pedio_prompt,strlen(pedio_prompt)))
            return 1;
        else
            return 0;
    }
    }


}



int COMPARENUM(char* telesths, int pedio_arxeiou, int pedio_prompt) //epistrefei 1 an tairiazoun, 0 an oxi
{
    int symbol = 0;

    if (!strncmp(telesths, "=",strlen(telesths))) //h timh tou symbol analogh tou telesth
        symbol = 1;
    else if (!strncmp(telesths, "!=",strlen(telesths)))
        symbol = 2;
    else if (!strncmp(telesths, "<",strlen(telesths)))
        symbol = 3;
    else if (!strncmp(telesths, ">",strlen(telesths)))
        symbol = 4;
    else if (!strncmp(telesths, "<=",strlen(telesths)))
        symbol = 5;
    else if (!strncmp(telesths, ">=",strlen(telesths)))
        symbol = 6;

    switch (symbol) //elegxos timwn
    {
    case 0:
    {
        printf("Lathos telesths\n");
        exit(1);        
    }
    case 1://=
    {
        if(pedio_arxeiou == pedio_prompt)
            return 1;
        else
            return 0;
    }
    case 2://!=
    {
        if(pedio_arxeiou != pedio_prompt)
            return 1;
        else
            return 0;
    }
    case 3://<
    {
        if(pedio_arxeiou < pedio_prompt)
            return 1;
        else
            return 0;
    }
    case 4://>
    {
        if(pedio_arxeiou > pedio_prompt)
            return 1;
        else
            return 0;
    }
    case 5://<=
    {
         if(pedio_arxeiou <= pedio_prompt)
            return 1;
        else
            return 0;
    }
    case 6://>=
    {
        if(pedio_arxeiou >= pedio_prompt)
            return 1;
        else
            return 0;
    }
    }


}

