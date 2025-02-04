#include "stdafx.h"
#include "Turn.h"
#include "ScoreCard.h"
#include "Dice.h"

// Constructor
Turn::Turn(Player& firstPlayer, Player& secondPlayer)
    : firstTurnPlayer(firstPlayer), secondTurnPlayer(secondPlayer), roundOver(false) {}

/****************************************************
* Function Name: Turn::startTurns
* Purpose: To start the turns for the players
* Parameters:
*           none
* Return Value: none
* Algorithm:
* 		 1) Play the first turn
* 		 2) Check if all categories have been filled
* 		 3) Play the second turn if all categories have not been filled
* 		 4) Set the round to be over if all categories have been filled
* Reference: none
/***************************************************/
void Turn::startTurns() {
    // Play the first turn 
	firstTurnPlayer.playTurn(); 
    // Check if all categories have been filled
	if (!ScoreCard::isAllCategoriesFilled()) { 
        // Play the second turn
		secondTurnPlayer.playTurn(); 
        roundOver = true;
    }
    else
	{
        // Set the round to be over if all categories have been filled
		roundOver = true; 
    }

}

/****************************************************
* Function Name: Turn::isRoundOver
* Purpose: To check if the round is over
* Parameters:
* 		 none
* Return Value:
* 		 bool, true if the round is over, false otherwise
* Reference: none
***************************************************/
bool Turn::isRoundOver() const {
    // Return the status of whether the round is over
    return roundOver; 
}


