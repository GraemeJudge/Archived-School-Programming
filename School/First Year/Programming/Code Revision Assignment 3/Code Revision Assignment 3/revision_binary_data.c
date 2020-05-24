/*
 * revision_binary_data.c
 *
 * This is a revision of binary_data.c. This program will support the writing of a
 * binary file format compatible with any CPU architecture
 * including big and little endian machines.
 *
 * The file format is as follows:
 * [bits 8 to 15 of magic]
 * [bits 0 to 7 of magic]
 * [bits 8 to 15 of command]
 * [bits 0 to 7 of command]
 * [bits 24 to 31 of data]
 * [bits 16 to 23 of data]
 * [bits 8 to 15 of data]
 * [bits 0 to 7 of data]
 * [checksum as 8 bits]
 *
 * Author: Stephane Durette
 * Date: March 8, 2019
 * Change Log:
 *    March 8, 2019 - source file created
 *
 */

 /*
 * header files needed for project
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/*
 * void get_values_from_user (void);
 *
 * This function will get the data, command and filename values
 * from the user interactively from the command line
 *
 * Input: short* command
 * 			memory location of the command variable that will be set by the user.
 * 
 * Input: long* data
 * 			memory location of the data variable that will be set by the user.
 *
 * Input: char* filename
 * 			string to be used as the filename that will be set by the user.
 *
 * Returns: Nothing
 */
void get_values_from_user(short *command, long *data, char *filename){
	unsigned int value;
	printf ("Enter command value: ");
	scanf ("%u", &value);
	*command = value & 0x0000FFFF;	/* keep only low 16 bits of value */
	
	fflush(stdin);
	printf ("Enter data: ");
	scanf ("%u", data);

	fflush (stdin);
	printf ("Enter filename: ");
	fgets (filename, 256, stdin);
	filename[strlen (filename) - 1] = '\0';	/* whack the newline from fgets */
}

/*
 * void write_values_to_file(int flipped, unsigned short *magic, unsigned short *command, unsigned long *data, unsigned char *checksum, char *filename);
 *
 * This function will write magic, command, data and checksum values into a binary file called filename.
 * It will compile for big endian format if flipped = 1, it will compile for little endian if flipped is 0
 *
 * Input: int flipped
 * 			flag value, if it's set to 1, it will flip the bytes to adhere to big endian format, otherwise 
 * 			it doesn't flip the bytes 
 * 
 * Input: unsigned short *magic
 *			memory location for the value of magic to write to the file.
 *
 * Input: unsigned short *command
 *			memory location for the value of command to write to the file.
 *
 * Input: unsigned long *data
 *			memory location for the value of data to write to the file.
 *
 * Input: unsigned char *checksum
 *			memory location for the value of checksum to write to the file.
 *
 * Input: char *filename
 *			string to name the file
 *
 * Returns: Nothing
 */
void write_values_to_file(int flipped, unsigned short *magic, unsigned short *command, unsigned long *data, unsigned char *checksum, char *filename){
	 FILE *fp;

	fp = fopen (filename, "wb");
	
	if (fp == NULL){
		fprintf(stderr, "File creation failed");
		return;
	}
	if (!flipped){
		fwrite (magic, sizeof (*magic), 1, fp);
		fwrite (command, sizeof (*command), 1, fp);
		fwrite (data, sizeof (*data), 1, fp);
		fwrite (checksum, sizeof (*checksum), 1, fp);
	} else {
		char *byte = (char*)magic;
		byte += sizeof(*magic) - sizeof(*byte);
		for(int i = 0; i < sizeof(*magic);i++) { fwrite (byte--, sizeof (*byte), 1, fp); }

		byte = (char*)command;
		byte += sizeof(*command) - sizeof(*byte);
		for(int i = 0; i < sizeof(*command);i++) { fwrite (byte--, sizeof (*byte), 1, fp); }

		byte = (char*)data;
		byte += sizeof(*data) - sizeof(*byte);
		for(int i = 0; i < sizeof(*data);i++) { fwrite (byte--, sizeof (*byte), 1, fp); }

		fwrite (checksum, sizeof (*checksum), 1, fp);
	}
	fclose (fp);
}
 
/*
 * void main (int argc, char** argv);
 *
 * this is the main entry point of the program. takes the input from a user, and computes the checksum.
 * it also outputs the results to a binary file.
 *
 * input int argc
 *		the amound of command line arguments passed to the function -1
 *
 * char** argv
 *		list of strings that represent the arguments to the function passed via the command line
 *
 * Returns: nothing
 */
void main (int argc, char** argv){
	unsigned short magic = 0xABCD;	/* first 2 bytes of file must have hex ABCD */
	unsigned short command;
	unsigned long data;
	unsigned char checksum;
	unsigned int value;
	FILE *fp;
	char filename[256] = "";
	
	#ifdef INTERACTIVE
		char filename[256] = "";
		get_values_from_user(&command, &data, filename);
	#endif
	
	#ifdef CLA
		if (argc != 4){
			printf("Incorrect Argument Count");
			return;
		}
		command = abs(atoi(argv[1])) & 0x0000FFFF;
		data = abs(atoi(argv[2]));
	#endif

	checksum = sizeof(magic) + sizeof(command) + sizeof(data);


	write_values_to_file(1, &magic, &command, &data, &checksum, argv[3]);
}

