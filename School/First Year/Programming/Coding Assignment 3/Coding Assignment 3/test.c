/*
 * test.c
 *
 * This file creates timestamps and floating point values between
 * 0 and 1. Creates both xml and csv files and saves them in the directory
 * where the program is executed.
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

/* Sources used for main function
 * 		http://www.cplusplus.com/reference/ctime/strftime/
 * 		https://stackoverflow.com/questions/1694827/random-float-number
 */


/*
 * void main();
 *
 * this is the entry point of the program. It tests the io files in the 
 * fileio.c module by generating data and storing it in both formats.
 *
 * Input: None
 * Returns: Nothing
 */
void main(){
	char csvFileName[] = "testfile.csv";
	char xmlFileName[] = "testfile.xml";
	float values[NUMBER_OF_VALUES];
	char times[NUMBER_OF_VALUES][TIMESTAMP_LENGTH];
	
	for(int i = 0; i < NUMBER_OF_VALUES; i++){
		
		//get local time info
		time_t rawtime;
		struct tm *timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		
		//store random float between 1 and 0 into array
		//store formatted timestamp into array
		strftime(times[i], TIMESTAMP_LENGTH, "%H:%M:%S", timeinfo);	
		values[i] = rand()/(float)RAND_MAX;
		
		//console output for debugging purposes
		printf("Record #%d\ttime: %s\tvalue: %f\n", i + 1, times[i], values[i]);
		
		//wait until next entry
		clock_t start_time = clock();
		while(clock() < start_time + DELAY_TIME) {/* do nothing */}
	}
	
	//create files with generated data
	saveDataInCSV(times, values, NUMBER_OF_VALUES, csvFileName);
	saveDataInXML(times, values, NUMBER_OF_VALUES, xmlFileName);
	
	printf("files created");
}