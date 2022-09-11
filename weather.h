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

// SAFE-GUARD: 
#ifndef WEATHER_H
#define WEATHER_H


//////////////////////////////////////
// Module macro's (usable by any file that includes this header)
//////////////////////////////////////

#define NAME_LEN 100
#define CURRENT_YEAR 2021

//Max dada number (region number, month number, location number...)
#define MAX_DATA_NUM 100

//FMT
#define FMT_ALL 1
#define FMT_REGION 2
#define FMT_MONTH 3
#define FMT_LOCATE 4
#define DISPLAY_COUNT 15



//////////////////////////////////////
// Structures
//////////////////////////////////////

// Data type Date
struct Date
{
	int year;
	int month;
	char monthName[NAME_LEN + 1];
};

// Data type Location
struct Location
{
	int regionCode;
	char name [NAME_LEN + 1];
};

// Data type WeatherRecord
struct WeatherRecord
{
	struct Date date;
	double precipAmt;
	char unit;
	struct Location location;
};



//////////////////////////////////////
////////MASTER DATA STRUCTURE/////////
//////////////////////////////////////

// Data type RegionMaster
struct RegionMaster
{
	int regionCode;
	char regionName[NAME_LEN+1];
};


// Data type Month 
struct MonthMaster
{
	char monthName[NAME_LEN + 1];  
	double precipAmt;
};



//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// Display corresponding weather records header based on FMT
void displayWeatherHeader(int fmt);

// Display corresponding weather records data based on FMT
void displayWeatherData(const struct WeatherRecord* record, int fmt);

// Display the total and average of precip amount based on FMT
void displayTotalAverage(const struct WeatherRecord records[], int max, int fmt);




//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// Menu: Main
void menuMain(const struct WeatherRecord records[], int max);

// View all weather records in the FMT_ALL format
void viewAllData(const struct WeatherRecord records[], int max, int fmt);

// View weather records by region in the FMT_REGION format
void viewByRegion(const struct WeatherRecord records[], int max, int fmt);

// View weather records by month in the FMT_MONTH format
void viewByMonth(const struct WeatherRecord records[], int max, int fmt);

// View weather records by location in the FMT_LOCCATE format
void viewByLocation(const struct WeatherRecord records[], int max, int fmt);




//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Calculate the precipt amount by region
int calculateRegionAmt(const struct RegionMaster list[], int maxData,
				       const struct WeatherRecord records[], int max,
				       struct WeatherRecord temp[]);	

// Calculate the precip amount by month
int calculateMonthAmt(struct WeatherRecord temp[], struct MonthMaster month[], int maxData,
					  const struct WeatherRecord records[], int max);

// Calculate the precip amount by location
int calculateLocationAmt(struct WeatherRecord temp[], 
						 const struct WeatherRecord records[], int max);

// Calculate subtotal based on different unit and conversion
double calculateSubtotal(const struct WeatherRecord* record);

// Sort weather reocrds by precip amount by descending order
void sortByPreciAmtDescend(struct WeatherRecord records[], int count);

// Sort the records data by precip amount in ascending order
void sortByPrecipAmtAcend(struct WeatherRecord records[], int max);

// Calculate the total of precip amount 
double calculateTotal(const struct WeatherRecord records[], int max);

// Calculate the average of precip amount 
double calculateAverage(const struct WeatherRecord records[], int max);



//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import weather data from file into a WeatherRecord array (returns # of records read)
int importWeatherDataFile(FILE* fp, struct WeatherRecord* data, int max);


#endif // !WEATHER_H