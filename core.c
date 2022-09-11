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
#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    while (getchar() != '\n')
    {
        ; 
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("< Press [ENTER] key to continue >");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get valid integer from user, otherwise display an error message
int inputInt(void)
{
    int intVal, invalid;
    char newLine = 'x';

    do {
        invalid = 0;
        scanf("%d%c", &intVal, &newLine);
        if (newLine != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
            invalid = 1;
        }
    } while (invalid);

    return intVal;
}

// Validates an integer value is entered within the range (inclusive) 
// and returned the value. Display error message if out of range.
int inputIntRange(int lowerBound, int upperBound)
{
    int rangeVal, invalid;

    do {
        invalid = 0;
        rangeVal = inputInt();
        if (rangeVal < lowerBound || rangeVal > upperBound)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ",
                   lowerBound, upperBound);
            invalid = 1;
        }
    } while (invalid);

    return rangeVal;
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////


// Check if the unit, return 0 if the unit is mm
int checkUnitMM(char unit)
{
    int needConvert = 0;

    if (unit != 'm')
    {
        needConvert = 1;
    }

    return needConvert;
}


// Covert amount based on unit
double unitConversion(char unit, double needConvert)
{
    double converted = 0;
    if (unit == 'c')
    {
        converted = needConvert * 10;
    }

    return converted;
}
