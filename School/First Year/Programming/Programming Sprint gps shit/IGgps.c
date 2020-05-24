/*
 * gps.c
 *
 * This is a test app that showcases some basic Windows 
 * methods of communicating with serial based devices 
 * such as GPS receivers. The source code provides a test harness
 * and allows both "real" Serial Port access for a real GPS sensor, 
 * as well as reading from a GPS log to mimic GPS sensor behaviour.
 *
 * Enable USING_GPSSENSOR to turn on compilation of sensor code, otherwise
 * the GPS sensor simulation will be compiled
 *
 * This source file provides three API: gps_open(), gps_getstring() and gps_close()
 */


#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void delay(int sec){
	int resTime = time(0) + sec;
	
	while(time(0) < resTime);
	
}


//#define USING_GPSSENSOR

/*
 * HANDLE gps_open (char *port);
 *
 * This function will provide access to a GPS sensor, based on the 
 * the serial port name provided via port. The API will initialize
 * the port to 4800 baud as per standard GPS communications.
 *
 * INVALID_HANDLE_VALUE is returned on error.
 */

#ifdef USING_GPSSENSOR

HANDLE
gps_open (char *port) 
{
	HANDLE h;
	int x;
	DCB dcb;

	/* open a handle to the serial port, specified by the port string supplied */

	h = CreateFile (port, GENERIC_READ, 0, NULL, OPEN_ALWAYS, 0, NULL);
	if (h == INVALID_HANDLE_VALUE) {
		return h;
	}

	/*
	 * need to reset com port to 4800 baud for GPS string communications
	 */

	FillMemory (&dcb, sizeof (dcb), 0);	
	dcb.DCBlength = sizeof (dcb);

	x = GetCommState (h, &dcb);
	dcb.BaudRate = CBR_4800;
	dcb.Parity = NOPARITY;
	dcb.ByteSize = 8;
	dcb.StopBits = ONESTOPBIT;

	x = SetCommState (h, &dcb);

	return h;
}	/* end gps_open */

#else

HANDLE
gps_open (char *port) 
{
	HANDLE h;
	int x;
	DCB dcb;

	/* open a handle to the GPS log file represented by port */

	h = CreateFile (port, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);

	return h;
}	/* end gps_open */

#endif

/*
 * int gps_getstring (HANDLE h, char buffer[], int max);
 *
 * This function will read a GPS string from the device (or log file)
 * specified by parameter h, into memory pointed to by buffer. The
 * resulting string is normally terminated with a \r\n character combination,
 * however, this function will strip these from the
 * resulting string, to the maximum length specified
 */

int
gps_getstring (HANDLE h, char buffer[], int max)
{
	int len = 0;
	char ch;
	DWORD num;

	/* some sanity checking */

	if (buffer == NULL)
		return 0;

	buffer[0] = '\0';
	if (max <= 0)
		return 0;

	max--;	/* one fewer bytes to retrieve to leave room for null terminator */

	/* read until we reach max length
	 * GPS string will have \r\n combination to terminate a line, strip before returning 
	 */

	while (len != max) {
		ReadFile (h, &ch, 1, &num, NULL);
#ifndef USING_GPSSENSOR
		/* 
		 * in simulation, when reaching end of file, reset to start to
		 * have continuous GPS sensor data 
		 */

		if (num == 0) {
			SetFilePointer (h, 0, NULL, FILE_BEGIN);
			continue;
		}	/* endif */
#endif

		if (ch == '\n')
			break;
		if (ch == '\r')
			continue;
		buffer[len] = ch;
		len++;
	}	/* end while */

	buffer[len] = '\0';

	return len;
}


/*
 * void gps_close (HANDLE h);
 *
 * This function will close access to the GPS device (or log file), specified
 * by parameter h.
 */

void
gps_close (HANDLE h)
{
	CloseHandle (h);
}	/* end gps_close */


#ifdef TEST_HARNESS

int
main (void)
{
	char port[100];
	char buffer[256];
	HANDLE h;
	int i;

	printf ("Enter serial port name (or log file name): ");
	gets (port);

	h = gps_open (port);
	if (h == INVALID_HANDLE_VALUE) {
		printf ("Unable to access GPS sensor\n");
		return 1;
	}

	/* read GPS strings */

	for (i = 0; i < 100000; i++) {
		//gps_getstring (h, buffer, 256);
		
		
		while(fgets(i, 256, h) != NULL){
			fputs();
		}
		
		// fprintf (stderr, "%s\n", buffer);
		delay(2);
	}	/* end for */

	gps_close (h);

	return 0;
}

#endif
