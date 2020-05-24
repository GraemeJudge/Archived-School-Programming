/*
 * fileio.h
 * 
 * This file provides prototypes, #defines and external global variable
 * declarations for the fileio project
 */

#ifndef __FILEIO_H__
#define __FILEIO_H__

//common header files used by the source code in this project
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//constants common to all source files	
#define NUMBER_OF_VALUES 50
#define DELAY_TIME 1000
#define TIMESTAMP_LENGTH 9

//prototypes
int saveDataInCSV(char time[][9], float values[], int numValues, char filename[]);
int saveDataInXML(char time[][9], float values[], int numValues, char filename[]);

#endif