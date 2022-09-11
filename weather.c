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

#include <stdio.h>
#include <string.h>

#include "weather.h"
#include "core.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// Display corresponding weather records header based on FMT
void displayWeatherHeader(int fmt)
{
    if (fmt == FMT_ALL)
    {
        printf("Year Month Precip.Amt Unit Region Name\n"
               "---- ----- ---------- ---- ------ ---------------\n");
    }
    else if (fmt == FMT_REGION)
    {
        printf("Region Name     Precip(mm)\n"
               "------ -------- ----------\n");
    }
    else if (fmt == FMT_MONTH)
    {
        printf("Month     Precip(mm)\n"
               "--------- ----------\n");
    }
    else if (fmt == FMT_LOCATE)
    {
        printf("Location        Precip(mm)\n"
               "--------------- ----------\n");
    }
}

// Display corresponding weather records data based on FMT (single record)
void displayWeatherData(const struct WeatherRecord* record, int fmt)
{
    if (fmt == FMT_ALL)
    {
        printf("%4d    %02d %10.1lf %4c %6d %-15s\n",
               record->date.year, record->date.month,
               record->precipAmt, record->unit,
               record->location.regionCode, record->location.name);
    }
    else if (fmt == FMT_REGION) 
    {
        printf("%6d %-8s %10.lf\n", 
            record->location.regionCode,
            record->location.name,
            record->precipAmt);
    }
    else if (fmt == FMT_MONTH) 
    {
        printf("%-9s %10.0lf\n", record->date.monthName, record->precipAmt);
    }
    else if (fmt == FMT_LOCATE)
    {
        printf("%15s %10.0lf\n", record->location.name, record->precipAmt);
    }
}

// Display the total and average of precip amount based on FMT
void displayTotalAverage(const struct WeatherRecord records[], int max, int fmt)
{
    double total = 0.0, average = 0.0;

    total = calculateTotal(records, max);       
    average = calculateAverage(records, max);   

    if (fmt == FMT_REGION)
    {
        printf("------ -------- ----------\n"
               "         Total: %10.0lf\n"  
               "       Average: %10.2lf\n\n", total, average);
    }
    else if (fmt == FMT_MONTH)
    {
        printf("--------- ----------\n"
               "   Total: %10.0lf\n"
               " Average: %10.2lf\n\n", total, average);
    }
    else if (fmt == FMT_LOCATE)
    {
        printf("--------------- ----------\n"
               "         Total: %10.0lf\n"
               "       Average: %10.2lf\n\n", total, average);
    }
}



//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// Menu: Main
void menuMain(const struct WeatherRecord records[], int recsCount)
{
    int selection;

    do {
        printf("=======================================================\n"
               "         Ontario Weather Analysis Service\n"
               "                  Year: %d\n"
               "=======================================================\n"
               "1. View all data\n"
               "2. View by region (sorted DESCENDING by precip.)\n"
               "3. View by month (sorted ASCENDING by precip.)\n"
               "4. View by location name (sorted DESCENDING by precip.)\n"
               "-------------------------------------------------------\n"
               "0. Exit\n"
               "-------------------------------------------------------\n"
               "Selection: ", CURRENT_YEAR);
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Application Terminated!\n");
            break;
        case 1:
            viewAllData(records, recsCount, FMT_ALL);
            break;
        case 2:
            viewByRegion(records, recsCount, FMT_REGION);
            break;
        case 3:
            viewByMonth(records, recsCount, FMT_MONTH);
            break;
        case 4:
            viewByLocation(records, recsCount, FMT_LOCATE);
            break;
        }
    } while (selection);
}

// View all weather records in the FMT_ALL format
void viewAllData(const struct WeatherRecord records[], int max, int fmt)
{
    int i, emptyRec = 0;
    displayWeatherHeader(fmt);
    for (i = 0; i < max; i++)
    {
        if (records[i].date.year == 0)
        {
            emptyRec++;
        }
        else
        {
            displayWeatherData(&records[i], fmt);
            if ((i+1) % DISPLAY_COUNT == 0)
            {
                putchar('\n');
                suspend();
            }
        }
    }
    if (emptyRec == i)
    {
        printf("*** No weather records found ***\n");
    }
    putchar('\n');
}

// View weather records by region in the FMT_REGION format
void viewByRegion(const struct WeatherRecord records[], int max, int fmt)
{ 
    int i;
    int counter = 0;

    struct WeatherRecord temp[MAX_DATA_NUM] = { {{0}} };

    struct RegionMaster regionMaster[MAX_DATA_NUM] = { {10, "Western"},
                                                       {20, "Northern"},
                                                       {30, "Estern"},
                                                       {40, "Central"} };

    displayWeatherHeader(FMT_REGION);
    counter = calculateRegionAmt(regionMaster, MAX_DATA_NUM, records, max, temp);
    sortByPreciAmtDescend(temp, counter);

    for (i = 0; i < counter ; i++)
    {
        displayWeatherData(&temp[i], FMT_REGION);
    }

    displayTotalAverage(temp, counter, FMT_REGION);
}   

// View weather records by month in the FMT_MONTH format
void viewByMonth(const struct WeatherRecord records[], int max, int fmt)
{
    int i, counter = 0;
    
    struct WeatherRecord temp[MAX_DATA_NUM] = { {{0}} };

    struct MonthMaster month[MAX_DATA_NUM] = { {"January", 0}, {"February", 0},{"March", 0},
                                               {"April", 0}, {"May", 0}, {"June", 0},
                                               {"July", 0}, {"August", 0}, {"September", 0},
                                               {"October", 0}, {"November", 0}, {"December", 0} };

    displayWeatherHeader(FMT_MONTH);
    counter = calculateMonthAmt(temp, month, MAX_DATA_NUM, records, max);
    sortByPrecipAmtAcend(temp, counter);

    for (i = 0; i < counter; i++)
    {
        displayWeatherData(&temp[i], FMT_MONTH); 
    }

    displayTotalAverage(temp, counter, FMT_MONTH);
}

