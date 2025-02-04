#include "stdafx.h"
#include "Dice.h"

// Constructor
Dice::Dice()
{
	// Seed the random number generator
	srand(static_cast<unsigned int>(time(0)));
}

/* *********************************************************************
Function Name: Dice::rollDice
Purpose: To roll a number of dice and store the results in a vector
Parameters:
	numDice, an integer passed by value. The number of dice to roll.
Return Value: A vector of integers, the results of the dice rolls
Algorithm:
	1. Clear the vector
	2. For each die to roll
		1. Roll the die and add the result to the vector
	3. Return the vector
Reference: none
********************************************************************* */
vector<int> Dice::rollDice(int numDice)
{
	// Clear the vector to store the results of the dice rolls
	diceResult.clear();

	// Roll the dice numDice times
	for (int i = 0; i < numDice; ++i)
	{
		// Add the result of the die roll to the vector
		diceResult.push_back(rand() % 6 + 1);
	}

	// Return the vector of dice rolls
	return diceResult;
}

/* *********************************************************************
Function Name: Dice::rollSingleDice
Purpose: To roll a single die
Parameters: None
Return Value: An integer, the result of the die roll
Algorithm:
	1. Return a random number
Reference: none
********************************************************************* */
int Dice::rollSingleDice()
{
	// Return a random number between 1 and 6 for the die roll
	return rand() % 6 + 1;
}
