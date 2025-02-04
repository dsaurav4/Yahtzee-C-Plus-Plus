#include "stdafx.h"
#include "Round.h"
#include "Dice.h"
#include "Turn.h"
#include "ScoreCard.h"

//Round::roundNumber stores the current round number
//It is a static variable so that it is shared among all instances of the class
int Round::roundNumber = 1;

// Constructor
Round::Round(const vector<Player*>& players) : players(players) {}

/****************************************************************
 * Function Name: Round::incrementRound
 * Purpose: To increment the current round number by one.
 * Parameters: None
 * Return Value: None
 * Reference: none
 ****************************************************************/
void Round::incrementRound() {
    roundNumber++;
}

/****************************************************************
 * Function Name: Round::getRoundNumber
 * Purpose: To return the current round number.
 * Parameters: None
 * Return Value: An integer, the current round number.
 * Reference: none
 ****************************************************************/
int Round::getRoundNumber() {
    return roundNumber;
}

/****************************************************************
 * Function Name: Round::setRoundNumber
 * Purpose:
            To set the current round number to a new specified value.
 * Parameters:
 *         newRoundNumber, an integer passed by value.
 *             It represents the new round number to be set.
 * Return Value: None
 * Reference: none
 ****************************************************************/
void Round::setRoundNumber(int newRoundNumber) {
    Round::roundNumber = newRoundNumber;
}

/****************************************************************
 * Function Name: Round::startRound
 * Purpose:
            To start a new round of the game.
 * Parameters:
            None
 * Return Value:
             None
 * Algorithm:
 *          1. If the current round number is 1, then roll the dice to decide who goes first.
 *          2. If the current round number is not 1, then the player with the lowest score goes first.
 *          3. If both players have the same score, then roll the dice to decide who goes first.
 *          4. Initialize a Turn object with the first and second player.
 *          5. Start the turn.
 * Reference: none
 ****************************************************************/
void Round::startRound() {
    cout << "\nRound " << roundNumber << " has started!" << endl;
	cout << "--------------------------------" << endl;

	// firstPlayer and secondPlayer hold the pointers to the players who will play the current round
    Player* firstPlayer = nullptr;
    Player* secondPlayer = nullptr;

	// Decide who goes first
	// if the round number is 1
    if (roundNumber == 1 ) {
		cout << "\nRolling to see who goes first..." << endl;
        int humanRoll = 0;
        int computerRoll = 0;

		// Decide who goes first by rolling the dice
		// Loop until the human and computer rolls are different
		do { 
			// humanRoll stores the value of the dice roll for the human player
            humanRoll = players[0]->turnChooseRoll();
            cout << players[0]->getName() << " rolled a " << humanRoll << endl;

            cout << "Press Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

			// computerRoll stores the value of the dice roll for the computer player
            computerRoll = players[1]->turnChooseRoll();
            this_thread::sleep_for(chrono::seconds(2));
            cout << players[1]->getName() << " rolled a " << computerRoll << endl;
			this_thread::sleep_for(chrono::seconds(1));

			// Decide who goes first 
			// If the human roll is greater than the computer roll, then the human goes first
            if (humanRoll > computerRoll) {
                cout << "\n" << players[0]->getName() << " goes first!" << endl;
				// assigning the first player to human player
                firstPlayer = players[0];
				// assigning the second player to the computer player
                secondPlayer = players[1];

            }
			// If the human roll is less than the computer roll, then the computer goes first
            else if (humanRoll < computerRoll) {
                cout << "\n" << players[1]->getName() << " goes first!" << endl;
				// assigning the first player to computer player
                firstPlayer = players[1];
				// assigning the second player to human player
                secondPlayer = players[0];
            }
			// display a message if the rolls are the same
            else {
                cout << "\nIt's a tie! Rolling again..." << endl;
            }
        } while (humanRoll == computerRoll);

    }
	// If the round number is not 1
    else {
		

		//player with lowest score goes first
		if (players[0]->getTotalScore() < players[1]->getTotalScore()) {
            cout << "\n" << players[0]->getName() << " goes first!" << endl;
			firstPlayer = players[0];
			secondPlayer = players[1];
		}
		else  if(players[0]->getTotalScore() > players[1]->getTotalScore()) {
            cout << "\n" << players[1]->getName() << " goes first!" << endl;
			firstPlayer = players[1];
			secondPlayer = players[0];
        }
		// If both players have the same score, then roll the dice to decide who goes first
        else {
            cout << "\nRolling to see who goes first..." << endl;
            int humanRoll = 0;
            int computerRoll = 0;

            // Decide who goes first
            do {
				humanRoll = players[0]->turnChooseRoll(); 
                cout << players[0]->getName() << " rolled a " << humanRoll << endl;

                cout << "Press Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

				computerRoll = players[1]->turnChooseRoll();
                this_thread::sleep_for(chrono::seconds(2));
                cout << players[1]->getName() << " rolled a " << computerRoll << endl;
                this_thread::sleep_for(chrono::seconds(1));

                if (humanRoll > computerRoll) {
                    cout << "\n" << players[0]->getName() << " goes first!" << endl;
                    firstPlayer = players[0];
                    secondPlayer = players[1];

                }
                else if (humanRoll < computerRoll) {
                    cout << "\n" << players[1]->getName() << " goes first!" << endl;
                    firstPlayer = players[1];
                    secondPlayer = players[0];
                }
                else {
                    cout << "\nIt's a tie! Rolling again..." << endl;
                }
            } while (humanRoll == computerRoll);
        }

    }
    
	//Initialize the turn object with the first and second player
    Turn turn(*firstPlayer, *secondPlayer);  

	// Start the turn
    turn.startTurns();

	// Check if the round is over
    if (turn.isRoundOver()) {
		cout << "Round " << roundNumber << " is over!" << endl;
        cout << players[0]->getName() << " has a total score of " << players[0]->getTotalScore() << endl;
        cout << players[1]->getName() << " has a total score of " << players[1]->getTotalScore() << endl;
		// Check if all categories have been filled
        if (!ScoreCard::isAllCategoriesFilled()) {
			incrementRound(); // Increment the round number
        }
    }
}