// View weather records by location in the FMT_LOCCATE format
void viewByLocation(const struct WeatherRecord records[], int max, int fmt)
{
    int i;
    int counter = 0;
    struct WeatherRecord temp[MAX_DATA_NUM] = { {{0}} };

    displayWeatherHeader(FMT_LOCATE);
    counter = calculateLocationAmt(temp, records, max);
    sortByPreciAmtDescend(temp, counter);

    for (i = 0; i < counter; i++)
    {
        displayWeatherData(&temp[i], FMT_LOCATE);
    }

    displayTotalAverage(temp, counter, FMT_LOCATE);
}



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Calculate the precipt amount by region
int calculateRegionAmt(const struct RegionMaster list[], int maxData,
                       const struct WeatherRecord records[], int max, 
                       struct WeatherRecord temp[])
{
    int i, j;
    int counter = 0;
    double regionTotal = 0.0;

    for (i = 0; i < maxData && list[i].regionCode; i++)
    {
        for (j = 0; j < max; j++)
        {
            if (list[i].regionCode == records[j].location.regionCode)
            {
                regionTotal = calculateSubtotal(&records[j]);
                temp[i].precipAmt += regionTotal;
            }
        }
        counter++;
        strcpy(temp[i].location.name, list[i].regionName);
        temp[i].location.regionCode = list[i].regionCode;
        regionTotal = 0;
    }

    return counter;
}

// Calculate the precip amount by month
int calculateMonthAmt(struct WeatherRecord temp[], struct MonthMaster month[], int maxData,
    const struct WeatherRecord records[], int max)
{
    int i, j, counter = 0;
    double precipAmtTotal = 0.0;

    for (i = 0; i < maxData && strlen(month[i].monthName); i++)
    {
        for (j = 0; j < max; j++)     
        {
            if (records[j].date.month == (i + 1))          
            {
                precipAmtTotal = calculateSubtotal(&records[j]);
                temp[i].precipAmt += precipAmtTotal;
            }
        }
        counter++;
        strcpy(temp[i].date.monthName, month[i].monthName);
        precipAmtTotal = 0.0;
    }

    return counter;
}

// calculate the precip amount by location
int calculateLocationAmt(struct WeatherRecord temp[], const struct WeatherRecord records[], int max)
{
    int i, j;
    int counter = 0;
    int valid = 0;
    double precipAmtTotal = 0.0;
     
    for (i = 0; i < max; i++) 
    {
        valid = 0;
        for (j = 0; temp[j].precipAmt; j++)  
        {
            if (!strcmp(temp[j].location.name, records[i].location.name))       // have record (location name)?
            {
                precipAmtTotal = calculateSubtotal(&records[i]);                // calculate precipAmtTotal
                temp[j].precipAmt += precipAmtTotal;                            // increment: precipAmtTotal
                valid = 1;
            }
        }
        if (!valid)                                                             // no record (location name)
        {
            strcpy(temp[j].location.name, records[i].location.name);            // store location name in temp
            precipAmtTotal = calculateSubtotal(&records[i]);                    // calculate precipAmtTotal
            temp[j].precipAmt += precipAmtTotal;                                // increment: precipAmtTotal

            counter++;                                                          // increment: the number of location
        }
    }

    return counter;
}

// Calculate subtotal based on different unit and conversion
double calculateSubtotal(const struct WeatherRecord* record)
{
    int convertUnit = checkUnitMM(record->unit);
    double subTotal;

    if (convertUnit)
    {
        subTotal = unitConversion(record->unit, record->precipAmt);
    }
    else
    {
        subTotal = record->precipAmt;
    }

    return subTotal;
}

// Sort weather reocrds by precip amount by descending order
void sortByPreciAmtDescend(struct WeatherRecord records[], int count)
{
    int i, j;
    struct WeatherRecord temp;

    for (i = count - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (records[j].precipAmt < records[j + 1].precipAmt)
            {
                temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
            }
        }
    }
}

// Sort the records data by precip amount in ascending order
void sortByPrecipAmtAcend(struct WeatherRecord records[], int max)
{
    int i, j;
    struct WeatherRecord temp;

    for (i = max - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (records[j].precipAmt > records[j + 1].precipAmt)
            {
                temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
            }
        }
    }
}

// Calculate the total of precip amount 
double calculateTotal(const struct WeatherRecord records[], int max)
{
    int i;
    double total = 0.0; 

    for (i = 0; i < max; i++)
    {
        total += records[i].precipAmt;
    }

    return total;
}

// Calculate the average of precip amount 
double calculateAverage(const struct WeatherRecord records[], int max)
{
    double average = 0.0;

    average = calculateTotal(records, max) / max;

    return average;
}



//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import weather data from file into a WeatherRecord array (returns # of records read)
int importWeatherDataFile(FILE* fp, struct WeatherRecord* data, int max)
{
    int recs = 0;

    if (fp != NULL)
    {
        while (recs < max &&
            fscanf(fp, "%d,%d,%lf,%c,%d,%15[^\n]\n",
               &data[recs].date.year, &data[recs].date.month,
               &data[recs].precipAmt, &data[recs].unit,
               &data[recs].location.regionCode,
               data[recs].location.name) == 6)
        {
            recs++;
        }
    }

    return recs;
}