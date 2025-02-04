/************************************************************
* Name:  Saurav Dahal
* Project : Yahtzee C++
* Class : Organization of Programming Languages (CMPS 366-01)
* Date : October 2nd, 2024
************************************************************/

#include "stdafx.h"
#include "ScoreCard.h"
#include "Tournament.h"
#include "Serialization.h"

// Main function
int main() {	
	// choice stores the user's choice to start a new game or load a saved game
	string choice;
	// isValidChoice stores the status of whether the user's choice is valid
	char isValidChoice = false;
	// serialize initializes a new Serialization object for saving the game state
	Serialization serialize;
	// tournament initializes a new Tournament object
	Tournament tournament;

	cout << "Welcome to Yahtzee!\n" << endl;
	cout << "Would you like to start a new game or load a saved game?\n";

	// Ask user if they want to start a new game or load a saved game
	// Loop until user enters a valid choice
	do {
		cout << "Please enter 'N' for new game or 'L' for load game: ";
		getline(cin, choice);
		if (choice == "N" || choice == "n")
		{
			isValidChoice = true;
			// Start a new tournament
			tournament.startNewTournament(); 
		}
		else if (choice == "L" || choice == "l")
		{
			serialize.loadGame();
			cin.ignore(10000, '\n');
			// Check if all categories have been filled
			if (!ScoreCard::isAllCategoriesFilled()) { 
				tournament.laodTournament(); // Load the tournament
			}
			else {
				// Display message if all categories have been filled
				cout << "\nAll categories have been filled!" << endl; 
				ScoreCard::displayScoreCard();
			}

			isValidChoice = true;
		}
		else
		{
			cout << "Invalid choice!" << endl;
		}
	} while (!isValidChoice); 
	return 0;

}