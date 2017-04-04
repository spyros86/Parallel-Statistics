/* 
 * File:   definitions.h
 * Author: Spyros Vlachos
 * Created on December 9, 2011, 9:56 PM
 */

#ifndef DEFINITIONS_H
#define	DEFINITIONS_H

#ifdef	__cplusplus
extern "C"
{
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char firstName[12];
    char lastName[12];
    int age;
    char job[15];
    int salary;
} record;

#define READSIZE (sizeof(record) +2)
#define READ 0
#define WRITE 1



#ifdef	__cplusplus
}
#endif

#endif	/* DEFINITIONS_H */

