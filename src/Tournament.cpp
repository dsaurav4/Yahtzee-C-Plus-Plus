#include "stdafx.h"
#include "Tournament.h"
#include "Round.h"
#include "ScoreCard.h"
#include "Serialization.h"

//Constructor
Tournament::Tournament() {
	players.push_back(new Human()); // Add human player
	players.push_back(new Computer()); // Add computer player
}

//Destructor
Tournament::~Tournament() {
	for (Player* player : players) {
		delete player; // Delete player
	}
}


/****************************************************************
 * Function Name: Tournament::startNewTournament
 * Purpose: To manage the initiation and progression of a new tournament,
 *          including handling rounds, saving the game state, and determining the winner.
 * Parameters: None
 * Return Value: None
 * Algorithm:
 *          1. Display a message indicating the start of the tournament.
 *          2. Display the current scorecard.
 *          3. Initialize a new Round object with the list of players.
 *          4. Initialize a Serialization object for saving the game state.
 *          5. Loop until all categories have been filled or the game is saved:
 *              a. Start a new round of the tournament.
 *              b. Prompt the user to decide whether to save the game.
 *              c. If the user chooses to save the game, save the current game state and exit the loop.
 *              d. If the user chooses not to save, continue playing.
 * Reference: none
 ****************************************************************/
void Tournament::startNewTournament() {
    // playerName stores the name of the player (currently unused in the function)
    string playerName;


    cout << "Starting Tournament...\n" << endl;

    // Display the current scorecard
    ScoreCard::displayScoreCard();

    // round initializes a new Round object with the list of players
    Round round(players);

    // serialize initializes a new Serialization object for saving the game state
    Serialization serialize;

    // Loop until all categories have been filled or the game is saved
    do {
        // Start a new round of the tournament
        round.startRound();

        // saveChoice stores the user's decision to save the game ('Y'/'N')
        string saveChoice;

        // loop to ensure the user provides a valid choice to save the game
        do {
            // Prompt the user to decide whether to save the game
            cout << "Would you like to save your game? (Y/N): ";
            getline(cin, saveChoice);

            // Validate the user's input
            if (saveChoice != "Y" && saveChoice != "y" && saveChoice != "N" && saveChoice != "n")
            {
                cout << "Invalid choice!" << endl;
            }
        } while (saveChoice != "Y" && saveChoice != "y" && saveChoice != "N" && saveChoice != "n"); 

        // If the user chooses to save the game
        if (saveChoice == "y" || saveChoice == "Y")
        {
            // Save the current game state
            serialize.saveGame();
            // Exit the loop after saving
            break;
        }
        else // If the user chooses not to save, continue playing
        {
            continue;
        }

    } while (!ScoreCard::isAllCategoriesFilled());

    // After exiting the loop, check if all categories have been filled
    if (ScoreCard::isAllCategoriesFilled())
    {
        // Inform the user that all categories are filled
        cout << "\nAll categories have been filled!" << endl;
        cout << "\nCalculating final scores..." << endl;
        // Pause the program for 2 seconds to simulate calculation time
        this_thread::sleep_for(chrono::seconds(2));

        // Display the final scores of both players
        cout << players[0]->getName() << "'s final score: " << players[0]->getTotalScore() << endl;
        cout << players[1]->getName() << "'s final score: " << players[1]->getTotalScore() << endl;

        // Determine and display the winner based on the final scores
        if (players[0]->getTotalScore() > players[1]->getTotalScore())
        {
            // Announce Player 1 as the winner
            cout << "\n" << players[0]->getName() << " wins!" << endl;
        }
        else if (players[0]->getTotalScore() < players[1]->getTotalScore())
        {
            // Announce Player 2 as the winner
            cout << "\n" << players[1]->getName() << " wins!" << endl;
        }
        else
        {
            // Announce a tie if scores are equal
            cout << "\n" << "It's a tie!" << endl;
        }
    }
}


/****************************************************************
 * Function Name: Tournament::laodTournament
 * Purpose: To manage the loading of a saved game state and continue the tournament from the saved state.
 * Parameters: None
 * Return Value: None
 * Algorithm:
 *          1. Display the current scorecard.
 *          2. Display the scores of both players.
 *          3. Initialize a new Round object with the list of players.
 *          4. Initialize a Serialization object for saving the game state.
 *          5. Loop until all categories have been filled or the game is saved:
 *              a. Start a new round of the tournament.
 *              b. Prompt the user to decide whether to save the game.
 *              c. If the user chooses to save the game, save the current game state and exit the loop.
 *              d. If the user chooses not to save, continue playing.
 * Reference: none
 ****************************************************************/
void Tournament::laodTournament() {
	// Display the current scorecard
	ScoreCard::displayScoreCard();

	// Display the scores of both players
	cout << players[0]->getName() << "'s score: " << players[0]->getTotalScore() << endl; // Display player 1's score
	cout << players[1]->getName() << "'s score: " << players[1]->getTotalScore() << endl; // Display player 2's score


    // round initializes a new Round object with the list of players
    Round round(players);

    // serialize initializes a new Serialization object for saving the game state
    Serialization serialize;

    // Loop until all categories have been filled or the game is saved
    do {
        // Start a new round of the tournament
        round.startRound();

        // saveChoice stores the user's decision to save the game ('Y'/'N')
        string saveChoice;

        // loop to ensure the user provides a valid choice to save the game
        do {
            // Prompt the user to decide whether to save the game
            cout << "Would you like to save your game? (Y/N): ";
            getline(cin, saveChoice);

            // Validate the user's input
            if (saveChoice != "Y" && saveChoice != "y" && saveChoice != "N" && saveChoice != "n")
            {
                cout << "Invalid choice!" << endl;
            }
        } while (saveChoice != "Y" && saveChoice != "y" && saveChoice != "N" && saveChoice != "n");

        // If the user chooses to save the game
        if (saveChoice == "y" || saveChoice == "Y")
        {
            // Save the current game state
            serialize.saveGame();
            // Exit the loop after saving
            break;
        }
        else // If the user chooses not to save, continue playing
        {
            continue;
        }

    } while (!ScoreCard::isAllCategoriesFilled());

    // After exiting the loop, check if all categories have been filled
    if (ScoreCard::isAllCategoriesFilled())
    {
        // Inform the user that all categories are filled
        cout << "\nAll categories have been filled!" << endl;
        cout << "\nCalculating final scores..." << endl;
        // Pause the program for 2 seconds to simulate calculation time
        this_thread::sleep_for(chrono::seconds(2));

        // Display the final scores of both players
        cout << players[0]->getName() << "'s final score: " << players[0]->getTotalScore() << endl;
        cout << players[1]->getName() << "'s final score: " << players[1]->getTotalScore() << endl;

        // Determine and display the winner based on the final scores
        if (players[0]->getTotalScore() > players[1]->getTotalScore())
        {
            // Announce Player 1 as the winner
            cout << "\n" << players[0]->getName() << " wins!" << endl;
        }
        else if (players[0]->getTotalScore() < players[1]->getTotalScore())
        {
            // Announce Player 2 as the winner
            cout << "\n" << players[1]->getName() << " wins!" << endl;
        }
        else
        {
            // Announce a tie if scores are equal
            cout << "\n" << "It's a tie!" << endl;
        }
    }
}