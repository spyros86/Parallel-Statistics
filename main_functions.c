/* 
 * File:  main_functions.c
 * Author: Spyros Vlachos
 * Created on December 9, 2011, 9:32 PM
 */
#include "definitions.h" 
#include "secondary_functions.h"
#include "main_functions.h"

int MAIN_CHECK_ARGS(int* DEPTH_OF_BINARY_TREE, char* RECORD_FILE, int argc, char** argv)//elegxw ta orismata apo synarthsh gia na einai pio mazemeno to programma.
{
    if (argc != 5)//an den exoun dothei ta aparaithta orismata
    {
        printf("Usage: ./findsort -d DepthOfBinaryTree -r RecordFile\n Now exiting!\n");
        exit(EXIT_FAILURE);
    }

    if (!strcmp("-d", argv[1]))//an to argv[1] einai -d
    {
        *DEPTH_OF_BINARY_TREE = atoi(argv[2]);

        printf("DEPTH_OF_BINARY_TREE= %d\n", *DEPTH_OF_BINARY_TREE);
        if (!strcmp("-r", argv[3]))//an to argv[3] einai -r
        {
            strncpy(RECORD_FILE, argv[4], FILENAME_MAX);
            printf("RECORD_FILE= %s\n", RECORD_FILE);
        }
        else
        {
            printf("Wrong arguments given!\nExiting!\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (!strcmp("-r", argv[1]))//an to argv[1] einai -r
    {
        strncpy(RECORD_FILE, argv[2], FILENAME_MAX);
        printf("RECORD_FILE= %s\n", RECORD_FILE);
        if (!strcmp("-d", argv[3]))//an to argv[3] einai -d
        {
            *DEPTH_OF_BINARY_TREE = atoi(argv[4]);

            printf("DEPTH_OF_BINARY_TREE= %d\n", *DEPTH_OF_BINARY_TREE);
        }
        else
        {
            printf("Wrong arguments given!\nExiting!\n");
            exit(EXIT_FAILURE);
        }
    }

}

int MAIN_GET_FILE_RECORD_NUM(char* RECORD_FILE, int* NUM_OF_RECORDS)
{
    FILE* fpb = FILE_OPEN_FILE(RECORD_FILE,"rb");

    //record rec;
    long FSize;
    //int i;
    // obtain file size:
    fseek(fpb, 0, SEEK_END);
    FSize = ftell(fpb);
    rewind(fpb);

    *NUM_OF_RECORDS = FSize / sizeof (record);

    /*for (i = 0; i < NUM_OF_RECORDS; i++)
    {
        fread(&rec, sizeof (record), 1, fpb);
        printf("%d %s %s %d %s %d\n", rec.id, rec.firstName, rec.lastName, rec.age, rec.job, rec.salary);
    }
     */

    FILE_CLOSE_FILE(fpb);

}

int MAIN_PROMPT(int DEPTH_OF_BINARY_TREE,char* RECORD_FILE,int NUM_OF_RECORDS)
{
    char command[50];
    
    char s_arithmos_pediou[4];
    char* chp; //gia thn strrchr wste na bgalw to $
    int i;
     char ok_arithmos_pediou[3];
    char telesths[3];
    char timh[20];
      
    
    printf(": Command: Arithmos-pediou Telesths Timh ENTER\nGia na bgeis \"exit\" ENTER\nGia help, help\n-----------------------------------\n");
    while (1)//prompt
    {
        
        printf("->");
        fgets(command,50,stdin);
        for(i=0;i<50;i++) //to fgets pairnei kai to \n gia valid character. Epeidh den to thelw to bgazw.
        {
            if(command[i] == '\n')
                command[i] = '\0';
        }
        if (!strcmp(command, "exit")) //an mou pei na bgw
        {
            printf("Exiting!\n");

            return 0;
        }
        else if(!strcmp(command, "help")) //an mou zhthsei boitheia
        {
            printf("Command: Arithmos-pediou Telesths Timh ENTER\nGia na bgeis \"exit\" ENTER\nGia help, help\n");
        }
        else
        {
            sscanf(command,"%3s %2s %19s",s_arithmos_pediou, telesths, timh); //pairnw apo to command ta epimerous
            
            //printf("AP: %s TELEST: %s TIMH: %s\n", s_arithmos_pediou, telesths, timh);
            chp=strrchr(s_arithmos_pediou,'$'); //briskw thn teleutaia emfanish tou $
            if(chp>0)
                strcpy(ok_arithmos_pediou, &s_arithmos_pediou[chp-s_arithmos_pediou+1]); //bazw ston arithmo pediou pou tha xrhsimopoihsw to kommati tou arithmou pediou pou phra xwris to $
            else
                strcpy(ok_arithmos_pediou, s_arithmos_pediou);  //an exei ksexasei kaneis to $
            
             
             START_SEARCH(NUM_OF_RECORDS,RECORD_FILE,DEPTH_OF_BINARY_TREE,ok_arithmos_pediou, telesths, timh); //edw tha arxisw ta fork.
             
            
        }



    }
}

