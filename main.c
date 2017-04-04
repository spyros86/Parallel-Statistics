/* 
 * File:   main.c
 * Author: Spyros Vlachos
 * Created on December 9, 2011, 9:32 PM
 */


#include "definitions.h"
#include "main_functions.h"


/*Globals*/

/*
 * 
 */
int main(int argc, char** argv)
{

    int DEPTH_OF_BINARY_TREE = 0;
    char RECORD_FILE[FILENAME_MAX];
    int NUM_OF_RECORDS = 0;    
   
   
    
    
    printf("\nLS: \n");
    system("ls");
    printf("\n");


    MAIN_CHECK_ARGS(&DEPTH_OF_BINARY_TREE, RECORD_FILE, argc, argv); //elegkse kai pare o,ti plhroforia apo ta arguments
    MAIN_GET_FILE_RECORD_NUM(RECORD_FILE, &NUM_OF_RECORDS);
   

    MAIN_PROMPT(DEPTH_OF_BINARY_TREE,RECORD_FILE,NUM_OF_RECORDS);
    
    





    return (EXIT_SUCCESS);
}

