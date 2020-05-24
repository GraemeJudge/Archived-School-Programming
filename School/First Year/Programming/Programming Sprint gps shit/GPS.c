#include <stdio.h>
#include <string.h>
#include <time.h>
#include<stdlib.h>
#include<math.h>


//very possibly a useless waste of time because i didnt read the project properly -_-




double DMSToGPS(char DMS[]);
int distance(struct point A,struct point B);

int appDoor = 0, appRes = 0, appCamp = 0;

void delay(int sec){

	int returnTime = time(0) + sec;

	while(time(0) < returnTime);
}



struct point
{
		float lat;
		float lon;
};




int
main(){

	static const char filename[] = "gpsdata.log";
	FILE *file = fopen ( filename, "r" );


struct point door; //closest was 281m away
	door.lat = 43.39073;
	door.lon = 80.40375;

struct point res; //closest was 57m away
	res.lat = 43.38491;
	res.lon = 80.41155;

struct point campus; //closest was 346m away
	campus.lat = 43.38611;
	campus.lon = 80.39685;


struct point first;
	first.lat = 44.2;
	first.lon = 80.3;

struct point second;
	second.lat = 44.19;
	second.lon = 80.28;


distance(first, second);



	if ( file != NULL )	{
		char line [256]; //max length of a line
		char north[256];
		char west[256];
		
		
		double lonHold = 100000, bestLon;
		double latHold = 100000, bestLat;
		
		char northHold[256];
		char westHold[256]; 
		
		
		
		while ( fgets ( line, sizeof line, file ) != NULL ){  //read the line as long as its not null;


			if(memcmp(line, "$GPGGA", 6) == 0){
				
				strcpy(north, (strchr(strchr(line, ',') + 1,',') + 1));
				strtok(north, ",N,");
				
				strcpy(west, strchr(strchr(strchr(line, ',') + 1,',') + 1, ',') + 3);
				strtok(west, ",W");
				
				
				double lat = DMSToGPS(north);
				
				
				double lon = DMSToGPS(west);
				
				
				struct point bus;
				bus.lon = lon;
				bus.lat = lat;
				
				//distance(bus,door);
				//distance(bus, res);
				//distance(bus, campus);
				
				//printf("%d\n", distance(bus, door));
				
				if(distance(bus, door) < 500 && appDoor == 0){
					printf("Next Stop Door\n");
					// appDoor = 1;
				}		
				if(distance(bus, res) < 500 && appRes == 0){
					printf("Next Stop Res\n");
					// appRes = 1;
				}
				if(distance(bus, campus) < 500 && appCamp == 0){
					printf("Next Stop Campus\n");
					// appCamp = 1;
				}
				
				// printf("%f North   Length: %d\n", lat, strlen(north) -1);
				// printf("%f West   Length: %d\n\n", lon, strlen(west) -1);
				
			
				
				
				
				
				//delay(1);
				
			}



		}
		
		// printf("%s  ----------  %s\n%f  ----------  %f", north, west, bestLat, bestLon);
		
		fclose ( file );

	}else{	
		perror ( filename ); // error catch if file doesnt open;
	}
	
	return 0;
}


double DMSToGPS(char DMS[256]){
	
	double d = atoi(DMS)/100;
	double m = atoi(DMS) - ((atoi(DMS)/100)*100); 
	double s = (atof(DMS) - atoi(DMS)) * 100;	
	
	return (d + (m/60) + (s/3600));
	
}


int distance(struct point A, struct point B){
	
	float rads = M_PI/180;
	
	float latDis = (fabs(A.lat - B.lat));
	float lonDis = (fabs(A.lon - B.lon));
	
	float rEarth = 6378;
	float cEarth = (2 * M_PI * rEarth);
	
	float r2 = rEarth * (cos(A.lat * rads));
	
	float c = (2 * M_PI * r2)/360;
	
	float rise = latDis * 113.32;
	float run = lonDis *(c);
	
	int dist = (int)(sqrt((rise * rise) + (run * run)) * 1000);
	
	return dist;
	
}

// float distance(struct point A, struct point B){
	
	// need to expand to take into account the curvature of the earth (just x direction)
	
	
	// float rads = M_PI / 180;
	
	// float r2 = 6378 * (cos(A.lat * rads));
	
	// float len = (2 * (M_PI * r2)) / 360; //km per degree difference for rise
	// float lan = 40075/360; //km per degree difference for run
	
	
	// isolate each piece??
	
	
	// float xDis = lan * (fabs(A.lon - B.lon)); //run
	// float yDis = len * (fabs(A.lat - B.lat)); //rise
	
	// float dist = sqrt((xDis * xDis) + (yDis * yDis));
	
	// printf("x1: %f   y1: %f   x2: %f    y2: %f  \n",A.lon,A.lat,B.lon,B.lon);
	
	 // printf("%f   \n", len);
	
	// printf("distance to door: %f     \n", xDis);
	
	
	// return 0;
// }