/*
############################################################################

Project Name: Ontario Weather Service Management(Final Assessment)
Description: Main Application Entry Point

############################################################################

/*
*****************************************************************************
						Final - Coding Question

Group#: 6
Session: NAA

Num.	Member			Student ID#		Email
----    --------------	-----------		---------------------------
1.      Yi-Hsuan Weng	106800204		yhweng1@myseneca.ca
2.		Ping-Ju Chen	151043205		pchen72@myseneca.ca
3.		Yuchi Zheng		025848151		yzheng103@myseneca.ca

Authenticity Declaration:
We declare this submission is the result of our own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of our own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

// include system library
#include <stdio.h>

// include weatherService header file
#include "weather.h"

#define MAX_RECS 250

int main(void)
{
	struct WeatherRecord records[MAX_RECS] = { { { 0 } } };
	
	FILE* fp = fopen("weatherdata.txt", "r");

	if (!fp)
	{
		printf("Error!! Unable to open the source file!");
	}
	else
	{
		int recordCount = importWeatherDataFile(fp, records, MAX_RECS);

		fclose(fp);
		fp = NULL;

		menuMain(records, recordCount);
	}
	
	return 0;
}