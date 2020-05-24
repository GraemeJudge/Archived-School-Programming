/*
 * fileio.c
 *
 * This file provides functions for saving timestamps and floats
 * in csv and xml formats to be used by other programs
 *
 * Author: Stephane Durette
 * Date: February 22, 2019
 * Change Log:
 *    February 22, 2019 - source file created
 *
 */

/*
 * Header files used for the project
 */
#include "fileio.h"

/*
 * int saveDataInCSV(char time[][9], float values[], int numValues, char filename[]);
 *
 * this function takes in a list of timestamps and a list of 
 * floating point values, stores them in a csv file in a way 
 * they can be read by microsoft excel.
 *
 * Input: char time[][9]
 *			Array of formatted time strings.
 *			time strings expect to be formatted HH:MM:SS
 *
 * Input: float values[]
 *			Array of floating point values, expected to be the same size as char 
 *			time[][9].
 *
 * Input: int numValues
 *			amount of values in the values[] and time[][9], these arrays are
 *			expected to be the same size
 *
 * Input: char filename[]
 * 			name of the file that the data is saved in
 *
 * Returns: -1 if execution fails, 0 if it succeeds
 */
int saveDataInCSV(char time[][9], float values[], int numValues, char filename[]){
	FILE *fptr;
	fptr = fopen(filename, "w");
	
	if (fptr == NULL){
		printf("File Opening Failed.");
		return -1;
	}
	
	fprintf(fptr, "time, value\n");
	for(int i = 0; i < numValues; i++){
		fprintf(fptr, "%s,%f\n", time[i], values[i]);
	}
	fclose(fptr);
	return 0;
}

/*
 * int saveDataInXML(char time[][9], float values[], int numValues, char filename[]);
 *
 * this function takes in a list of timestamps and a list of 
 * floating point values, stores them in an xml file in a way 
 * they can be read by microsoft excel.
 *
 * Input: char time[][9]
 *			Array of formatted time strings.
 *			time strings expect to be formatted HH:MM:SS
 *
 * Input: float values[]
 *			Array of floating point values, expected to be the same size as char 
 *			time[][9].
 *
 * Input: int numValues
 *			amount of values in the values[] and time[][9], these arrays are
 *			expected to be the same size
 *
 * Input: char filename[]
 * 			name of the file that the data is saved in
 *
 * Returns: -1 if execution fails, 0 if it succeeds
 */
int saveDataInXML(char time[][9], float values[], int numValues, char filename[]){
	FILE *fptr;
	fptr = fopen(filename, "w");
	
	if (fptr == NULL){
		printf("File Opening Failed.");
		return -1;
	}
	fprintf(fptr, "<data-set>\n");
	for(int i = 0; i < numValues; i++){
		fprintf(fptr,"<record>\n");
		fprintf(fptr, "<time>%s</time>\n", time[i]);
		fprintf(fptr, "<value>%f</value>\n", values[i]);
		fprintf(fptr,"</record>\n");
	}
	fprintf(fptr, "</data-set>");
	fclose(fptr);
	return 0;
}