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
#ifndef CORE_H
#define CORE_H


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);



//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get valid integer from user, otherwise display an error message
int inputInt(void);

// Validates an integer value is entered within the range (inclusive) 
// and returned the value. Display error message if out of range.
int inputIntRange(int lowerBound, int upperBound);



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Check if the unit, return 0 if the unit is mm
int checkUnitMM(char unit);

// Covert amount based on unit
double unitConversion(char unit, double needConvert);

#endif // !CORE_H