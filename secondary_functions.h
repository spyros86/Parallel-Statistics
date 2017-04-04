/* 
 * File:   secondary_functions.h
 * Author: Spyros Vlachos
 * Created on December 9, 2011, 9:32 PM
 */

#ifndef SECONDARY_FUNCTIONS_H
#define	SECONDARY_FUNCTIONS_H

#ifdef	__cplusplus
extern "C"
{
#endif

    
    
FILE* FILE_OPEN_FILE(char* RECORD_FILE, char* mode);

int FILE_CLOSE_FILE(FILE* fp);
int START_SEARCH(int NUM_OF_RECORDS,char* RECORD_FILE,int DEPTH_OF_BINARY_TREE,char* ok_arithmos_pediou,char* telesths,char* timh);
int COMPARE(char* telesths, char* pedio_arxeiou, char* pedio_prompt); //epistrefei 1 an tairiazoun, 0 an oxi
int COMPARENUM(char* telesths, int pedio_arxeiou, int pedio_prompt); //to idio gia numbers

#ifdef	__cplusplus
}
#endif

#endif	/* SECONDARY_FUNCTIONS_H */

