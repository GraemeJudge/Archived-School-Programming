/*
 * binarydata.c
 *
 * This program will support the writing of a
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
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* TODO: change this from an interactive console app to a command line utility using this
 * command line: binarydata filename command value
 * for example: binarydata c:\tmp\data.bin 12345 987654321
 * this will allow for scriptability of this program in the future
 */

int
main (int argc, char *argv[]){
	unsigned short magic = 0xABCD;	/* first 2 bytes of file must have hex ABCD */
	unsigned short command;
	unsigned long data;
	unsigned char checksum;
	unsigned int value;
	FILE *fp;
	char filename[256];

	/* read data into binary file members */

	if (argc < 4){
		return -1;
	}
	command = (unsigned short)(argv[1]);// & 0x0000FFFF;	/* keep only low 16 bits of value */
	data = argv[2];
	filename = argv[3];
	/* compute checksum which is a sum of all the bytes in magic, command and data
	 * it should work as described here:
	 * https://en.wikipedia.org/wiki/Longitudinal_redundancy_check
	 * but I don't know how to add the bytes together!
	 */

	/* TODO: fix this algorithm */
	checksum = magic + command + data;	/* this doesn't seem to work? needs fix */

	filename[strlen (filename) - 1] = '\0';	/* whack the newline from fgets */

	/* output file data - should be 9 bytes in total
	 * but when compiled for a little endian CPU target, the
	 * bytes in the 16 and 32 bit values are backwards
	 * from the file format specification when I view the
	 * file from this web site: https://www.fileformat.info/tool/hexdump.htm
	 * Help!
	 */

	/* TODO: fix this to be platform agnostic */
	fp = fopen (filename, "wb");
	if (fp == NULL){
		fprintf(stderr, "File creation failed");
		return -1;
	}
	fwrite (&magic, sizeof (magic), 1, fp);
	fwrite (&command, sizeof (command), 1, fp);
	fwrite (&data, sizeof (data), 1, fp);
	fwrite (&checksum, sizeof (checksum), 1, fp);
	fclose (fp);

	return 0;
}	/* end main */

