/* 
 * File:   main_functions.h
 * Author: Spyros Vlachos
 * Created on December 9, 2011, 9:32 PM
 */

#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

#ifdef	__cplusplus
extern "C"
{
#endif
    
   
int MAIN_CHECK_ARGS(int* DEPTH_OF_BINARY_TREE, char* RECORD_FILE, int argc, char** argv);
int MAIN_GET_FILE_RECORD_NUM(char* RECORD_FILE,int* NUM_OF_RECORDS);
int MAIN_PROMPT(int DEPTH_OF_BINARY_TREE,char* RECORD_FILE,int NUM_OF_RECORDS);


#ifdef	__cplusplus
}
#endif

#endif	/* FUNCTIONS_H */

