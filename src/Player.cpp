#include "stdafx.h"
#include "Player.h"
#include "Dice.h"
#include "ScoreCard.h"
#include "Round.h"

/****************************************************************
 * Function Name: Player::getName
 * Purpose: To get the name of the player
 * Parameters:
 *         None
 * Return Value: A string representing the name of the player
 * Reference: None
 ****************************************************************/
string Player::getName()
{
	return name;
}

// Constructor for Human class
Human::Human()
{
	// Set the name of the human player
	name = "Human";
}

// Constructor for Computer class
Computer::Computer()
{
	// Set the name of the computer player
	name = "Computer";
}

/****************************************************************
 * Function Name: Human::turnChooseRoll
 * Purpose: To choose the turn for the Human player
 * Parameters:
 *         None
 * Return Value: An integer representing the value of the dice roll
 * Algorithm:
 * 			 1. Ask the user to roll the dice
 * 			 2. Loop until user enters a valid choice
 * 			 3. Return the value of the dice roll
 * Reference: None
 ****************************************************************/
int Human::turnChooseRoll()
{
	// Create a Dice object to roll the dice
	Dice dice;

	// roll stores the user's choice to roll the dice
	string roll;

	// Ask the user to roll the dice and loop until user enters a valid choice
	do
	{
		cout << "\nEnter R to roll the dice: ";
		getline(cin, roll);

		// Display message if the user enters an invalid choice
		if (roll != "R" && roll != "r")
		{
			cout << "Invalid input!" << endl;
		}
	} while (roll != "R" && roll != "r");

	return dice.rollSingleDice(); // return the value of the dice roll
}

/****************************************************************
 * Function Name: Coomputer::turnChooseRoll
 * Purpose: To choose the turn for the Computer player
 * Parameters:
 *         None
 * Return Value: An integer representing the value of the dice roll
 * Algorithm:
 * 			 1. Display message that computer is rolling the dice
 * 			 2. Return the value of the dice roll
 * Reference: None
 ****************************************************************/
int Computer::turnChooseRoll()
{
	// Create a Dice object to roll the dice
	Dice dice;

	cout << "\nComputer is rolling the dice..." << endl;

	// return the value of the dice roll for the computer
	return dice.rollSingleDice();
}

/****************************************************************
 * Function Name: Human::isHuman
 * Purpose: To check if the player is human
 * Parameters:
 *         None
 * Return Value: A boolean value of true
 * Reference: None
 ****************************************************************/
bool Human::isHuman()
{
	return true;
}

/****************************************************************
 * Function Name: Computer::isHuman
 * Purpose: To check if the player is computer
 * Parameters:
 *         None
 * Return Value: A boolean value of false
 * Reference: None
 ****************************************************************/
bool Computer::isHuman()
{
	return false;
}

/****************************************************************
 * Function Name: Player::getTotalScore
 * Purpose: To get the total score of the player
 * Parameters:
 *         None
 * Return Value: An integer representing the total score of the player
 * Reference: None
 ****************************************************************/
int Player::getTotalScore()
{
	// Return the total score of the player that calls this function
	return ScoreCard::getTotalScore(this->name);
}

/****************************************************************
 * Function Name: Player::rollOrSet
 * Purpose: To roll the dice randomly or set the values manually
 * Parameters:
 *         diceCount, an integer passed by value. The number of dice to roll
 * Return Value: A vector of integers representing the dice values
 * Algorithm:
 * 			 1. Ask the user if they want to roll the dice randomly or set the values manually
 * 			 2. Loop until user enters a valid choice
 * 			 3. Roll the dice randomly if the user chooses to roll the dice randomly
 * 			 4. Set the dice values manually if the user chooses to set the values manually
 * 			 5. Loop until user enters a valid input
 * 			 6. Set the manually entered values
 * 			 7. Return the dice values based on the number of dice
 * Reference: None
 ****************************************************************/
vector<int> Player::rollOrSet(int diceCount)
{
	// setDiceValues vector stores the dice values
	vector<int> setDiceValues;
	// rollOrSet stores the user's choice to roll the dice randomly or set the values manually
	string rollOrSet;
	// dice object to roll the dice
	Dice dice;

	// Ask the user if they want to roll the dice randomly or set the values manually
	// and loop until user enters a valid choice
	do
	{
		cout << "Do you want to roll the dice randomly or set the dice values? Enter R for random or S to set: ";
		getline(cin, rollOrSet);

		if (rollOrSet != "R" && rollOrSet != "r" && rollOrSet != "S" && rollOrSet != "s")
		{
			cout << "Invalid input!" << endl;
		}
	} while (rollOrSet != "R" && rollOrSet != "r" && rollOrSet != "S" && rollOrSet != "s");

	// Roll the dice randomly if the user chooses to roll the dice randomly
	// and return the dice values based on the number of dice
	if (rollOrSet == "R" || rollOrSet == "r")
	{

		if (!this->isHuman())
		{
			cout << "Computer is rolling the dice..." << endl;
			// Pause for 2 seconds to mimic the computer rolling the dice
			this_thread::sleep_for(chrono::seconds(2));
		}
		// Return dice values based on the number of dice
		return (dice.rollDice(diceCount));
	}
	// Set the dice values manually if the user chooses to set the values manually
	// and loop until user enters a valid input
	else
	{
		// input stores the user's input for the dice values
		string input;
		// validInput stores the boolean value to check if the input is valid
		bool validInput = false;
		// valueOrValues stores the string value based on the number of dice
		string valueOrValues = (diceCount == 1) ? "value" : "values";

		// Loop until user enters a valid input
		while (!validInput)
		{
			// clear the setDiceValues vector to store the dice values
			// entered by the user
			setDiceValues.clear();

			cout << "Enter " << diceCount << " dice " << valueOrValues << " (1 - 6) separated by spaces : ";
			getline(cin, input);

			// istringstream object to read the input
			// from the user
			istringstream iss(input);
			// value stores the dice value from the input stream
			int value;
			// tempValues vector stores the temporary dice values
			vector<int> tempValues;

			// inputIsValid stores the boolean value to check if the input is valid
			bool inputIsValid = true;
			// Loop until the end of the input stream
			while (iss >> value)
			{
				if (value < 1 || value > 6)
				{
					cout << "Invalid input! Dice values must be between 1 and 6." << endl;
					inputIsValid = false;
					// Break the loop if the input is not between 1 and 6
					break;
				}
				// Add the dice value to the tempValues vector
				// if the input is between 1 and 6
				tempValues.push_back(value);
			}

			if (!iss.eof())
			{
				cout << "Invalid input! Only numbers separated by spaces are allowed." << endl;
				// Set the input to be invalid if the input stream has not reached the end
				inputIsValid = false;
			}

			if (tempValues.size() != diceCount)
			{
				cout << "You must enter exactly " << diceCount << " dice " << valueOrValues << "." << endl;
				// Set the input to be invalid if the number of dice values entered is not equal to the number of dice
				inputIsValid = false;
			}

			if (inputIsValid)
			{
				// Set the setDiceValues vector to the tempValues vector if the input is valid
				setDiceValues = tempValues;
				// Set the validInput to be true meaning the input is valid
				validInput = true;
			}
			else
			{
				// clear the input stream if the input is invalid to make sure the input stream is empty
				cin.clear();
			}
		}

		// Clear the input buffer just in case (if there's any leftover input)
		cout << "Press enter to continue...";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		// Set the manually entered values
		return setDiceValues;
	}
}

/****************************************************************
 * Function Name: Human::chooseCategory
 * Purpose: To choose the category for the human player
 * Parameters:
 * 			 finalDiceValues, a vector of integers passed by value. it stores the final dice values
 *   			after the human player has chosen to stand or after the third roll
 * Return Value: None
 * Algorithm:
 * 			 1. Check if there are any available categories to choose from
 * 			 2. Display the categories to choose from
 * 			 3. Ask the user if they need help choosing a category
 * 			 4. Display the best category to choose if the user needs help
 * 			 5. Ask the user to choose a category
 * 			 6. Loop until user enters a valid choice
 * 			 7. Set the category the user chose
 * Reference: None
 ****************************************************************/
void Human::chooseCategory(vector<int> finalDiceValues)
{
	// Check if there are any available categories to choose from
	if (ScoreCard::getBestHands(finalDiceValues).first != "")
	{
		// index stores the index of the category
		int index = 0;

		// Display the categories to choose from
		cout << "\nChoose the catergory you want to pursue" << endl;
		for (string category : ScoreCard::getCategoryToChoose(finalDiceValues))
		{
			cout << index + 1 << ") " << category << " - " << ScoreCard::calculatePoints(category, finalDiceValues) << endl;
			index++;
		}

		// needHelp stores the user's choice if they need help choosing a category
		string needHelp;
		do
		{
			cout << "\nDo you need help choosing a category? Enter Y for yes or N for no: ";
			getline(cin, needHelp);

			if (needHelp != "Y" && needHelp != "y" && needHelp != "N" && needHelp != "n")
			{
				cout << "Invalid input!" << endl;
			}
		} while (needHelp != "Y" && needHelp != "y" && needHelp != "N" && needHelp != "n");

		// Display the best category to choose if the user needs help
		if (needHelp == "Y" || needHelp == "y")
		{
			cout << "Computer is helping you choose a category..." << endl;
			// Pause for 2 seconds to mimic the computer helping the user choose a category
			this_thread::sleep_for(chrono::seconds(2));
			// Display the best category to choose
			cout << "You should choose " << ScoreCard::getBestHands(finalDiceValues).first << " with " << ScoreCard::getBestHands(finalDiceValues).second << " points." << endl;
		}

		// validInput stores the boolean value to check if the input is valid
		bool validInput = false;
		// Ask the user to choose a category and loop until user enters a valid choice
		do
		{
			// input stores the user's input for the category
			string input;
			cout << "Enter the number of the category you want to pursue: ";
			getline(cin, input);
			// istringstream object to read the input
			istringstream iss(input);

			// singleDigitRegex stores the regular expression for a single digit
			regex singleDigitRegex("^[0-9]$");
			// indexChoice stores the index of the category the user chose
			int indexChoice;
			// inputValid stores the boolean value to check if the input is valid
			bool inputValid = false;
			// Loop until user enters a valid choice if the input is a single digit
			if (regex_match(input, singleDigitRegex))
			{
				while (iss >> indexChoice)
				{
					if (indexChoice < 1 || indexChoice > index)
					{
						cout << "Invalid input! Please enter a number between 1 and " << index << "." << endl;
						// Set the input to be invalid if the input is not between 1 and the index
						inputValid = false;
					}
					else
					{
						// category stores the category the user chose
						string category = ScoreCard::getCategoryToChoose(finalDiceValues)[indexChoice - 1];
						cout << this->getName() << " chose " << category << " with " << ScoreCard::calculatePoints(category, finalDiceValues) << " points." << endl;
						this_thread::sleep_for(chrono::seconds(1));
						// Set the category the user chose if the input is between 1 and the index
						ScoreCard::chooseCategory(category, finalDiceValues, this->getName(), Round::getRoundNumber());
						// Set the input to be valid if the input is between 1 and the index
						inputValid = true;
					}
				}
			}
			else
			{
				cout << "Invalid input! Please enter a single digit (0-9)." << endl;
				// Set the input to be invalid if the input is not a single digit
				inputValid = false;
			}

			if (inputValid)
			{
				// Set the validInput to be true meaning the input is valid
				validInput = true;
			}
			// Clear the input stream if the input is invalid to make sure the input stream is empty
			cin.clear();
			cout << "Press enter to continue...";
			// Clear the input buffer just in case (if there's any leftover input)
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while (!validInput);
	}
	else
	{
		cout << "No available categories to choose from!" << endl;
	}
}

/****************************************************************
 * Function Name: Human::PlayTurn
 * Purpose: To play the turn for the human player
 * Parameters:
 *         None
 * Return Value: None
 * Algorithm:
 * 			 1. Create a Dice object to roll the dice
 * 			 2. Create vectors to store the rolled dice values, current dice values, and final dice values
 * 			 3. Initialize the roll counter to 1 and the number of dice to 5
 * 			 4. Display the message that the turn has begun
 * 			 5. Loop until the roll counter is less than or equal to 3
 * 			 6. Display the current roll status
 * 			 7. Ask the user if they want to roll the dice randomly or set the values manually
 * 			 8. Display the rolled or manually set dice values
 * 			 9. Set the current dice values
 * 			 10. Display the possible points for the current dice values
 * 			 11. Ask the user if they need help choosing a category
 * 			 12. Display the help message if the user needs help
 * 			 13. Ask the user to stand or roll again
 * 			 14. Keep the recently rolled dice values the user chose to keep
 * 			 15. Display the final dice values if the user chose to stand or after the third roll
 * 			 16. Choose the category if the user chose to stand or after the third roll
 * 			 17. Increment the roll counter
 * 			 18. Display the score card
 * 			 19. Display the message that the turn is over
 * Reference: None
 ****************************************************************/
void Human::playTurn()
{
	// dice object to roll the dice
	Dice dice;
	// rolledDiceValues vector stores the rolled dice values
	vector<int> rolledDiceValues;
	// currentDiceValues vector stores the current dice values
	// after the user rolls the dice
	vector<int> currentDiceValues;
	// finalDiceValues vector stores the final dice values
	// that the user chose to keep
	vector<int> finalDiceValues;

	// rollCounter stores the roll counter
	int rollCounter = 1;
	// diceCount stores the number of dice to roll
	// which is initially set to 5 and will be updated
	int diceCount = 5;

	cout << this->getName() << "'s turn has begun!" << endl;

	// Loop until the roll counter is less than or equal to 3
	// or until the user chooses to stand
	do
	{
		// Display current roll status
		if (rollCounter == 1)
		{
			this_thread::sleep_for(chrono::seconds(1));
			cout << endl;
			ScoreCard::displayAllAvailableCategories();
			cout << "\nFirst roll..." << endl;
		}
		else if (rollCounter == 2)
		{
			rolledDiceValues.clear();
			cout << "\nSecond roll..." << endl;
		}
		else
		{
			rolledDiceValues.clear();
			cout << "\nThird roll..." << endl;
		}

		// rolledDiceValues stores the rolled or manually set dice values based on the user's choice
		rolledDiceValues = rollOrSet(diceCount);

		// Display the rolled or manually set dice values
		cout << this->getName() << " rolled: ";
		for (int value : rolledDiceValues)
		{
			cout << value << " ";
		}
		cout << endl;

		// Set the current dice values
		currentDiceValues.clear();
		if (finalDiceValues.size() > 0)
		{
			// Add the kept dice values to the current dice values
			for (int value : finalDiceValues)
			{
				currentDiceValues.push_back(value);
			}
		}

		// Add the recently rolled dice values to the current dice values
		for (int value : rolledDiceValues)
		{
			currentDiceValues.push_back(value);
		}

		if (rollCounter == 2)
		{
			// Display the current dice values
			cout << "Your new dice values are: ";
			for (int value : currentDiceValues)
			{
				cout << value << " ";
			}
		}

		if (rollCounter < 3)
		{
			// Display the possible points for the current dice values
			ScoreCard::displayPossiblePoints(currentDiceValues);
			string needHelp;

			// Ask the user if they need help and loop until user enters a valid choice
			do
			{
				cout << "\nDo you need help? Enter Y for yes or N for no: ";
				getline(cin, needHelp);

				if (needHelp != "Y" && needHelp != "y" && needHelp != "N" && needHelp != "n")
				{
					cout << "Invalid input!" << endl;
				}
			} while (needHelp != "Y" && needHelp != "y" && needHelp != "N" && needHelp != "n");

			// Display the help message if the user needs help
			if (needHelp == "Y" || needHelp == "y")
			{
				if (rollCounter == 1)
					// suggestions for the first roll
					this->firstRollHelp(currentDiceValues);
				else
					// suggestions for the second roll
					this->secondRollHelp(rolledDiceValues, finalDiceValues);
			}

			// standOrRoll stores the user's choice to stand or roll again
			string standOrRoll;
			// Ask the user to stand or roll again and loop until user enters a valid choice
			do
			{
				cout << "\nDo you want to stand or roll again? Enter S to stand or R to roll again: ";
				getline(cin, standOrRoll);

				if (standOrRoll != "R" && standOrRoll != "r" && standOrRoll != "S" && standOrRoll != "s")
				{
					cout << "Invalid input!" << endl;
				}
			} while (standOrRoll != "R" && standOrRoll != "r" && standOrRoll != "S" && standOrRoll != "s");

			if (standOrRoll == "S" || standOrRoll == "s")
			{
				// update the final dice values
				for (int value : rolledDiceValues)
				{
					finalDiceValues.push_back(value);
				}

				// display the final dice values
				cout << "\nYour final dice values are: ";
				for (int value : finalDiceValues)
				{
					cout << value << " ";
				}
				cout << endl;

				// prompt the user to choose the category
				this->chooseCategory(finalDiceValues);
				// break the loop if the user chooses to stand
				break;
			}
			else
			{
				// diceToRollAgain stores the dice the user chose to roll again
				vector<int> diceToRollAgain;
				// diceToKeep stores the dice the user chose to keep
				vector<int> diceToKeep;
				// validInput stores the boolean value to check if the input is valid
				bool validInput = false;

				// Ask the user to choose the dice they want to roll again
				// and loop until user enters a valid choice
				do
				{
					// input stores the user's input for the dice values
					string input;
					cout << "\nChoose the dice you want to roll again separated by spaces (e.g., 3 5): ";
					getline(cin, input);

					// istringstream object to read the input
					istringstream iss(input);
					// faceValue stores the dice value from the input stream
					int faceValue;
					// inputIsValid stores the boolean value to check if the input is valid
					bool inputIsValid = true;

					// diceAlreadyChosen stores the dice the user already chose to roll again
					vector<int> diceAlreadyChosen;
					// clear the diceAlreadyChosen vector to store the dice values
					diceToRollAgain.clear();

					// Loop until the end of the input stream
					while (iss >> faceValue)
					{
						if (faceValue < 1 || faceValue > 6)
						{
							cout << "Invalid dice value: " << faceValue << ". Must be between 1 and 6." << endl;
							// Set the input to be invalid if the value is not between 1 and 6
							inputIsValid = false;
							continue;
						}

						if (find(rolledDiceValues.begin(), rolledDiceValues.end(), faceValue) == rolledDiceValues.end())
						{
							cout << "Dice with value " << faceValue << " is not in your rolled dice!" << endl;
							// Set the input to be invalid if the value is not in the rolled dice values
							inputIsValid = false;
							continue;
						}

						// count the number of times the value appears in the rolled dice values
						__int64 countInRolledDice = count(rolledDiceValues.begin(), rolledDiceValues.end(), faceValue);
						// count the number of times the value appears in the dice chosen to reroll
						__int64 contChosenToReRoll = count(diceToRollAgain.begin(), diceToRollAgain.end(), faceValue);

						// Check if the number of times the value appears in the dice chosen to reroll
						// is greater than or equal to the number of times the value appears in
						// the rolled dice values
						if (contChosenToReRoll >= countInRolledDice)
						{
							cout << "You can't choose to reroll more dice than you have!" << endl;
							inputIsValid = false;
							continue;
						}

						// Add the dice value to the diceToRollAgain vector
						diceToRollAgain.push_back(faceValue);
					}

					if (inputIsValid && !diceToRollAgain.empty())
					{
						// Set the input to be valid if the input is valid and the dice to reroll is not empty
						validInput = true;

						cout << "You chose to reroll the following dice: ";
						// Display the dice the user chose to reroll
						for (int dice : diceToRollAgain)
						{
							cout << dice << " ";
						}
						cout << endl;

						// clear the diceToKeep vector to store the dice values
						diceToKeep.clear();
						// diceToRemove stores the dice to remove
						vector<int> diceToRemove = diceToRollAgain;

						// Add the dice to keep
						for (int rolledDice : rolledDiceValues)
						{
							auto it = find(diceToRemove.begin(), diceToRemove.end(), rolledDice);

							if (it != diceToRemove.end())
							{
								diceToRemove.erase(it);
							}
							else
							{
								diceToKeep.push_back(rolledDice);
							}
						}

						if (diceToKeep.empty())
						{
							cout << "You chose to reroll all dice from this roll." << endl;
						}
						else
						{
							cout << "You kept the following dice: ";
							for (int dice : diceToKeep)
							{
								finalDiceValues.push_back(dice);
								cout << dice << " ";
							}
							cout << endl;
						}

						// Display the final dice values
						cout << "Your current dice values are: ";
						for (int dice : finalDiceValues)
						{
							cout << dice << " ";
						}
						cout << endl;
					}
					else
					{
						this_thread::sleep_for(chrono::seconds(1));
						cout << "No dice was chosen for reroll." << endl;
					}
					cin.clear();
					cout << "Press enter to continue...";
					// Clear the input buffer just in case (if there's any leftover input)
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				} while (!validInput);
				// Update the dice count to the number of dice to reroll
				diceCount = static_cast<int>(diceToRollAgain.size());
			}
		}
		else
		{
			// Update the final dice values
			for (int value : rolledDiceValues)
			{
				finalDiceValues.push_back(value);
			}
			// Display the final dice values
			cout << "\nYour final dice values are: ";
			for (int value : finalDiceValues)
			{
				cout << value << " ";
			}
			cout << endl;
			// prompt the user to choose the category
			this->chooseCategory(finalDiceValues);
		}
		// Increment the roll counter
		rollCounter++;
	} while (rollCounter <= 3);
	// Display the score card
	ScoreCard::displayScoreCard();
	cout << "\n"
		<< this->getName() << "'s turn is over!" << endl;
}

/****************************************************************
 * Function Name: Computer::playTurn
 * Purpose: To play the turn for the computer player
 * Parameters:
 *         None
 * Return Value: None
 * Algorithm:
 * 			 1. Display the message that the computer's turn has begun.
 * 			 2. Create a Dice object to roll the dice.
 * 			 3. Create vectors to store the rolled dice values, current dice values, and final dice values.
 * 			 4. Initialize the roll counter to 1 and the number of dice to 5.
 * 			 5. Loop until the roll counter is less than or equal to 3:
 * 			    a. Display the current roll status (first, second, or third roll).
 * 			    b. Roll the dice and display the rolled values.
 * 			    c. Add the rolled dice values to the current dice values.
 * 			    d. For the first roll, apply the first roll strategy:
 * 			        i. Determine which dice to keep and which to reroll.
 * 			        ii. If no dice are left to reroll, stand and choose the best category.
 * 			    e. For the second roll, apply the second roll strategy:
 * 			        i. Determine which dice to keep and which to reroll.
 * 			        ii. If no dice are left to reroll, stand and choose the best category.
 * 			    f. For the third roll, finalize the dice and choose the best category.
 * 			 6. Display the final dice and category chosen by the computer.
 * 			 7. Increment the roll counter after each roll.
 * 			 8. Display the score card at the end of the turn.
 * 			 9. Display the message that the computer's turn is over.
 * Reference: None
 ****************************************************************/
void Computer::playTurn()
{
	// Display the message that the computer's turn has begun
	cout << "\n"
		<< this->getName() << "'s turn has begun!" << endl;

	// dice object used to roll the dice
	Dice dice;

	// rolledDiceValues stores the values of the dice rolled in each roll
	vector<int> rolledDiceValues;

	// currentDiceValues stores the current dice values in the game
	vector<int> currentDiceValues;

	// finalDiceValues stores the dice values that the computer decides to keep
	vector<int> finalDiceValues;

	// rollCounter keeps track of the number of rolls (up to three)
	int rollCounter = 1;

	// diceCount stores the number of dice to be rolled in each turn
	int diceCount = 5;

	do
	{
		// Display the current roll status based on the roll counter
		if (rollCounter == 1)
		{
			this_thread::sleep_for(chrono::seconds(1)); // Pause for 1 second
			cout << endl;
			// Display all available categories to the computer
			ScoreCard::displayAllAvailableCategories();
			// Inform that the first roll is happening
			cout << "\nFirst roll..." << endl;
		}
		else if (rollCounter == 2)
		{
			// Inform that the second roll is happening
			cout << "\nSecond roll..." << endl;
		}
		else
		{
			// Inform that the third roll is happening
			cout << "\nThird roll..." << endl;
		}

		// rolledDiceValues stores the results of rolling the dice
		rolledDiceValues = rollOrSet(diceCount);

		// Display the rolled dice values
		cout << "Computer rolled: ";
		for (int value : rolledDiceValues)
		{
			cout << value << " ";
		}
		cout << endl;

		// If the computer has kept dice, update currentDiceValues with the final kept dice
		if (finalDiceValues.size() > 0)
		{
			for (int value : finalDiceValues)
			{
				currentDiceValues.push_back(value);
			}
		}

		// Add the recently rolled dice values to the current dice values
		for (int value : rolledDiceValues)
		{
			currentDiceValues.push_back(value);
		}

		// If it's the first roll, apply the first roll strategy
		if (rollCounter == 1)
		{
			// temp stores the result of the first roll move (kept dice and dice to reroll)
			pair<vector<int>, vector<int>> temp = firstRollMove(currentDiceValues);

			// finalDiceValues stores the dice values that the computer decides to keep
			finalDiceValues = temp.first;

			// diceToRollAgain stores the dice values that the computer decides to reroll
			vector<int> diceToRollAgain = temp.second;

			// If no dice are left to reroll, the computer stands with the current dice
			if (temp.second.size() == 0)
			{
				// bestHand stores the name of the best category for the current dice
				string bestHand = ScoreCard::getBestHands(finalDiceValues).first;

				// points stores the points that the computer can score based on the current dice
				int points = ScoreCard::getBestHands(finalDiceValues).second;

				// Display the final dice values
				cout << "Computer's final dice is as follows: ";
				for (int dice : finalDiceValues)
				{
					cout << dice << " ";
				}
				cout << endl;

				// If the points are greater than 0, choose the best category and stand
				if (points > 0)
				{
					ScoreCard::chooseCategory(bestHand, finalDiceValues, this->getName(), Round::getRoundNumber());
					cout << "\nComputer chose to stand with " << bestHand << " with " << points << " points!" << endl;
				}
				else
				{
					// Inform that no category is available to choose from
					cout << "No category to choose for computer!" << endl;
				}
				break; // End the turn as the computer stands
			}
			else
			{
				// Display the dice that the computer chose to keep
				cout << "\nComputer chose to keep the following dice: ";
				for (int dice : finalDiceValues)
				{
					cout << dice << " ";
				}
				cout << endl;

				// Display the dice that the computer chose to reroll
				cout << "\nComputer chose to reroll the following dice: ";
				for (int dice : diceToRollAgain)
				{
					cout << dice << " ";
				}
				cout << endl;

				// Update diceCount to reflect the number of dice to reroll
				diceCount = static_cast<int>(diceToRollAgain.size());
			}
		}
		// If it's the second roll, apply the second roll strategy
		else if (rollCounter == 2)
		{
			// temp stores the result of the second roll move (kept dice and dice to reroll)
			pair<vector<int>, vector<int>> temp = secondRollMove(rolledDiceValues, finalDiceValues);

			// finalDiceValues stores the dice values that the computer decides to keep
			finalDiceValues = temp.first;

			// diceToRollAgain stores the dice values that the computer decides to reroll
			vector<int> diceToRollAgain = temp.second;

			// If no dice are left to reroll, the computer stands with the current dice
			if (temp.second.size() == 0)
			{
				// bestHand stores the name of the best category for the current dice
				string bestHand = ScoreCard::getBestHands(finalDiceValues).first;

				// points stores the points that the computer can score based on the current dice
				int points = ScoreCard::getBestHands(finalDiceValues).second;

				// Display the final dice values
				cout << "Computer's final dice is as follows: ";
				for (int dice : finalDiceValues)
				{
					cout << dice << " ";
				}
				cout << endl;

				// If the points are greater than 0, choose the best category and stand
				if (points > 0)
				{
					ScoreCard::chooseCategory(bestHand, finalDiceValues, this->getName(), Round::getRoundNumber());
					cout << "\nComputer chose to stand with " << bestHand << " with " << points << " points!" << endl;
				}
				else
				{
					// Inform that no category is available to choose from
					cout << "No category to choose for computer!" << endl;
				}
				break; // End the turn as the computer stands
			}
			else
			{
				// Display the dice that the computer chose to keep
				cout << "\nComputer chose to keep the following dice: ";
				for (int dice : finalDiceValues)
				{
					cout << dice << " ";
				}
				cout << endl;

				// Display the dice that the computer chose to reroll
				cout << "\nComputer chose to reroll the following dice: ";
				for (int dice : diceToRollAgain)
				{
					cout << dice << " ";
				}
				cout << endl;

				// Update diceCount to reflect the number of dice to reroll
				diceCount = static_cast<int>(diceToRollAgain.size());
			}
		}
		// If it's the third roll, finalize the turn with no rerolls left
		else
		{
			// Add the current roll's dice values to the final dice values
			for (int die : rolledDiceValues)
			{
				finalDiceValues.push_back(die);
			}

			// Display the final dice values after the third roll
			cout << "Computer's final dice is as follows: ";
			for (int dice : finalDiceValues)
			{
				cout << dice << " ";
			}

			// bestHand stores the name of the best category for the current dice
			string bestHand = ScoreCard::getBestHands(finalDiceValues).first;

			// currentMaximumPoints stores the maximum points the computer can score with the current dice values
			int currentMaximumPoints = ScoreCard::getBestHands(finalDiceValues).second;

			// If a category is available, display the possible points and best category
			if (bestHand != "")
			{
				ScoreCard::displayPossiblePoints(finalDiceValues);
				cout << "Computer's best category after this roll is: " << bestHand << " with " << currentMaximumPoints << " points." << endl;
			}

			// points stores the points that the computer can score based on the current dice
			int points = ScoreCard::getBestHands(finalDiceValues).second;

			// If points are available, choose the best category
			if (points > 0)
			{
				ScoreCard::chooseCategory(bestHand, finalDiceValues, this->getName(), Round::getRoundNumber());
				cout << "\nComputer chose to stand with " << bestHand << " with " << points << " points!" << endl;
			}
			else
			{
				// Inform that no category is available to choose from
				cout << "No category to choose for computer!" << endl;
			}

			// End the turn after the third roll
			break;
		}

		this_thread::sleep_for(chrono::seconds(1)); // Pause for 1 second before the next roll
		rollCounter++;															// Increment the roll counter
	} while (rollCounter <= 3);

	// Display the score card at the end of the turn
	ScoreCard::displayScoreCard();

	// Display a message that the computer's turn is over
	cout << "\n"
		<< this->getName() << "'s turn is over!\n"
		<< endl;
}

/****************************************************************
 * Function Name: Computer::firstRollMove
 * Purpose: To determine the computer's strategy for the first roll
 * Parameters:
 *         currentDiceValues, a vector of integers passed by value. it stores the current dice values
 * Return Value: A pair of vectors of integers
 * 				 The first vector stores the dice values the computer chose to keep
 * 				 The second vector stores the dice values the computer chose to roll again
 * Algorithm:
 * 			 1. Get the best category for the current dice values
 * 			 2. Get the maximum points for the best category
 * 			 3. Display the possible points for the current dice values and the best category
 * 			 4. Check if the best category is Yahtzee
 *          4.1. Display message that computer chose to stand with Yahtzee
 *          4.2. Keep all dice values
 * 			 5. Check if the best category is Five Straight
 *          5.1. Display message that computer chose to stand with Five Straight
 *          5.2. Keep all dice values
 * 			 6. Check if the best category is Four Straight
 *           6.1. Check if Five Straight is available
 * 				 	 6.2. If not available, display message and keep all dice values
 * 				 	 6.3. If available, pursue Five Straight
 * 				 	 6.4. Roll one of the identical dice if two of the dice are the same
 * 				 	 6.5. Roll the last dice if the first two dice values are 1 and 2, keep the first four dice values
 * 				 	 6.6. Otherwise, roll the first dice and keep the last four dice values
 * 			 7. Check if the best category is Full House
 *          7.1. Display message that computer chose to stand with Full House
 *          7.2. Keep all dice values
 * 			 8. Check if the best category is Four of a Kind
 *          8.1. Store the count of each dice value
 *          8.2. Store the non-four kind value and the four kind value
 *          8.3. If Yahtzee is available, attempt to go for Yahtzee by rerolling the remaining die
 *          8.4. If non-four kind value is not 6, reroll it to try to get a higher die
 *          8.5. If non-four kind value is 6, stand with Four of a Kind
 * 			 9. Check if the best category is Three of a Kind
 *          9.1. Store the three kind value
 *          9.2. If current maximum points are greater than Full House points, stand with Three of a Kind
 *          9.3. If Yahtzee or Full House is available, pursue them
 *          9.4. If neither is available, reroll to try to get higher die values
 * 			 10. Check if the best category is Aces, Twos, Threes, Fours, Fives, or Sixes
 *          10.1. Store the target value
 *          10.2. If all dice values are the same, keep all dice
 *          10.3. If there are two pairs and Full House is available, pursue Full House
 *          10.4. If there is one pair and Five Straight is available, pursue Five Straight
 *          10.5. If Yahtzee, Four of a Kind, Three of a Kind, or Full House is available, pursue them
 *          10.6. Otherwise, reroll non-target values to try to get a better hand
 * 			 11. If no pairs are found, pursue a Straight if available, otherwise reroll all dice
 * 			 12. If Yahtzee is available, pursue Yahtzee
 * 			 13. If Full House is available, pursue Full House
 * 			 14. Otherwise, reroll all dice to try to get a better hand
 * 			 15. Return the pair of vectors of integers
 * Reference: Brainstormed with the help of ChatGPT.
 ****************************************************************/
pair<vector<int>, vector<int>> Computer::firstRollMove(const vector<int> currentDiceValues)
{
	// diceToRollAgain stores the dice values that the computer decides to reroll in the next round
	vector<int> diceToRollAgain;

	// diceToKeep stores the dice values that the computer decides to keep based on the best category and strategy
	vector<int> diceToKeep;

	// bestCategory stores the name of the best scoring category for the current dice combination
	string bestCategory = ScoreCard::getBestHands(currentDiceValues).first;

	// currentMaximumPoints stores the maximum points the computer can score with the current dice values
	int currentMaximumPoints = ScoreCard::getBestHands(currentDiceValues).second;

	// diceCount stores the count of occurrences of each dice value to help in decision-making
	map<int, int> diceCount;
	for (int value : currentDiceValues)
	{
		// Increment the count for each dice value
		diceCount[value]++;
	}

	// If there is a viable category to score in, display the possible points and best category
	if (bestCategory != "")
	{
		// Display the possible points based on current dice values
		ScoreCard::displayPossiblePoints(currentDiceValues);

		// Inform the best category and possible points after the current roll
		cout << "Computer's best category after this roll is: " << bestCategory << " with " << currentMaximumPoints << " points." << endl;
	}
	else
	{
		// Inform that there are no available categories for the computer to choose from
		cout << "Computer has no available categories to choose from!" << endl;
	}

	// If the best category is Yahtzee, diceToKeep stores all dice and no rerolls are needed
	if (bestCategory == "Yahtzee")
	{
		// Inform that the computer chose to stand with Yahtzee
		cout << "Computer chose to stand with Yahtzee! 50 points for computer!" << endl;

		// Store all current dice values as dice to keep
		diceToKeep = currentDiceValues;

		// Return the kept dice and no rerolls
		return make_pair(diceToKeep, diceToRollAgain);
	}
	// If the best category is Five Straight, diceToKeep stores all dice values
	else if (bestCategory == "Five Straight")
	{
		// Inform that the computer chose to stand with Five Straight
		cout << "Computer chose to stand with Five straight! 40 points for computer!" << endl;

		// Store all current dice values as dice to keep
		diceToKeep = currentDiceValues;

		// Return the kept dice and no rerolls
		return make_pair(diceToKeep, diceToRollAgain);
	}
	// If the best category is Four Straight, determine if the computer can pursue Five Straight
	else if (bestCategory == "Four Straight")
	{
		// temp stores the unique dice values to check for straight combinations
		set<int> temp;

		// If Five Straight is not available, diceToKeep stores all dice and no rerolls are needed
		if (!ScoreCard::isCategoryAvailable("Five Straight"))
		{
			// Inform that the computer will stand as Five Straight is not available
			cout << "\nComputer will stand on this as Five Straight is not available!" << endl;

			// Store all current dice values as dice to keep
			diceToKeep = currentDiceValues;
		}
		else
		{
			// Inform that the computer wants to pursue Five Straight
			cout << "\nComputer wants to pursue Five Straight!" << endl;

			// Add current dice values to temp to check for straight possibilities
			for (int value : currentDiceValues)
			{
				temp.insert(value);
			}

			// If two of the dice are the same, reroll one of the identical dice
			if (temp.size() == 4)
			{
				for (int dice : temp)
				{
					// If there are two identical dice, reroll one of them
					if (count(currentDiceValues.begin(), currentDiceValues.end(), dice) == 2)
					{
						diceToRollAgain.push_back(dice); // Add the identical dice to reroll
					}
					// Keep the other identical dice
					diceToKeep.push_back(dice);
				}
			}
			else
			{
				// Sort the dice values to check the sequence for potential straights
				vector<int> sortedDice = currentDiceValues;
				sort(sortedDice.begin(), sortedDice.end());

				// If the first two dice values are 1 and 2, reroll the last dice
				if (sortedDice[0] == 1 && sortedDice[1] == 2)
				{
					// Add the last dice to reroll
					diceToRollAgain.push_back(sortedDice[4]);

					// Keep the first four dice values
					for (int i = 0; i < 4; i++)
					{
						diceToKeep.push_back(sortedDice[i]);
					}
				}
				else
				{
					// Reroll the first dice
					diceToRollAgain.push_back(sortedDice[0]);

					// Keep the last four dice values
					for (int i = 1; i < 5; i++)
					{
						diceToKeep.push_back(sortedDice[i]);
					}
				}
			}
		}
		// Return the dice to keep and reroll
		return make_pair(diceToKeep, diceToRollAgain);
	}
	// If the best category is Full House, diceToKeep stores all dice values and no rerolls are needed
	else if (bestCategory == "Full House")
	{
		// Inform that the computer chose to stand with Full House
		cout << "Computer chose to stand with Full House! 25 points for computer!" << endl;

		// Store all current dice values as dice to keep
		diceToKeep = currentDiceValues;

		// Return the kept dice and no rerolls
		return make_pair(diceToKeep, diceToRollAgain);
	}
	// If the best category is Four of a Kind, reroll non-four-kind dice or stand depending on strategy
	else if (bestCategory == "Four of a Kind")
	{
		// nonFourKindValue stores the value of the dice that is not part of the four of a kind
		int nonFourKindValue = -1;

		// fourKindValue stores the value of the dice that appears four times
		int fourKindValue = -1;

		// Identify which dice forms the four of a kind and which one doesn't
		for (const auto& pair : diceCount)
		{
			if (pair.second == 1)
			{
				nonFourKindValue = pair.first;
			}
			else
			{
				fourKindValue = pair.first;
			}
		}

		// If Yahtzee is available, reroll the non-four-kind dice to attempt for Yahtzee
		if (nonFourKindValue != -1)
		{
			if (ScoreCard::isCategoryAvailable("Yahtzee"))
			{
				// Inform that the computer is attempting to go for Yahtzee by rerolling the remaining die
				cout << "\nComputer is attempting to go for Yahtzee by rerolling the remaining die!\n";

				// Add the four-of-a-kind dice to keep and reroll the other die
				for (int die : currentDiceValues)
				{
					if (die == fourKindValue)
					{
						diceToKeep.push_back(die); // Keep the four-of-a-kind dice
					}
					else
					{
						diceToRollAgain.push_back(die); // Add the non-matching die to reroll
					}
				}
			}
			// If Yahtzee is not available and the non-four-kind value is not 6, reroll it
			else if (nonFourKindValue != 6)
			{
				// Inform that the computer chose to reroll the non-four of a kind value to try to get a higher die
				cout << "Computer chose to reroll the non-four of a kind value to try to get a higher die: " << nonFourKindValue << endl;

				// Add the non-four-kind dice to reroll
				diceToRollAgain.push_back(nonFourKindValue);

				// Keep the four-of-a-kind dice
				for (int die : currentDiceValues)
				{
					if (die == fourKindValue)
					{
						diceToKeep.push_back(die);
					}
				}
			}
			// If the non-four-kind value is 6, the computer chooses to stand
			else
			{
				// Inform that the computer chose to stand
				cout << "Computer chose to stand on this as the non-four of a kind value is 6 and Yahtzee is not available!" << endl;

				// Keep all current dice values
				diceToKeep = currentDiceValues;
			}
		}
		else
		{
			// If the current dice values are all smaller than 4, reroll one of the non-matching dice
			if (currentDiceValues[0] < 4)
			{
				// Inform that the computer chose to reroll to try to get a higher die to add to the sum
				cout << "\nComputer chose to reroll to try to get a higher die to add to the sum!" << endl;

				// Keep the first four dice values
				for (int i = 0; i < 4; i++)
				{
					diceToKeep.push_back(currentDiceValues[i]);
				}
				// Add the last dice to reroll
				diceToRollAgain.push_back(currentDiceValues[4]);
			}
			else
			{
				// Inform that the computer chose to stand with Four of a Kind
				cout << "\nComputer chose to stand with Four of a Kind!" << endl;

				// Keep all current dice values
				for (int die : currentDiceValues)
				{
					diceToKeep.push_back(die);
				}
			}
		}
		// Return the dice to keep and reroll
		return make_pair(diceToKeep, diceToRollAgain);
	}
	// If the best category is Three of a Kind, execute Three of a Kind strategy
	else if (bestCategory == "Three of a Kind")
	{
		// threeKindValue stores the value of the dice that appears at least three times
		int threeKindValue = -1;

		// Find the value that appears three or more times
		for (const auto& pair : diceCount)
		{
			if (pair.second >= 3)
			{
				threeKindValue = pair.first;
			}
		}

		// fullHousePoints stores the points for Full House based on current dice values
		int fullHousePoints = ScoreCard::calculatePoints("Full House", currentDiceValues);

		// If the maximum points exceed Full House points and Full House is 25 points, stand with Three of a Kind
		if (currentMaximumPoints > fullHousePoints && fullHousePoints == 25)
		{
			// Inform that the computer chose to stand with Three of a Kind
			cout << "Computer chose to stand with Three of a Kind as it is greater" << endl;

			// Keep all current dice values
			diceToKeep = currentDiceValues;

			// Return the kept dice and no rerolls
			return make_pair(diceToKeep, diceToRollAgain);
		}

		// If Yahtzee or Full House is available, attempt to go for Yahtzee or Full House
		if (ScoreCard::isCategoryAvailable("Yahtzee") || ScoreCard::isCategoryAvailable("Full House"))
		{
			// If both Yahtzee and Full House are available, attempt to go for one
			if (ScoreCard::isCategoryAvailable("Yahtzee") && ScoreCard::isCategoryAvailable("Full House"))
			{
				// Inform the computer's decision to pursue either category
				if (diceCount[threeKindValue] == 3)
				{
					cout << "\nComputer is attempting to go for Yahtzee or Full House!\n";
				}
				else
				{
					cout << "\nComputer is attempting to go for Yahtzee!\n";
				}

				// Keep the dice that match the Three of a Kind value and reroll others
				for (int die : currentDiceValues)
				{
					if (die == threeKindValue)
					{
						diceToKeep.push_back(die);
					}
					else
					{
						diceToRollAgain.push_back(die);
					}
				}
			}
			// If only Yahtzee is available, attempt to go for Yahtzee
			else if (ScoreCard::isCategoryAvailable("Yahtzee") && !ScoreCard::isCategoryAvailable("Full House"))
			{
				// Inform that the computer is attempting to go for Yahtzee
				cout << "\nComputer is attempting to go for Yahtzee!\n";

				// Keep the dice that match the Three of a Kind value and reroll others
				for (int die : currentDiceValues)
				{
					if (die == threeKindValue)
					{
						diceToKeep.push_back(die);
					}
					else
					{
						diceToRollAgain.push_back(die);
					}
				}
			}
			// If only Full House is available, pursue Full House
			else
			{
				// Inform that the computer wants to pursue Full House
				cout << "\nComputer wants to pursue Full House!" << endl;

				// max stores the highest dice value
				int max = *max_element(currentDiceValues.begin(), currentDiceValues.end());

				// Keep the three-of-a-kind dice and the highest other dice
				if (max == threeKindValue)
				{
					for (int die : currentDiceValues)
					{
						if (die == threeKindValue)
						{
							diceToKeep.push_back(die);
						}
						else
						{
							diceToRollAgain.push_back(die);
						}
					}
				}
				else
				{
					// Keep the three-of-a-kind dice and the highest remaining dice
					int count = 0;
					for (int die : currentDiceValues)
					{
						if (die == threeKindValue && count < 3)
						{
							diceToKeep.push_back(die);
							count++;
						}
						else if (die == max)
						{
							diceToKeep.push_back(die);
						}
						else
						{
							diceToRollAgain.push_back(die);
						}
					}
				}
			}
		}
		// If neither Yahtzee nor Full House is available, reroll the remaining dice
		else
		{
			// Keep the dice that match the Three of a Kind value and reroll others
			for (int value : currentDiceValues)
			{
				if (diceCount[value] <= 2)
				{
					if (value < 6)
					{
						diceToRollAgain.push_back(value); // Reroll lower dice values
					}
					else
					{
						diceToKeep.push_back(value); // Keep higher dice values
					}
				}
				else
				{
					diceToKeep.push_back(value); // Keep the three-of-a-kind dice
				}
			}

			// Inform that the computer is rerolling for a better hand
			if (diceToRollAgain.size() > 0)
			{
				cout << "Computer decided to roll again to try and get higher die value!";
			}
			else
			{
				cout << "Computer decided to stand with Three of a Kind!";
			}
		}

		// Return the dice to keep and reroll
		return make_pair(diceToKeep, diceToRollAgain);
	}
	// If the best category is Aces, Twos, Threes, Fours, Fives, or Sixes, execute lower number strategy
	else if (bestCategory == "Aces" || bestCategory == "Twos" || bestCategory == "Threes" || bestCategory == "Fours" || bestCategory == "Fives" || bestCategory == "Sixes")
	{
		// targetValue stores the target dice value that the computer is pursuing
		int targetValue = -1;

		// Assign the target value based on the best category
		if (bestCategory == "Aces")
			targetValue = 1;
		else if (bestCategory == "Twos")
			targetValue = 2;
		else if (bestCategory == "Threes")
			targetValue = 3;
		else if (bestCategory == "Fours")
			targetValue = 4;
		else if (bestCategory == "Fives")
			targetValue = 5;
		else if (bestCategory == "Sixes")
			targetValue = 6;

		// pairs stores dice values that appear in pairs
		vector<int> pairs;

		// nonPairs stores dice values that do not appear in pairs
		vector<int> nonPairs;

		// isStraightPossible stores whether a straight is possible
		bool isStraightPossible = false;

		// Count the number of pairs and non-pairs
		for (const auto& pair : diceCount)
		{
			if (pair.second >= 2)
			{
				pairs.push_back(pair.first);
			}
			else if (pair.second == 1)
			{
				nonPairs.push_back(pair.first);
			}
		}

		// If there is only one pair, check for possible straights
		if (pairs.size() == 1)
		{
			vector<int> sortedDice = currentDiceValues;
			set<int> temp(currentDiceValues.begin(), currentDiceValues.end());

			// Define potential straight sequences
			vector<int> straight = { 1, 2, 3, 4, 5 };
			vector<int> straight2 = { 2, 3, 4, 5, 6 };

			// Check if a straight is possible
			int count = 0;
			for (int die : temp)
			{
				if (find(straight.begin(), straight.end(), die) != straight.end())
				{
					count++;
				}
			}

			// If four dice match a straight, mark straight as possible
			if (count == 4)
			{
				isStraightPossible = true;
			}
			else
			{
				count = 0;
				for (int die : temp)
				{
					if (find(straight2.begin(), straight2.end(), die) != straight2.end())
					{
						count++;
					}
				}
				if (count == 4)
				{
					isStraightPossible = true;
				}
			}
		}

		// If all the dice values are the same, the computer keeps all dice
		if (diceCount.size() == 1)
		{
			cout << "Computer chose to keep all dice as they are all the same value.\n";
			diceToKeep = currentDiceValues;
		}
		// If two pairs exist and Full House is available, pursue Full House
		else if (pairs.size() == 2 && ScoreCard::isCategoryAvailable("Full House"))
		{
			cout << "Computer is pursuing Full House!" << endl;
			for (int die : currentDiceValues)
			{
				if (die == pairs[0] || die == pairs[1])
				{
					diceToKeep.push_back(die);
				}
				else
				{
					diceToRollAgain.push_back(die);
				}
			}
		}
		// If one pair exists, consider pursuing straights or other categories
		else if (pairs.size() == 1)
		{
			// If Five Straight is possible, pursue it
			if (ScoreCard::isCategoryAvailable("Five Straight") && isStraightPossible)
			{
				cout << "Computer is pursuing Five Straight!" << endl;
				int count = 0;
				for (int die : currentDiceValues)
				{
					if (die == pairs[0] && count < 1)
					{
						diceToRollAgain.push_back(die);
						count++;
					}
					else
					{
						diceToKeep.push_back(die);
					}
				}
			}
			// If Yahtzee, Four of a Kind, Three of a Kind, or Full House is available, pursue them
			else if (ScoreCard::isCategoryAvailable("Yahtzee") || ScoreCard::isCategoryAvailable("Four of a Kind") || ScoreCard::isCategoryAvailable("Three of a Kind") || ScoreCard::isCategoryAvailable("Full House"))
			{
				cout << "Computer is pursuing ";

				if (ScoreCard::isCategoryAvailable("Yahtzee"))
				{
					cout << "Yahtzee | ";
				}
				if (ScoreCard::isCategoryAvailable("Four of a Kind"))
				{
					cout << "Four of a Kind | ";
				}
				if (ScoreCard::isCategoryAvailable("Three of a Kind"))
				{
					cout << "Three of a Kind | ";
				}
				if (ScoreCard::isCategoryAvailable("Full House"))
				{
					cout << "Full House | ";
				}

				for (int die : currentDiceValues)
				{
					if (die == pairs[0])
					{
						diceToKeep.push_back(die);
					}
					else
					{
						diceToRollAgain.push_back(die);
					}
				}
			}
			// If no other categories are available, reroll non-target dice
			else
			{
				cout << "Computer is rolling the non-target value to try to get a better hand!" << endl;
				for (int die : currentDiceValues)
				{
					if (die == targetValue)
					{
						diceToKeep.push_back(die);
					}
					else
					{
						diceToRollAgain.push_back(die);
					}
				}
			}
		}
		// If no pairs exist, reroll all dice to pursue better hands
		else
		{
			bool hasNoPairs = true;
			for (const auto& pair : diceCount)
			{
				if (pair.second >= 2)
				{
					hasNoPairs = false;
					break;
				}
			}

			if (hasNoPairs)
			{
				// If a straight is possible, reroll dice to pursue it
				if (ScoreCard::isCategoryAvailable("Four Straight") || ScoreCard::isCategoryAvailable("Five Straight"))
				{
					cout << "No pairs found, attempting to pursue a Straight!" << endl;

					for (int value : currentDiceValues)
					{
						if (value == 1)
						{
							diceToRollAgain.push_back(value);
						}
						else
						{
							diceToKeep.push_back(value);
						}
					}

					if (diceToRollAgain.size() > 0)
					{
						cout << "Computer is rerolling Aces to pursue a straight.\n";
					}
				}
				else
				{
					cout << "No pairs found, rerolling all dice to try to get a better hand!" << endl;
					diceToRollAgain = currentDiceValues;
				}
			}
			else
			{
				// If pairs are present, reroll non-target dice
				for (int value : currentDiceValues)
				{
					if (value == targetValue)
					{
						diceToKeep.push_back(value);
					}
					else
					{
						diceToRollAgain.push_back(value);
					}
				}
				cout << "Computer is rerolling to try to get more " << targetValue << "'s.\n";
			}
		}

		// Return the dice to keep and reroll
		return make_pair(diceToKeep, diceToRollAgain);
	}
	// If no specific category is identified, reroll all dice
	else
	{
		bool hasPairs = false;

		// Check if there are any pairs in the current dice values
		for (int value : currentDiceValues)
		{
			if (diceCount[value] >= 2)
			{
				hasPairs = true;
				break;
			}
		}

		// If Yahtzee is available, reroll non-paired dice to attempt Yahtzee
		if (ScoreCard::isCategoryAvailable("Yahtzee"))
		{
			if (hasPairs)
			{
				cout << "Computer is pursuing Yahtzee!" << endl;
				int count = 0;
				bool moreThanTwoSame = false;

				for (int die : currentDiceValues)
				{
					if (diceCount[die] > 2)
					{
						moreThanTwoSame = true;
						break;
					}
				}

				if (moreThanTwoSame)
				{
					for (int die : currentDiceValues)
					{
						if (diceCount[die] > 2)
						{
							diceToKeep.push_back(die);
						}
						else
						{
							diceToRollAgain.push_back(die);
						}
					}
				}
				else
				{
					vector<int> sortedDice = currentDiceValues;
					sort(sortedDice.begin(), sortedDice.end());

					for (int die : sortedDice)
					{
						if (diceCount[die] >= 2 and count < 2)
						{
							diceToKeep.push_back(die);
							count++;
						}
						else
						{
							diceToRollAgain.push_back(die);
						}
					}
				}
			}
			else
			{
				cout << "Computer is rolling all the die again to try to get Yahtzee!" << endl;
				diceToRollAgain = currentDiceValues;
			}
		}
		// If Full House is available, reroll non-paired dice to pursue Full House
		else if (ScoreCard::isCategoryAvailable("Full House"))
		{
			if (hasPairs)
			{
				cout << "Computer is pursuing Full House!" << endl;
				for (int die : currentDiceValues)
				{
					if (diceCount[die] >= 2)
					{
						diceToKeep.push_back(die);
					}
					else
					{
						diceToRollAgain.push_back(die);
					}
				}
			}
			else
			{
				cout << "Computer is rolling all the die again to try to get Full House!" << endl;
				diceToRollAgain = currentDiceValues;
			}
		}
		// If neither Yahtzee nor Full House is available, reroll all dice to pursue a better hand
		else
		{
			cout << "Computer is rolling all the die again to try to get a better hand!" << endl;
			diceToRollAgain = currentDiceValues;
		}

		// Return the dice to keep and reroll
		return make_pair(diceToKeep, diceToRollAgain);
	}
}

/****************************************************************
 * Function Name: Computer::secondRollMove
 * Purpose: To determine the computer's strategy for the second roll
 * Parameters:
 *         rolledDice, a vector of integers passed by value. It stores the dice values that were rolled in the second roll
 *         keptDice, a vector of integers passed by value. It stores the dice values the computer chose to keep from the first roll
 * Return Value: A pair of vectors of integers
 *                 The first vector stores the dice values the computer chose to keep
 *                 The second vector stores the dice values the computer chose to roll again
 * Algorithm:
 *             1. Combine keptDice and rolledDice into currentDiceValues
 *             2. Count the occurrences of each die value in currentDiceValues
 *             3. Determine the best category and its maximum points using ScoreCard::getBestHands
 *             4. Display possible points and the best category
 *             5. If the best category is Yahtzee:
 *                 5.1. Display message that computer stands with Yahtzee
 *                 5.2. Keep all dice
 *             6. Else if the best category is Five Straight:
 *                 6.1. Display message that computer stands with Five Straight
 *                 6.2. Keep all dice
 *             7. Else if the best category is Four Straight:
 *                 7.1. If Five Straight is not available:
 *                     7.1.1. Display message and keep all dice
 *                 7.2. Else:
 *                     7.2.1. Display message to pursue Five Straight
 *                     7.2.2. Insert dice values into a temporary set
 *                     7.2.3. If there are exactly four unique dice values:
 *                         7.2.3.1. Identify the duplicate die value
 *                         7.2.3.2. If the duplicate can be rerolled:
 *                             7.2.3.2.1. Reroll it and keep the rest
 *                         7.2.3.3. Else, stand with Four Straight
 *                     7.2.4. Else:
 *                         7.2.4.1. Sort the dice
 *                         7.2.4.2. Determine which die to reroll to achieve Five Straight
 *                         7.2.4.3. If the first two dice are 1 and 2 and the last die can be rerolled, reroll it
 *                         7.2.4.4. Else, reroll the first die if possible
 *             8. Else if the best category is Full House:
 *                 8.1. Display message that computer stands with Full House
 *                 8.2. Keep all dice
 *             9. Else if the best category is Four of a Kind:
 *                 9.1. Identify the non-four kind die
 *                 9.2. If Yahtzee is available:
 *                     9.2.1. If the non-four kind die can be rerolled:
 *                         9.2.1.1. Reroll it to pursue Yahtzee
 *                         9.2.1.2. Keep other dice
 *                     9.2.2. Else, stand with Four of a Kind
 *                 9.3. Else:
 *                     9.3.1. If the non-four kind die is not 6:
 *                         9.3.1.1. If it can be rerolled:
 *                             9.3.1.1.1. Reroll it to try to get a higher die
 *                             9.3.1.1.2. Keep other dice
 *                         9.3.1.2. Else, stand with Four of a Kind
 *                     9.3.2. Else, stand with Four of a Kind
 *             10. Else if the best category is Three of a Kind:
 *                 10.1. Identify the three kind die
 *                 10.2. Calculate Full House points
 *                 10.3. If current maximum points are greater than Full House points and Full House is 25:
 *                     10.3.1. Display message and stand with Three of a Kind
 *                     10.3.2. Keep all dice
 *                 10.4. If Yahtzee or Full House is available:
 *                     10.4.1. If both Yahtzee and Full House are available:
 *                         10.4.1.1. If three kind count is exactly 3:
 *                             10.4.1.1.1. Check if non-three kind dice can be rerolled
 *                             10.4.1.1.2. If both can be rerolled, pursue Yahtzee or Full House
 *                             10.4.1.1.3. Else if at least one can be rerolled, reroll accordingly
 *                             10.4.1.1.4. Else, stand with Three of a Kind
 *                         10.4.1.2. Else:
 *                             10.4.1.2.1. Check and reroll to pursue Yahtzee or Full House
 *                     10.4.2. Else if only Yahtzee is available:
 *                         10.4.2.1. Reroll non-three kind dice to pursue Yahtzee if possible
 *                         10.4.2.2. Else, stand with Three of a Kind
 *                     10.4.3. Else if only Full House is available:
 *                         10.4.3.1. Reroll non-three kind dice to pursue Full House if possible
 *                         10.4.3.2. Else, stand with Three of a Kind
 *                     10.4.4. Else, check and reroll to pursue Full House
 *                 10.5. Else, stand with Three of a Kind
 *                 10.6. Else, check and reroll to pursue Full House
 *             11. Else if the best category is one of the upper sections (Aces, Twos, Threes, Fours, Fives, Sixes):
 *                 11.1. Identify the target die value
 *                 11.2. Identify pairs and non-pairs in the dice count
 *                 11.3. If there is one pair:
 *                     11.3.1. If pursuing categories like Yahtzee, Four of a Kind, Three of a Kind, or Full House:
 *                         11.3.1.1. Display message and keep the pair dice, reroll others
 *                     11.3.2. Else, reroll non-target values to try to get a better hand
 *                 11.4. Else if there are two pairs and Full House is available:
 *                     11.4.1. Display message and keep the pairs, reroll the rest
 *                 11.5. Else if there are no pairs:
 *                     11.5.1. If a Straight is available, attempt to pursue it by rerolling specific dice
 *                     11.5.2. Else, reroll all dice to try to get a better hand
 *                 11.6. Else, keep target dice and reroll others
 *             12. Else, handle cases with no pairs:
 *                 12.1. If a Straight is available, attempt to pursue it by rerolling specific dice
 *                 12.2. Else, reroll all dice to try to get a better hand
 *             13. If Yahtzee is available and not pursued yet, attempt to pursue Yahtzee by keeping the most frequent die
 *             14. If Full House is available and not pursued yet, attempt to pursue Full House by keeping pairs
 *             15. Otherwise, reroll all dice to try to get a better hand
 *             16. Return the pair of vectors of integers representing dice to keep and reroll
 * Reference: Brainstormed with the help of ChatGPT.
 ****************************************************************/
pair<vector<int>, vector<int>> Computer::secondRollMove(const vector<int> rolledDice, vector<int> keptDice)
{
	// Combine keptDice and rolledDice into currentDiceValues
	vector<int> currentDiceValues;

	for (int die : keptDice)
	{
		currentDiceValues.push_back(die);
	}

	for (int die : rolledDice)
	{
		currentDiceValues.push_back(die);
	}

	// diceToRollAgain stores the dice values that the computer decides to reroll in the next round
	vector<int> diceToRollAgain;

	// diceToKeep stores the dice values that the computer decides to keep based on the best category and strategy
	vector<int> diceToKeep;

	// bestCategory stores the name of the best scoring category for the current dice combination
	string bestCategory = ScoreCard::getBestHands(currentDiceValues).first;

	// currentMaximumPoints stores the maximum points the computer can score with the current dice values
	int currentMaximumPoints = ScoreCard::getBestHands(currentDiceValues).second;

	// diceCount stores the count of occurrences of each dice value to help in decision-making
	map<int, int> diceCount;
	for (int die : currentDiceValues)
	{
		// Increment the count for each dice value
		diceCount[die]++;
	}

	// If there is a viable category to score in, display the possible points and best category
	if (bestCategory != "")
	{
		// Display the possible points based on current dice values
		ScoreCard::displayPossiblePoints(currentDiceValues);

		// Inform the best category and possible points after the current roll
		cout << "Computer's best category after this roll is: " << bestCategory << " with " << currentMaximumPoints << " points." << endl;
	}
	else
	{
		// Inform that there are no available categories for the computer to choose from
		cout << "Computer has no available categories to choose from!" << endl;
	}

	// If the best category is Yahtzee, diceToKeep stores all dice and no rerolls are needed
	if (bestCategory == "Yahtzee")
	{
		// Inform that the computer chose to stand with Yahtzee
		cout << "Computer chose to stand with Yahtzee! 50 points for computer!" << endl;

		// Store all current dice values as dice to keep
		diceToKeep = currentDiceValues;

		// Return the kept dice and no rerolls
		return make_pair(diceToKeep, diceToRollAgain);
	}
	// If the best category is Five Straight, diceToKeep stores all dice values
	else if (bestCategory == "Five Straight")
	{
		// Inform that the computer chose to stand with Five Straight
		cout << "Computer chose to stand with Five straight! 40 points for computer!" << endl;

		// Store all current dice values as dice to keep
		diceToKeep = currentDiceValues;

		// Return the kept dice and no rerolls
		return make_pair(diceToKeep, diceToRollAgain);
	}
	// If the best category is Four Straight, determine if the computer can pursue Five Straight
	else if (bestCategory == "Four Straight")
	{
		// temp stores the unique dice values to check for straight combinations
		set<int> temp;

		// If Five Straight is not available, diceToKeep stores all dice and no rerolls are needed
		if (!ScoreCard::isCategoryAvailable("Five Straight"))
		{
			// Inform that the computer will stand as Five Straight is not available
			cout << "\nComputer will stand on this as Five Straight is not available!" << endl;

			// Store all current dice values as dice to keep
			diceToKeep = currentDiceValues;
		}
		else
		{
			// Inform that the computer wants to pursue Five Straight
			cout << "\nComputer wants to pursue Five Straight!" << endl;

			// Add current dice values to temp to check for straight possibilities
			for (int value : currentDiceValues)
			{
				temp.insert(value);
			}

			// If two of the dice are the same, reroll one of the identical dice
			if (temp.size() == 4)
			{
				int nonStraightValue = -1;
				for (int dice : currentDiceValues)
				{
					// Identify the duplicate die value
					if (count(currentDiceValues.begin(), currentDiceValues.end(), dice) == 2)
					{
						nonStraightValue = dice;
					}
				}

				// Check if the duplicate can be rerolled
				if (nonStraightValue != -1 && find(rolledDice.begin(), rolledDice.end(), nonStraightValue) != rolledDice.end())
				{
					// Inform that the computer is rerolling the duplicate die
					cout << "Computer is re-rolling: " << nonStraightValue << endl;

					// Add the duplicate die to reroll
					diceToRollAgain.push_back(nonStraightValue);

					// Keep the other unique dice
					for (int dice : temp)
					{
						diceToKeep.push_back(dice);
					}
				}
				else
				{
					// Inform that the computer cannot reroll the duplicate die and stands with Four Straight
					cout << "\nComputer is standing on Four Straight as it cannot reroll " << nonStraightValue << "!" << endl;

					// Keep all current dice values
					for (int dice : currentDiceValues)
					{
						diceToKeep.push_back(dice);
					}
				}
			}
			else
			{
				// Sort the dice values to check the sequence for potential straights
				vector<int> sortedDice = currentDiceValues;
				sort(sortedDice.begin(), sortedDice.end());

				// If the first two dice values are 1 and 2, reroll the last die
				if (sortedDice[0] == 1 && sortedDice[1] == 2)
				{
					// Add the last die to reroll
					diceToRollAgain.push_back(sortedDice[4]);

					// Keep the first four dice values
					for (int i = 0; i < 4; i++)
					{
						diceToKeep.push_back(sortedDice[i]);
					}
				}
				else
				{
					// Reroll the first die to attempt completing the Five Straight
					diceToRollAgain.push_back(sortedDice[0]);

					// Keep the last four dice values
					for (int i = 1; i < 5; i++)
					{
						diceToKeep.push_back(sortedDice[i]);
					}
				}
			}
		}
		// Return the dice to keep and reroll
		return make_pair(diceToKeep, diceToRollAgain);
	}
	// If the best category is Full House, diceToKeep stores all dice values and no rerolls are needed
	else if (bestCategory == "Full House")
	{
		// Inform that the computer chose to stand with Full House
		cout << "Computer chose to stand with Full House! 25 points for computer!" << endl;

		// Store all current dice values as dice to keep
		diceToKeep = currentDiceValues;

		// Return the kept dice and no rerolls
		return make_pair(diceToKeep, diceToRollAgain);
	}
	// If the best category is Four of a Kind, reroll non-four-kind dice or stand depending on strategy
	else if (bestCategory == "Four of a Kind")
	{
		// nonFourKindValue stores the value of the dice that is not part of the four of a kind
		int nonFourKindValue = -1;

		// fourKindValue stores the value of the dice that appears four times
		int fourKindValue = -1;

		// Identify which dice forms the four of a kind and which one doesn't
		for (const auto& pair : diceCount)
		{
			if (pair.second == 1)
			{
				nonFourKindValue = pair.first;
			}
			else
			{
				fourKindValue = pair.first;
			}
		}

		// If Yahtzee is available, reroll the non-four-kind dice to attempt for Yahtzee
		if (nonFourKindValue != -1)
		{
			if (ScoreCard::isCategoryAvailable("Yahtzee"))
			{
				// Inform that the computer is attempting to go for Yahtzee by rerolling the remaining die
				cout << "\nComputer is attempting to go for Yahtzee by rerolling the remaining die!\n";

				// Add the four-of-a-kind dice to keep and reroll the other die
				for (int die : currentDiceValues)
				{
					if (die == fourKindValue)
					{
						diceToKeep.push_back(die); // Keep the four-of-a-kind dice
					}
					else
					{
						diceToRollAgain.push_back(die); // Add the non-matching die to reroll
					}
				}
			}
			// If Yahtzee is not available and the non-four-kind value is not 6, reroll it
			else if (nonFourKindValue != 6)
			{
				// Inform that the computer chose to reroll the non-four of a kind value to try to get a higher die
				cout << "Computer chose to reroll the non-four of a kind value to try to get a higher die: " << nonFourKindValue << endl;

				// Add the non-four-kind die to reroll
				diceToRollAgain.push_back(nonFourKindValue);

				// Keep the four-of-a-kind dice
				for (int die : currentDiceValues)
				{
					if (die == fourKindValue)
					{
						diceToKeep.push_back(die);
					}
				}
			}
			// If the non-four-kind value is 6, the computer chooses to stand
			else
			{
				// Inform that the computer chose to stand
				cout << "Computer chose to stand on this as the non-four of a kind value is 6 and Yahtzee is not available!" << endl;

				// Keep all current dice values
				diceToKeep = currentDiceValues;
			}
		}
		else
		{
			// If the current dice values are all smaller than 4, reroll one of the non-matching dice
			if (currentDiceValues[0] < 4)
			{
				// Inform that the computer chose to reroll to try to get a higher die to add to the sum
				cout << "\nComputer chose to reroll to try to get a higher die to add to the sum!" << endl;

				// Keep the first four dice values
				for (int i = 0; i < 4; i++)
				{
					diceToKeep.push_back(currentDiceValues[i]);
				}
				// Add the last die to reroll
				diceToRollAgain.push_back(currentDiceValues[4]);
			}
			else
			{
				// Inform that the computer chose to stand with Four of a Kind
				cout << "\nComputer chose to stand with Four of a Kind!" << endl;

				// Keep all current dice values
				for (int die : currentDiceValues)
				{
					diceToKeep.push_back(die);
				}
			}
		}
		// Return the dice to keep and reroll
		return make_pair(diceToKeep, diceToRollAgain);
	}
	// If the best category is Three of a Kind, execute Three of a Kind strategy
	else if (bestCategory == "Three of a Kind")
	{
		// threeKindValue stores the value of the dice that appears at least three times
		int threeKindValue = -1;

		// Find the value that appears three or more times
		for (const auto& pair : diceCount)
		{
			if (pair.second >= 3)
			{
				threeKindValue = pair.first;
			}
		}

		// fullHousePoints stores the points for Full House based on current dice values
		int fullHousePoints = ScoreCard::calculatePoints("Full House", currentDiceValues);

		// If the maximum points exceed Full House points and Full House is 25, stand with Three of a Kind
		if (currentMaximumPoints > fullHousePoints && fullHousePoints == 25)
		{
			// Inform that the computer chose to stand with Three of a Kind
			cout << "Computer chose to stand with Three of a Kind as it is greater" << endl;

			// Keep all current dice values
			diceToKeep = currentDiceValues;

			// Return the kept dice and no rerolls
			return make_pair(diceToKeep, diceToRollAgain);
		}

		// If Yahtzee or Full House is available, attempt to go for Yahtzee or Full House
		if (ScoreCard::isCategoryAvailable("Yahtzee") || ScoreCard::isCategoryAvailable("Full House"))
		{
			// If both Yahtzee and Full House are available, attempt to go for one
			if (ScoreCard::isCategoryAvailable("Yahtzee") && ScoreCard::isCategoryAvailable("Full House"))
			{
				// Inform the computer's decision to pursue either category
				if (diceCount[threeKindValue] == 3)
				{
					cout << "\nComputer is attempting to go for Yahtzee or Full House!\n";
				}
				else
				{
					cout << "\nComputer is attempting to go for Yahtzee!\n";
				}

				// Keep the dice that match the Three of a Kind value and reroll others
				for (int die : currentDiceValues)
				{
					if (die == threeKindValue)
					{
						diceToKeep.push_back(die);
					}
					else
					{
						diceToRollAgain.push_back(die);
					}
				}
			}
			// If only Yahtzee is available, attempt to go for Yahtzee
			else if (ScoreCard::isCategoryAvailable("Yahtzee") && !ScoreCard::isCategoryAvailable("Full House"))
			{
				// Inform that the computer is attempting to go for Yahtzee
				cout << "\nComputer is attempting to go for Yahtzee!\n";

				// Keep the dice that match the Three of a Kind value and reroll others
				for (int die : currentDiceValues)
				{
					if (die == threeKindValue)
					{
						diceToKeep.push_back(die);
					}
					else
					{
						diceToRollAgain.push_back(die);
					}
				}
			}
			// If only Full House is available, pursue Full House
			else
			{
				// Inform that the computer wants to pursue Full House
				cout << "\nComputer wants to pursue Full House!" << endl;

				// max stores the highest dice value
				int max = *max_element(currentDiceValues.begin(), currentDiceValues.end());

				// Keep the three-of-a-kind dice and the highest other die
				if (max == threeKindValue)
				{
					for (int die : currentDiceValues)
					{
						if (die == threeKindValue)
						{
							diceToKeep.push_back(die);
						}
						else
						{
							diceToRollAgain.push_back(die);
						}
					}
				}
				else
				{
					// Keep the three-of-a-kind dice and the highest remaining die
					int count = 0;
					for (int die : currentDiceValues)
					{
						if (die == threeKindValue && count < 3)
						{
							diceToKeep.push_back(die);
							count++;
						}
						else if (die == max)
						{
							diceToKeep.push_back(die);
						}
						else
						{
							diceToRollAgain.push_back(die);
						}
					}
				}
			}
		}
		// If neither Yahtzee nor Full House is available, reroll the remaining dice
		else
		{
			// Keep the dice that match the Three of a Kind value and reroll others
			for (int value : currentDiceValues)
			{
				if (diceCount[value] <= 2)
				{
					if (value < 6)
					{
						diceToRollAgain.push_back(value); // Reroll lower dice values
					}
					else
					{
						diceToKeep.push_back(value); // Keep higher dice values
					}
				}
				else
				{
					diceToKeep.push_back(value); // Keep the three-of-a-kind dice
				}
			}

			// Inform that the computer is rerolling for a better hand
			if (diceToRollAgain.size() > 0)
			{
				cout << "Computer decided to roll again to try and get higher die value!";
			}
			else
			{
				cout << "Computer decided to stand with Three of a Kind!";
			}
		}

		// Return the dice to keep and reroll
		return make_pair(diceToKeep, diceToRollAgain);
	}
	// If the best category is Aces, Twos, Threes, Fours, Fives, or Sixes, execute lower number strategy
	else if (bestCategory == "Aces" || bestCategory == "Twos" || bestCategory == "Threes" || bestCategory == "Fours" || bestCategory == "Fives" || bestCategory == "Sixes")
	{
		// targetValue stores the target dice value that the computer is pursuing
		int targetValue = -1;

		// Assign the target value based on the best category
		if (bestCategory == "Aces")
			targetValue = 1;
		else if (bestCategory == "Twos")
			targetValue = 2;
		else if (bestCategory == "Threes")
			targetValue = 3;
		else if (bestCategory == "Fours")
			targetValue = 4;
		else if (bestCategory == "Fives")
			targetValue = 5;
		else if (bestCategory == "Sixes")
			targetValue = 6;

		// pairs stores dice values that appear in pairs
		vector<int> pairs;

		// nonPairs stores dice values that do not appear in pairs
		vector<int> nonPairs;

		// isStraightPossible stores whether a straight is possible
		bool isStraightPossible = false;

		// Count the number of pairs and non-pairs
		for (const auto& pair : diceCount)
		{
			if (pair.second >= 2)
			{
				pairs.push_back(pair.first);
			}
			else if (pair.second == 1)
			{
				nonPairs.push_back(pair.first);
			}
		}

		// If there is only one pair, check for possible straights
		if (pairs.size() == 1)
		{
			vector<int> sortedDice = currentDiceValues;
			set<int> temp(currentDiceValues.begin(), currentDiceValues.end());

			// Define potential straight sequences
			vector<int> straight = { 1, 2, 3, 4, 5 };
			vector<int> straight2 = { 2, 3, 4, 5, 6 };

			// Check if a straight is possible
			int count = 0;
			for (int die : temp)
			{
				if (find(straight.begin(), straight.end(), die) != straight.end())
				{
					count++;
				}
			}

			// If four dice match a straight, mark straight as possible
			if (count == 4)
			{
				isStraightPossible = true;
			}
			else
			{
				count = 0;
				for (int die : temp)
				{
					if (find(straight2.begin(), straight2.end(), die) != straight2.end())
					{
						count++;
					}
				}
				if (count == 4)
				{
					isStraightPossible = true;
				}
			}
		}

		// If all the dice values are the same, the computer keeps all dice
		if (diceCount.size() == 1)
		{
			cout << "Computer chose to keep all dice as they are all the same value.\n";
			diceToKeep = currentDiceValues;
		}
		// If two pairs exist and Full House is available, pursue Full House
		else if (pairs.size() == 2 && ScoreCard::isCategoryAvailable("Full House"))
		{
			// Inform that the computer is pursuing Full House
			cout << "Computer is pursuing Full House!" << endl;

			// Keep the pairs and reroll the rest
			for (int die : currentDiceValues)
			{
				if (die == pairs[0] || die == pairs[1])
				{
					diceToKeep.push_back(die);
				}
				else
				{
					diceToRollAgain.push_back(die);
				}
			}
		}
		// If one pair exists, consider pursuing straights or other categories
		else if (pairs.size() == 1)
		{
			// If Five Straight is possible, pursue it
			if (ScoreCard::isCategoryAvailable("Five Straight") && isStraightPossible)
			{
				// Inform that the computer is pursuing Five Straight
				cout << "Computer is pursuing Five Straight!" << endl;

				int count = 0;
				for (int die : currentDiceValues)
				{
					if (die == pairs[0] && count < 1)
					{
						// Reroll one instance of the paired die
						diceToRollAgain.push_back(die);
						count++;
					}
					else
					{
						// Keep the other dice
						diceToKeep.push_back(die);
					}
				}
			}
			// If Yahtzee, Four of a Kind, Three of a Kind, or Full House is available, pursue them
			else if (ScoreCard::isCategoryAvailable("Yahtzee") || ScoreCard::isCategoryAvailable("Four of a Kind") || ScoreCard::isCategoryAvailable("Three of a Kind") || ScoreCard::isCategoryAvailable("Full House"))
			{
				// Inform which categories the computer is pursuing
				cout << "Computer is pursuing ";

				if (ScoreCard::isCategoryAvailable("Yahtzee"))
				{
					cout << "Yahtzee | ";
				}
				if (ScoreCard::isCategoryAvailable("Four of a Kind"))
				{
					cout << "Four of a Kind | ";
				}
				if (ScoreCard::isCategoryAvailable("Three of a Kind"))
				{
					cout << "Three of a Kind | ";
				}
				if (ScoreCard::isCategoryAvailable("Full House"))
				{
					cout << "Full House | ";
				}

				cout << endl;

				// Keep the paired dice and reroll the rest
				for (int die : currentDiceValues)
				{
					if (die == pairs[0])
					{
						diceToKeep.push_back(die);
					}
					else
					{
						diceToRollAgain.push_back(die);
					}
				}
			}
			// If no other categories are available, reroll non-target dice
			else
			{
				// Inform that the computer is rerolling non-target values to try to get a better hand
				cout << "Computer is rolling the non-target value to try to get a better hand!" << endl;

				// Keep the target value dice and reroll the rest
				for (int die : currentDiceValues)
				{
					if (die == targetValue)
					{
						diceToKeep.push_back(die);
					}
					else
					{
						diceToRollAgain.push_back(die);
					}
				}
			}
		}
		// If no pairs exist, reroll all dice to pursue better hands or straights
		else
		{
			// Check if there are no pairs in the dice count
			bool hasNoPairs = true;
			for (const auto& pair : diceCount)
			{
				if (pair.second >= 2)
				{
					hasNoPairs = false;
					break;
				}
			}

			if (hasNoPairs)
			{
				// If a straight is available, attempt to pursue it by rerolling specific dice
				if (ScoreCard::isCategoryAvailable("Four Straight") || ScoreCard::isCategoryAvailable("Five Straight"))
				{
					// Check if the computer can pursue a straight by rerolling Aces
					if (find(rolledDice.begin(), rolledDice.end(), 1) != rolledDice.end())
					{
						// Inform that the computer is attempting to pursue a Straight
						cout << "No pairs found, attempting to pursue a Straight!" << endl;

						// Keep all dice except Aces, which are rerolled to try to complete a straight
						for (int value : currentDiceValues)
						{
							if (value == 1)
							{
								diceToRollAgain.push_back(value);
							}
							else
							{
								diceToKeep.push_back(value);
							}
						}

						// Inform that the computer is rerolling Aces to pursue a straight
						if (diceToRollAgain.size() > 0)
						{
							cout << "Computer is rerolling Aces to pursue a straight.\n";
						}
					}
					else
					{
						// Inform that the computer is rerolling currently rolled dice to try to get a higher die
						cout << "Computer is rerolling currently rolled dice to try to get a higher die!" << endl;

						// Reroll all dice that were rolled again and keep the rest
						for (int value : currentDiceValues)
						{
							if (find(rolledDice.begin(), rolledDice.end(), value) != rolledDice.end())
							{
								diceToRollAgain.push_back(value);
							}
							else
							{
								diceToKeep.push_back(value);
							}
						}
					}
				}
				else
				{
					// Inform that the computer is rerolling all dice to try to get a better hand
					cout << "No pairs found, rerolling all dice to try to get a better hand!" << endl;

					// Reroll all dice
					diceToRollAgain = currentDiceValues;
				}
			}
			else
			{
				// If pairs are present, reroll non-target dice
				for (int value : currentDiceValues)
				{
					if (value == targetValue)
					{
						diceToKeep.push_back(value);
					}
					else
					{
						if (find(rolledDice.begin(), rolledDice.end(), value) != rolledDice.end())
							diceToRollAgain.push_back(value);
						else
							diceToKeep.push_back(value);
					}
				}
				// Inform that the computer is rerolling to try to get more target values
				if (diceToRollAgain.size() != 0)
					cout << "Computer is rerolling to try to get more " << targetValue << "'s.\n";
				else
					cout << "Computer is standing on " << targetValue << " as it cannot reroll the remaining dice!" << endl;
			}
		}

		// Return the dice to keep and reroll
		return make_pair(diceToKeep, diceToRollAgain);
	}
	// If no specific category is identified, reroll all dice
	else
	{
		// hasPairs indicates whether there are any pairs in the current dice values
		bool hasPairs = false;

		// Check if there are any pairs in the current dice values
		for (int value : currentDiceValues)
		{
			if (diceCount[value] >= 2)
			{
				hasPairs = true;
				break;
			}
		}

		// If Yahtzee is available, consider pursuing Yahtzee
		if (ScoreCard::isCategoryAvailable("Yahtzee"))
		{
			if (hasPairs)
			{
				// Inform that the computer is pursuing Yahtzee
				cout << "Computer is pursuing Yahtzee!" << endl;

				// Initialize count and flag for more than two same dice
				int count = 0;
				bool moreThanTwoSame = false;

				// Check if any die appears more than two times
				for (int die : currentDiceValues)
				{
					if (diceCount[die] > 2)
					{
						moreThanTwoSame = true;
						break;
					}
				}

				if (moreThanTwoSame)
				{
					// Keep the dice that appear more than two times and reroll the rest
					for (int die : currentDiceValues)
					{
						if (diceCount[die] > 2)
						{
							diceToKeep.push_back(die);
						}
						else
						{
							diceToRollAgain.push_back(die);
						}
					}
				}
				else
				{
					// Sort the dice to prioritize keeping pairs for Yahtzee
					vector<int> sortedDice = currentDiceValues;
					sort(sortedDice.begin(), sortedDice.end());

					for (int die : sortedDice)
					{
						if (diceCount[die] >= 2 && count < 2)
						{
							// Keep the paired dice
							diceToKeep.push_back(die);
							count++;
						}
						else
						{
							// Reroll the rest
							diceToRollAgain.push_back(die);
						}
					}
				}
			}
			else
			{
				// Inform that the computer is rerolling all dice to try to get Yahtzee
				cout << "Computer is rolling all the die again to try to get Yahtzee!" << endl;

				// Reroll all dice
				diceToRollAgain = currentDiceValues;
			}
		}
		// If Full House is available, consider pursuing Full House
		else if (ScoreCard::isCategoryAvailable("Full House"))
		{
			if (hasPairs)
			{
				// Inform that the computer is pursuing Full House
				cout << "Computer is pursuing Full House!" << endl;

				// Keep the paired dice and reroll the rest
				for (int die : currentDiceValues)
				{
					if (diceCount[die] >= 2)
					{
						diceToKeep.push_back(die);
					}
					else
					{
						diceToRollAgain.push_back(die);
					}
				}
			}
			else
			{
				// Inform that the computer is rerolling all dice to try to get Full House
				cout << "Computer is rolling all the die again to try to get Full House!" << endl;

				// Reroll all dice
				diceToRollAgain = currentDiceValues;
			}
		}
		// If neither Yahtzee nor Full House is available, reroll all dice to pursue a better hand
		else
		{
			// Inform that the computer is rerolling all dice to try to get a better hand
			cout << "Computer is rolling all the die again to try to get a better hand!" << endl;

			// Reroll all dice
			diceToRollAgain = currentDiceValues;
		}

		// Return the dice to keep and reroll
		return make_pair(diceToKeep, diceToRollAgain);
	}
}

/****************************************************************
 * Function Name: Human::firstRollHelp
 * Purpose: To provide guidance to the human player on which dice to keep
 *          and which to reroll based on the current dice values.
 * Parameters:
 *         currentDiceValues, a vector of integers passed by value.
 *             It stores the current dice values rolled by the player.
 * Return Value: None
 * Algorithm:
 *             1. Initialize vectors to store dice to keep and dice to reroll.
 *             2. Determine the best scoring category and its points using ScoreCard::getBestHands.
 *             3. Count the occurrences of each dice value to assist in decision-making.
 *             4. If a viable category exists:
 *                 4.1. Display possible points for each category.
 *                 4.2. Inform the player of the best category and its points.
 *             5. Based on the best category, provide specific guidance:
 *                 5.1. If Yahtzee:
 *                     5.1.1. Advise the player to keep all dice and score Yahtzee.
 *                 5.2. If Five Straight:
 *                     5.2.1. Advise the player to keep all dice and score Five Straight.
 *                 5.3. If Four Straight:
 *                     5.3.1. Check if Five Straight is available.
 *                         5.3.1.1. If not available, advise the player to keep all dice.
 *                         5.3.1.2. If available, suggest pursuing Five Straight by rerolling duplicates or specific dice.
 *                 5.4. If Full House:
 *                     5.4.1. Advise the player to keep all dice and score Full House.
 *                 5.5. If Four of a Kind:
 *                     5.5.1. Identify the non-four-kind die.
 *                     5.5.2. If Yahtzee is available:
 *                         5.5.2.1. Suggest rerolling the non-four-kind die to attempt Yahtzee.
 *                     5.5.3. If Yahtzee is not available and the non-four-kind die is not 6:
 *                         5.5.3.1. Suggest rerolling it to try for a higher die value.
 *                     5.5.4. If the non-four-kind die is 6, advise the player to keep all dice.
 *                 5.6. If Three of a Kind:
 *                     5.6.1. Identify the three-kind die.
 *                     5.6.2. Calculate Full House points.
 *                     5.6.3. If current points exceed Full House points:
 *                         5.6.3.1. Advise the player to keep all dice and score Three of a Kind.
 *                     5.6.4. If Yahtzee or Full House is available:
 *                         5.6.4.1. Suggest pursuing Yahtzee or Full House by keeping the three-kind dice and rerolling others.
 *                     5.6.5. If neither is available, suggest rerolling non-three-kind dice to improve the hand.
 *                 5.7. If one of the upper sections (Aces, Twos, Threes, Fours, Fives, Sixes):
 *                     5.7.1. Identify the target die value based on the category.
 *                     5.7.2. Identify pairs and non-pairs in the dice count.
 *                     5.7.3. If there are two pairs and Full House is available:
 *                         5.7.3.1. Suggest keeping the pairs and rerolling the remaining die.
 *                     5.7.4. If there is one pair:
 *                         5.7.4.1. If Five Straight is available and possible, suggest pursuing it by rerolling one instance of the paired die.
 *                         5.7.4.2. If Yahtzee, Four of a Kind, Three of a Kind, or Full House is available, suggest pursuing them by keeping the pair and rerolling others.
 *                         5.7.4.3. Otherwise, suggest rerolling non-target dice to try to improve the hand.
 *                     5.7.5. If no pairs exist:
 *                         5.7.5.1. If a Straight is available, suggest rerolling specific dice to pursue it.
 *                         5.7.5.2. Otherwise, suggest rerolling all dice to try to get a better hand.
 *             6. If no specific category is identified:
 *                 6.1. Check for any pairs in the dice.
 *                 6.2. If Yahtzee is available:
 *                     6.2.1. If there are pairs, suggest pursuing Yahtzee by keeping multiple instances of the paired die.
 *                     6.2.2. If no pairs, suggest rerolling all dice to attempt Yahtzee.
 *                 6.3. If Full House is available:
 *                     6.3.1. If there are pairs, suggest keeping them and rerolling the rest to pursue Full House.
 *                     6.3.2. If no pairs, suggest rerolling all dice to attempt Full House.
 *                 6.4. If neither Yahtzee nor Full House is available, suggest rerolling all dice to pursue a better hand.
 *             7. Display the dice the player should keep and reroll.
 * Reference: Brainstormed with the help of ChatGPT.
 ****************************************************************/
void Human::firstRollHelp(const vector<int> currentDiceValues)
{
	vector<int> diceToKeep;
	vector<int> diceToRollAgain;

	string bestCategory = ScoreCard::getBestHands(currentDiceValues).first;
	int currentMaximumPoints = ScoreCard::getBestHands(currentDiceValues).second;

	map<int, int> diceCount;
	for (int value : currentDiceValues)
	{
		diceCount[value]++;
	}

	if (!bestCategory.empty())
	{
		ScoreCard::displayPossiblePoints(currentDiceValues);
		cout << "Your best category after this roll is: " << bestCategory << " with " << currentMaximumPoints << " points." << endl;
	}
	else
	{
		cout << "You have no available categories to choose from!" << endl;
	}

	if (bestCategory == "Yahtzee")
	{
		cout << "You have a Yahtzee! You should stand with Yahtzee and score 50 points!" << endl;
		diceToKeep = currentDiceValues;
	}
	else if (bestCategory == "Five Straight")
	{
		cout << "You have a Five Straight! You should stand with Five Straight and score 40 points!" << endl;
		diceToKeep = currentDiceValues;
	}
	else if (bestCategory == "Four Straight")
	{
		set<int> uniqueDice(currentDiceValues.begin(), currentDiceValues.end());

		if (!ScoreCard::isCategoryAvailable("Five Straight"))
		{
			cout << "\nYou should stand with Four Straight as Five Straight is not available!" << endl;
			diceToKeep = currentDiceValues;
		}
		else
		{
			cout << "\nYou might want to pursue Five Straight!" << endl;

			if (uniqueDice.size() == 4)
			{
				for (int die : uniqueDice)
				{
					if (count(currentDiceValues.begin(), currentDiceValues.end(), die) == 2)
					{
						diceToRollAgain.push_back(die);
					}
					diceToKeep.push_back(die);
				}
			}
			else
			{
				vector<int> sortedDice = currentDiceValues;
				sort(sortedDice.begin(), sortedDice.end());

				if (sortedDice[0] == 1 && sortedDice[1] == 2)
				{
					diceToRollAgain.push_back(sortedDice[4]);
					for (int i = 0; i < 4; i++)
					{
						diceToKeep.push_back(sortedDice[i]);
					}
				}
				else
				{
					diceToRollAgain.push_back(sortedDice[0]);
					for (int i = 1; i < 5; i++)
					{
						diceToKeep.push_back(sortedDice[i]);
					}
				}
			}
		}
	}
	else if (bestCategory == "Full House")
	{
		cout << "You have a Full House! You should stand with Full House and score 25 points!" << endl;
		diceToKeep = currentDiceValues;
	}
	else if (bestCategory == "Four of a Kind")
	{
		int nonFourKindValue = -1;
		int fourKindValue = -1;
		for (const auto& pair : diceCount)
		{
			if (pair.second == 1)
			{
				nonFourKindValue = pair.first;
			}
			else
			{
				fourKindValue = pair.first;
			}
		}

		if (nonFourKindValue != -1)
		{
			if (ScoreCard::isCategoryAvailable("Yahtzee"))
			{
				cout << "\nYou might attempt to go for Yahtzee by rerolling the remaining die!" << endl;
				for (int die : currentDiceValues)
				{
					if (die == fourKindValue)
					{
						diceToKeep.push_back(die);
					}
					else
					{
						diceToRollAgain.push_back(die);
					}
				}
			}
			else
			{
				if (nonFourKindValue != 6)
				{
					cout << "You might reroll the non-four of a kind value to try to get a higher die: " << nonFourKindValue << endl;
					diceToRollAgain.push_back(nonFourKindValue);
					for (int die : currentDiceValues)
					{
						if (die == fourKindValue)
						{
							diceToKeep.push_back(die);
						}
					}
				}
				else
				{
					cout << "You should stand as the non-four of a kind value is 6 and Yahtzee is not available!" << endl;
					diceToKeep = currentDiceValues;
				}
			}
		}
		else
		{
			if (currentDiceValues[0] < 4)
			{
				cout << "\nYou might reroll to try to get a higher die to add to the sum!" << endl;
				for (int i = 0; i < 4; i++)
				{
					diceToKeep.push_back(currentDiceValues[i]);
				}
				diceToRollAgain.push_back(currentDiceValues[4]);
			}
			else
			{
				cout << "\nYou should stand with Four of a Kind!" << endl;
				diceToKeep = currentDiceValues;
			}
		}
	}
	else if (bestCategory == "Three of a Kind")
	{
		int threeKindValue = -1;
		for (const auto& pair : diceCount)
		{
			if (pair.second >= 3)
			{
				threeKindValue = pair.first;
			}
		}

		int fullHousePoints = ScoreCard::calculatePoints("Full House", currentDiceValues);

		if (currentMaximumPoints > fullHousePoints && fullHousePoints == 25)
		{
			cout << "You might stand with Three of a Kind as it scores higher than a Full House." << endl;
			diceToKeep = currentDiceValues;
		}
		else if (ScoreCard::isCategoryAvailable("Yahtzee") || ScoreCard::isCategoryAvailable("Full House"))
		{
			if (ScoreCard::isCategoryAvailable("Yahtzee") && ScoreCard::isCategoryAvailable("Full House"))
			{
				if (diceCount[threeKindValue] == 3)
				{
					cout << "\nYou might attempt to go for Yahtzee or Full House!" << endl;
				}
				else
				{
					cout << "\nYou might attempt to go for Yahtzee!" << endl;
				}

				for (int die : currentDiceValues)
				{
					if (die == threeKindValue)
					{
						diceToKeep.push_back(die);
					}
					else
					{
						diceToRollAgain.push_back(die);
					}
				}
			}
			else if (ScoreCard::isCategoryAvailable("Yahtzee"))
			{
				cout << "\nYou might attempt to go for Yahtzee!" << endl;
				for (int die : currentDiceValues)
				{
					if (die == threeKindValue)
					{
						diceToKeep.push_back(die);
					}
					else
					{
						diceToRollAgain.push_back(die);
					}
				}
			}
			else
			{
				cout << "\nYou might want to pursue a Full House!" << endl;
				int maxDie = *max_element(currentDiceValues.begin(), currentDiceValues.end());

				if (maxDie == threeKindValue)
				{
					for (int die : currentDiceValues)
					{
						if (die == threeKindValue)
						{
							diceToKeep.push_back(die);
						}
						else
						{
							diceToRollAgain.push_back(die);
						}
					}
				}
				else
				{
					int count = 0;
					for (int die : currentDiceValues)
					{
						if (die == threeKindValue && count < 3)
						{
							diceToKeep.push_back(die);
							count++;
						}
						else if (die == maxDie)
						{
							diceToKeep.push_back(die);
						}
						else
						{
							diceToRollAgain.push_back(die);
						}
					}
				}
			}
		}
		else
		{
			for (int die : currentDiceValues)
			{
				if (diceCount[die] <= 2)
				{
					if (die < 6)
					{
						diceToRollAgain.push_back(die);
					}
					else
					{
						diceToKeep.push_back(die);
					}
				}
				else
				{
					diceToKeep.push_back(die);
				}
			}
			if (!diceToRollAgain.empty())
			{
				cout << "You might decide to roll again to try and get higher die values!" << endl;
			}
			else
			{
				cout << "You might decide to stand with Three of a Kind!" << endl;
			}
		}
	}
	else if (bestCategory == "Aces" || bestCategory == "Twos" || bestCategory == "Threes" || bestCategory == "Fours" || bestCategory == "Fives" || bestCategory == "Sixes")
	{
		int targetValue = -1;

		if (bestCategory == "Aces")
			targetValue = 1;
		else if (bestCategory == "Twos")
			targetValue = 2;
		else if (bestCategory == "Threes")
			targetValue = 3;
		else if (bestCategory == "Fours")
			targetValue = 4;
		else if (bestCategory == "Fives")
			targetValue = 5;
		else if (bestCategory == "Sixes")
			targetValue = 6;

		vector<int> pairs;
		vector<int> nonPairs;
		bool isStraightPossible = false;

		for (const auto& pair : diceCount)
		{
			if (pair.second >= 2)
			{
				pairs.push_back(pair.first);
			}
			else if (pair.second == 1)
			{
				nonPairs.push_back(pair.first);
			}
		}

		if (pairs.size() == 1)
		{
			vector<int> sortedDice = currentDiceValues;
			set<int> temp(currentDiceValues.begin(), currentDiceValues.end());

			vector<int> straight = { 1, 2, 3, 4, 5 };
			vector<int> straight2 = { 2, 3, 4, 5, 6 };

			int count = 0;
			for (int die : temp)
			{
				if (find(straight.begin(), straight.end(), die) != straight.end())
				{
					count++;
				}
			}

			if (count == 4)
			{
				isStraightPossible = true;
			}
			else
			{
				count = 0;

				for (int die : temp)
				{
					if (find(straight2.begin(), straight2.end(), die) != straight2.end())
					{
						count++;
					}
				}

				if (count == 4)
				{
					isStraightPossible = true;
				}
			}
		}

		if (diceCount.size() == 1)
		{
			cout << "You have all dice with the same value. You should keep all dice." << endl;
			diceToKeep = currentDiceValues;
		}
		else if (pairs.size() == 2 && ScoreCard::isCategoryAvailable("Full House"))
		{
			cout << "You might pursue a Full House!" << endl;
			for (int die : currentDiceValues)
			{
				if (die == pairs[0] || die == pairs[1])
				{
					diceToKeep.push_back(die);
				}
				else
				{
					diceToRollAgain.push_back(die);
				}
			}
		}
		else if (pairs.size() == 1)
		{
			if (ScoreCard::isCategoryAvailable("Five Straight") && isStraightPossible)
			{
				cout << "You might pursue a Five Straight!" << endl;
				int count = 0;
				for (int die : currentDiceValues)
				{
					if (die == pairs[0] && count < 1)
					{
						diceToRollAgain.push_back(die);
						count++;
					}
					else
					{
						diceToKeep.push_back(die);
					}
				}
			}
			else if (ScoreCard::isCategoryAvailable("Yahtzee") || ScoreCard::isCategoryAvailable("Four of a Kind") || ScoreCard::isCategoryAvailable("Three of a Kind") || ScoreCard::isCategoryAvailable("Full House"))
			{
				cout << "You might pursue ";

				if (ScoreCard::isCategoryAvailable("Yahtzee"))
				{
					cout << "Yahtzee | ";
				}
				if (ScoreCard::isCategoryAvailable("Four of a Kind"))
				{
					cout << "Four of a Kind | ";
				}
				if (ScoreCard::isCategoryAvailable("Three of a Kind"))
				{
					cout << "Three of a Kind | ";
				}
				if (ScoreCard::isCategoryAvailable("Full House"))
				{
					cout << "Full House | ";
				}
				cout << endl;

				for (int die : currentDiceValues)
				{
					if (die == pairs[0])
					{
						diceToKeep.push_back(die);
					}
					else
					{
						diceToRollAgain.push_back(die);
					}
				}
			}
			else
			{
				cout << "You might reroll the non-target value to try to get a better hand!" << endl;
				for (int die : currentDiceValues)
				{
					if (die == targetValue)
					{
						diceToKeep.push_back(die);
					}
					else
					{
						diceToRollAgain.push_back(die);
					}
				}
			}
		}
		else
		{
			bool hasNoPairs = true;
			for (const auto& pair : diceCount)
			{
				if (pair.second >= 2)
				{
					hasNoPairs = false;
					break;
				}
			}

			if (hasNoPairs)
			{
				if (ScoreCard::isCategoryAvailable("Four Straight") || ScoreCard::isCategoryAvailable("Five Straight"))
				{
					cout << "No pairs found. You might attempt to pursue a Straight!" << endl;

					for (int value : currentDiceValues)
					{
						if (value == 1)
						{
							diceToRollAgain.push_back(value);
						}
						else
						{
							diceToKeep.push_back(value);
						}
					}

					if (!diceToRollAgain.empty())
					{
						cout << "You might reroll Aces to pursue a straight." << endl;
					}
				}
				else
				{
					cout << "No pairs found. You might reroll all dice to try to get a better hand!" << endl;
					diceToRollAgain = currentDiceValues;
				}
			}
			else
			{
				for (int value : currentDiceValues)
				{
					if (value == targetValue)
					{
						diceToKeep.push_back(value);
					}
					else
					{
						diceToRollAgain.push_back(value);
					}
				}
				cout << "You might reroll to try to get more " << targetValue << "'s." << endl;
			}
		}
	}
	else
	{
		bool hasPairs = false;

		for (int value : currentDiceValues)
		{
			if (diceCount[value] >= 2)
			{
				hasPairs = true;
				break;
			}
		}

		if (ScoreCard::isCategoryAvailable("Yahtzee"))
		{

			if (hasPairs)
			{
				cout << "You might pursue a Yahtzee!" << endl;
				int count = 0;
				bool moreThanTwoSame = false;

				for (int die : currentDiceValues)
				{
					if (diceCount[die] > 2)
					{
						moreThanTwoSame = true;
						break;
					}
				}

				if (moreThanTwoSame)
				{
					for (int die : currentDiceValues)
					{
						if (diceCount[die] > 2)
						{
							diceToKeep.push_back(die);
						}
						else
						{
							diceToRollAgain.push_back(die);
						}
					}
				}
				else
				{
					vector<int> sortedDice = currentDiceValues;
					sort(sortedDice.begin(), sortedDice.end());

					for (int die : sortedDice)
					{
						if (diceCount[die] >= 2 && count < 2)
						{
							diceToKeep.push_back(die);
							count++;
						}
						else
						{
							diceToRollAgain.push_back(die);
						}
					}
				}
			}
			else
			{
				cout << "You might reroll all the dice to try to get Yahtzee!" << endl;
				diceToRollAgain = currentDiceValues;
			}
		}
		else if (ScoreCard::isCategoryAvailable("Full House"))
		{

			if (hasPairs)
			{
				cout << "You might pursue a Full House!" << endl;
				for (int die : currentDiceValues)
				{
					if (diceCount[die] >= 2)
					{
						diceToKeep.push_back(die);
					}
					else
					{
						diceToRollAgain.push_back(die);
					}
				}
			}
			else
			{
				cout << "You might reroll all the dice to try to get a Full House!" << endl;
				diceToRollAgain = currentDiceValues;
			}
		}
		else
		{
			cout << "You might reroll all the dice to try to get a better hand!" << endl;
			diceToRollAgain = currentDiceValues;
		}
	}

	cout << "\nYou should keep these dice: ";
	if (diceToKeep.empty())
		cout << "None";
	else
	{
		for (int die : diceToKeep)
		{
			cout << die << " ";
		}
	}
	cout << endl;

	cout << "\nYou should reroll these dice: ";
	if (diceToRollAgain.empty())
		cout << "None";
	else
	{
		for (int die : diceToRollAgain)
		{
			cout << die << " ";
		}
	}
	cout << endl;
}

/****************************************************************
 * Function Name: Human::secondRollHelp
 * Purpose: To provide guidance to the human player on which dice to keep
 *          and which to reroll after the second roll based on the current
 *          and previously kept dice values.
 * Parameters:
 *         rolledDice, a vector of integers passed by value.
 *             It stores the dice values that were rolled in the second roll.
 *         keptDice, a vector of integers passed by value.
 *             It stores the dice values the player chose to keep from the first roll.
 * Return Value: None
 * Algorithm:
 *             1. Combine keptDice and rolledDice into currentDiceValues.
 *             2. Initialize vectors to store dice to keep and dice to reroll.
 *             3. Determine the best scoring category and its points using ScoreCard::getBestHands.
 *             4. Count the occurrences of each dice value to assist in decision-making.
 *             5. If a viable category exists:
 *                 5.1. Display possible points for each category.
 *                 5.2. Inform the player of the best category and its points.
 *             6. Based on the best category, provide specific guidance:
 *                 6.1. If Yahtzee:
 *                     6.1.1. Advise the player to keep all dice and score Yahtzee.
 *                 6.2. If Five Straight:
 *                     6.2.1. Advise the player to keep all dice and score Five Straight.
 *                 6.3. If Four Straight:
 *                     6.3.1. Check if Five Straight is available.
 *                         6.3.1.1. If not available, advise the player to keep all dice.
 *                         6.3.1.2. If available, suggest pursuing Five Straight by rerolling duplicates or specific dice.
 *                 6.4. If Full House:
 *                     6.4.1. Advise the player to keep all dice and score Full House.
 *                 6.5. If Four of a Kind:
 *                     6.5.1. Identify the non-four-kind die.
 *                     6.5.2. If Yahtzee is available:
 *                         6.5.2.1. Suggest rerolling the non-four-kind die to attempt Yahtzee.
 *                     6.5.3. If Yahtzee is not available and the non-four-kind die is not 6:
 *                         6.5.3.1. Suggest rerolling it to try for a higher die value.
 *                     6.5.4. If the non-four-kind die is 6, advise the player to keep all dice.
 *                 6.6. If Three of a Kind:
 *                     6.6.1. Identify the three-kind die.
 *                     6.6.2. Calculate Full House points.
 *                     6.6.3. If current points exceed Full House points:
 *                         6.6.3.1. Advise the player to keep all dice and score Three of a Kind.
 *                     6.6.4. If Yahtzee or Full House is available:
 *                         6.6.4.1. Suggest pursuing Yahtzee or Full House by keeping the three-kind dice and rerolling others.
 *                     6.6.5. If neither is available, suggest rerolling non-three-kind dice to improve the hand.
 *                 6.7. If one of the upper sections (Aces, Twos, Threes, Fours, Fives, Sixes):
 *                     6.7.1. Identify the target die value based on the category.
 *                     6.7.2. Identify pairs and non-pairs in the dice count.
 *                     6.7.3. If there are two pairs and Full House is available:
 *                         6.7.3.1. Suggest keeping the pairs and rerolling the remaining die.
 *                     6.7.4. If there is one pair:
 *                         6.7.4.1. If Five Straight is available and possible, suggest pursuing it by rerolling one instance of the paired die.
 *                         6.7.4.2. If Yahtzee, Four of a Kind, Three of a Kind, or Full House is available, suggest pursuing them by keeping the pair and rerolling others.
 *                         6.7.4.3. Otherwise, suggest rerolling non-target dice to try to improve the hand.
 *                     6.7.5. If no pairs exist:
 *                         6.7.5.1. If a Straight is available, suggest rerolling specific dice to pursue it.
 *                         6.7.5.2. Otherwise, suggest rerolling all dice to try to get a better hand.
 *             7. If no specific category is identified:
 *                 7.1. Check for any pairs in the dice.
 *                 7.2. If Yahtzee is available:
 *                     7.2.1. If there are pairs, suggest pursuing Yahtzee by keeping multiple instances of the paired die.
 *                     7.2.2. If no pairs, suggest rerolling all dice to attempt Yahtzee.
 *                 7.3. If Full House is available:
 *                     7.3.1. If there are pairs, suggest keeping them and rerolling the rest to pursue Full House.
 *                     7.3.2. If no pairs, suggest rerolling all dice to attempt Full House.
 *                 7.4. If neither Yahtzee nor Full House is available, suggest rerolling all dice to pursue a better hand.
 *             8. Display the dice the player should keep and reroll.
 * Reference: Brainstormed with the help of ChatGPT.
 ****************************************************************/
void Human::secondRollHelp(const vector<int> rolledDice, const vector<int> keptDice)
{
	vector<int> currentDiceValues = keptDice;
	currentDiceValues.insert(currentDiceValues.end(), rolledDice.begin(), rolledDice.end());

	vector<int> diceToKeep;
	vector<int> diceToRollAgain;

	string bestCategory = ScoreCard::getBestHands(currentDiceValues).first;
	int currentMaximumPoints = ScoreCard::getBestHands(currentDiceValues).second;

	map<int, int> diceCount;
	for (int die : currentDiceValues)
	{
		diceCount[die]++;
	}

	if (!bestCategory.empty())
	{
		ScoreCard::displayPossiblePoints(currentDiceValues);
		cout << "Your best category after this roll is: " << bestCategory << " with " << currentMaximumPoints << " points." << endl;
	}
	else
	{
		cout << "You have no available categories to choose from!" << endl;
	}

	if (bestCategory == "Yahtzee")
	{
		cout << "You have a Yahtzee! You should stand with Yahtzee and score 50 points!" << endl;
		diceToKeep = currentDiceValues;
	}
	else if (bestCategory == "Five Straight")
	{
		cout << "You have a Five Straight! You should stand with Five Straight and score 40 points!" << endl;
		diceToKeep = currentDiceValues;
	}
	else if (bestCategory == "Four Straight")
	{
		set<int> uniqueDice(currentDiceValues.begin(), currentDiceValues.end());

		if (!ScoreCard::isCategoryAvailable("Five Straight"))
		{
			cout << "\nYou should stand with Four Straight as Five Straight is not available!" << endl;
			diceToKeep = currentDiceValues;
		}
		else
		{
			cout << "\nYou might want to pursue Five Straight!" << endl;

			if (uniqueDice.size() == 4)
			{
				int nonStraightValue = -1;
				for (int die : currentDiceValues)
				{
					if (count(currentDiceValues.begin(), currentDiceValues.end(), die) == 2)
					{
						nonStraightValue = die;
						break;
					}
				}

				if (nonStraightValue != -1 && find(rolledDice.begin(), rolledDice.end(), nonStraightValue) != rolledDice.end())
				{
					cout << "You might reroll: " << nonStraightValue << " to pursue Five Straight." << endl;
					diceToRollAgain.push_back(nonStraightValue);
					for (int die : uniqueDice)
					{
						diceToKeep.push_back(die);
					}
				}
				else
				{
					cout << "\nYou should stand with Four Straight as you cannot reroll " << nonStraightValue << "!" << endl;
					diceToKeep = currentDiceValues;
				}
			}
			else
			{
				vector<int> sortedDice = currentDiceValues;
				sort(sortedDice.begin(), sortedDice.end());

				if (sortedDice[0] == 1 && sortedDice[1] == 2)
				{
					if (find(rolledDice.begin(), rolledDice.end(), sortedDice[4]) != rolledDice.end())
					{
						cout << "You might reroll: " << sortedDice[4] << " to pursue Five Straight." << endl;
						diceToRollAgain.push_back(sortedDice[4]);
						for (int i = 0; i < 4; i++)
						{
							diceToKeep.push_back(sortedDice[i]);
						}
					}
					else
					{
						cout << "\nYou should stand with Four Straight as you cannot reroll " << sortedDice[4] << "!" << endl;
						diceToKeep = currentDiceValues;
					}
				}
				else
				{
					if (find(rolledDice.begin(), rolledDice.end(), sortedDice[0]) != rolledDice.end())
					{
						cout << "You might reroll: " << sortedDice[0] << " to pursue Five Straight." << endl;
						diceToRollAgain.push_back(sortedDice[0]);
						for (int i = 1; i < 5; i++)
						{
							diceToKeep.push_back(sortedDice[i]);
						}
					}
					else
					{
						cout << "\nYou should stand with Four Straight as you cannot reroll " << sortedDice[0] << "!" << endl;
						diceToKeep = currentDiceValues;
					}
				}
			}
		}
	}
	else if (bestCategory == "Full House")
	{
		cout << "You have a Full House! You should stand with Full House and score 25 points!" << endl;
		diceToKeep = currentDiceValues;
	}
	else if (bestCategory == "Four of a Kind")
	{
		int nonFourKindValue = -1;
		for (const auto &pair : diceCount)
		{
			if (pair.second == 1)
			{
				nonFourKindValue = pair.first;
				break;
			}
		}

		if (nonFourKindValue != -1)
		{
			if (ScoreCard::isCategoryAvailable("Yahtzee"))
			{
				if (find(rolledDice.begin(), rolledDice.end(), nonFourKindValue) != rolledDice.end())
				{
					cout << "You might reroll: " << nonFourKindValue << " to pursue Yahtzee!" << endl;
					diceToRollAgain.push_back(nonFourKindValue);
					for (int die : currentDiceValues)
					{
						if (die != nonFourKindValue)
						{
							diceToKeep.push_back(die);
						}
					}
				}
				else
				{
					cout << "\nYou should stand with Four of a Kind as you cannot reroll " << nonFourKindValue << "!" << endl;
					diceToKeep = currentDiceValues;
				}
			}
			else
			{
				if (nonFourKindValue != 6)
				{
					if (find(rolledDice.begin(), rolledDice.end(), nonFourKindValue) != rolledDice.end())
					{
						cout << "You might reroll " << nonFourKindValue << " to try to get a higher die." << endl;
						diceToRollAgain.push_back(nonFourKindValue);
						for (int die : currentDiceValues)
						{
							if (die != nonFourKindValue)
							{
								diceToKeep.push_back(die);
							}
						}
					}
					else
					{
						cout << "\nYou should stand with Four of a Kind as you cannot reroll " << nonFourKindValue << "!" << endl;
						diceToKeep = currentDiceValues;
					}
				}
				else
				{
					cout << "\nYou should stand with Four of a Kind as the non-four of a kind value is 6 and Yahtzee is not available!" << endl;
					diceToKeep = currentDiceValues;
				}
			}
		}
		else
		{
			if (currentDiceValues[0] < 4)
			{
				cout << "\nYou might reroll to try to get a higher die to add to the sum!" << endl;
				for (int i = 0; i < 4; i++)
				{
					diceToKeep.push_back(currentDiceValues[i]);
				}
				diceToRollAgain.push_back(currentDiceValues[4]);
			}
			else
			{
				cout << "\nYou should stand with Four of a Kind!" << endl;
				diceToKeep = currentDiceValues;
			}
		}
	}
	else if (bestCategory == "Three of a Kind")
	{
		int threeKindValue = -1;
		for (const auto &pair : diceCount)
		{
			if (pair.second >= 3)
			{
				threeKindValue = pair.first;
			}
		}

		int fullHousePoints = ScoreCard::calculatePoints("Full House", currentDiceValues);

		if (currentMaximumPoints > fullHousePoints && fullHousePoints == 25)
		{
			cout << "You might stand with Three of a Kind as it scores higher than a Full House." << endl;
			diceToKeep = currentDiceValues;
		}

		if (ScoreCard::isCategoryAvailable("Yahtzee") || ScoreCard::isCategoryAvailable("Full House"))
		{
			if (ScoreCard::isCategoryAvailable("Yahtzee") && ScoreCard::isCategoryAvailable("Full House"))
			{
				if (diceCount[threeKindValue] == 3)
				{
					bool isBothAvailableForReroll = true;
					bool atLeastOneAvailableForReroll = false;
					for (int die : currentDiceValues)
					{
						if (die != threeKindValue)
						{
							if (find(rolledDice.begin(), rolledDice.end(), die) == rolledDice.end())
							{
								isBothAvailableForReroll = false;
							}
							else
							{
								atLeastOneAvailableForReroll = true;
							}
						}
					}

					if (isBothAvailableForReroll)
					{
						cout << "\nYou might attempt to go for Yahtzee or Full House!" << endl;
						for (int die : currentDiceValues)
						{
							if (die == threeKindValue)
							{
								diceToKeep.push_back(die);
							}
							else
							{
								diceToRollAgain.push_back(die);
							}
						}
					}
					else if (atLeastOneAvailableForReroll)
					{
						for (int die : currentDiceValues)
						{
							if (die != threeKindValue && find(rolledDice.begin(), rolledDice.end(), die) != rolledDice.end() && die != 6)
							{
								cout << "\nYou might reroll " << die << " to try to get a higher die." << endl;
								diceToRollAgain.push_back(die);
							}
							else
							{
								diceToKeep.push_back(die);
							}
						}
					}
					else
					{
						cout << "\nYou should stand with Three of a Kind as you cannot reroll the remaining dice!" << endl;
						diceToKeep = currentDiceValues;
					}
				}
				else
				{
					bool isSingleAvailableForReroll = false;
					for (int die : currentDiceValues)
					{
						if (die != threeKindValue && find(rolledDice.begin(), rolledDice.end(), die) != rolledDice.end())
						{
							cout << "\nYou might reroll " << die << " to try to get Yahtzee!" << endl;
							isSingleAvailableForReroll = true;
						}
					}

					if (isSingleAvailableForReroll)
					{
						for (int die : currentDiceValues)
						{
							if (die == threeKindValue)
							{
								diceToKeep.push_back(die);
							}
							else
							{
								diceToRollAgain.push_back(die);
							}
						}
					}
					else
					{
						cout << "\nYou should stand with Three of a Kind as you cannot reroll the remaining dice!" << endl;
						diceToKeep = currentDiceValues;
					}
				}
			}
			else if (ScoreCard::isCategoryAvailable("Yahtzee") && !ScoreCard::isCategoryAvailable("Full House"))
			{
				vector<int> nonThreeKindValues;
				for (int die : currentDiceValues)
				{
					if (die != threeKindValue)
					{
						nonThreeKindValues.push_back(die);
					}
				}
				bool canRoll = true;
				for (int die : nonThreeKindValues)
				{
					if (find(rolledDice.begin(), rolledDice.end(), die) == rolledDice.end())
					{
						canRoll = false;
					}
				}

				if (canRoll)
				{
					cout << "You might attempt to go for Yahtzee!" << endl;
					for (int die : currentDiceValues)
					{
						if (die == threeKindValue)
						{
							diceToKeep.push_back(die);
						}
						else
						{
							diceToRollAgain.push_back(die);
						}
					}
				}
				else
				{
					cout << "You should stand with Three of a Kind as you cannot reroll the remaining dice!" << endl;
					diceToKeep = currentDiceValues;
				}
			}
			else
			{
				if (diceCount[threeKindValue] == 3)
				{
					vector<int> nonThreeKindValues;
					for (int die : currentDiceValues)
					{
						if (die != threeKindValue)
						{
							nonThreeKindValues.push_back(die);
						}
					}
					bool canRoll = false;
					for (int die : nonThreeKindValues)
					{
						if (find(rolledDice.begin(), rolledDice.end(), die) != rolledDice.end())
						{
							canRoll = true;
						}
					}

					if (canRoll)
					{
						cout << "You might attempt to go for Full House!" << endl;
						for (int die : currentDiceValues)
						{
							if (die == threeKindValue)
							{
								diceToKeep.push_back(die);
							}
							else
							{
								diceToRollAgain.push_back(die);
							}
						}
					}
					else
					{
						cout << "You should stand with Three of a Kind as you cannot reroll the remaining dice!" << endl;
						diceToKeep = currentDiceValues;
					}
				}
				else
				{
					bool isSingleAvailableForReroll = false;
					bool isOneThreeKindValueAvailable = false;
					for (int die : currentDiceValues)
					{
						if (die != threeKindValue && find(rolledDice.begin(), rolledDice.end(), die) != rolledDice.end())
						{
							isSingleAvailableForReroll = true;
						}
						if (die == threeKindValue && find(rolledDice.begin(), rolledDice.end(), die) != rolledDice.end())
						{
							isOneThreeKindValueAvailable = true;
						}
					}

					if (isSingleAvailableForReroll && isOneThreeKindValueAvailable)
					{
						cout << "You might attempt to go for Full House!" << endl;
						int count = 0;
						for (int die : currentDiceValues)
						{
							if (die == threeKindValue && count < 3)
							{
								diceToKeep.push_back(die);
								count++;
							}
							else
							{
								diceToRollAgain.push_back(die);
							}
						}
					}
					else
					{
						cout << "\nYou should stand with Three of a Kind as you cannot reroll the remaining dice!" << endl;
						diceToKeep = currentDiceValues;
					}
				}
			}
		}
		else
		{
			for (int value : currentDiceValues)
			{
				if (diceCount[value] <= 2)
				{
					if (value < 6 && find(rolledDice.begin(), rolledDice.end(), value) != rolledDice.end())
					{
						diceToRollAgain.push_back(value);
					}
					else
					{
						diceToKeep.push_back(value);
					}
				}
				else
				{
					diceToKeep.push_back(value);
				}
			}
			if (!diceToRollAgain.empty())
			{
				cout << "You might decide to roll again to try and get higher die values!" << endl;
			}
			else
			{
				cout << "You should stand with Three of a Kind as you cannot reroll the remaining dice!" << endl;
				diceToKeep = currentDiceValues;
			}
		}
	}
	else if (bestCategory == "Aces" || bestCategory == "Twos" || bestCategory == "Threes" || bestCategory == "Fours" || bestCategory == "Fives" || bestCategory == "Sixes")
	{
		int targetValue = -1;

		if (bestCategory == "Aces")
			targetValue = 1;
		else if (bestCategory == "Twos")
			targetValue = 2;
		else if (bestCategory == "Threes")
			targetValue = 3;
		else if (bestCategory == "Fours")
			targetValue = 4;
		else if (bestCategory == "Fives")
			targetValue = 5;
		else if (bestCategory == "Sixes")
			targetValue = 6;

		vector<int> pairs;
		vector<int> nonPairs;
		bool isStraightPossible = false;
		for (const auto &pair : diceCount)
		{
			if (pair.second >= 2)
			{
				pairs.push_back(pair.first);
			}
			else if (pair.second == 1)
			{
				nonPairs.push_back(pair.first);
			}
		}

		if (pairs.size() == 1)
		{
			vector<int> sortedDice = currentDiceValues;
			set<int> temp(currentDiceValues.begin(), currentDiceValues.end());

			vector<int> straight = {1, 2, 3, 4, 5};
			vector<int> straight2 = {2, 3, 4, 5, 6};

			int count = 0;
			for (int die : temp)
			{
				if (find(straight.begin(), straight.end(), die) != straight.end())
				{
					count++;
				}
			}

			if (count == 4 && find(rolledDice.begin(), rolledDice.end(), pairs[0]) != rolledDice.end())
			{
				isStraightPossible = true;
			}
			else
			{
				count = 0;

				for (int die : temp)
				{
					if (find(straight2.begin(), straight2.end(), die) != straight2.end())
					{
						count++;
					}
				}

				if (count == 4 && find(rolledDice.begin(), rolledDice.end(), pairs[0]) != rolledDice.end())
				{
					isStraightPossible = true;
				}
			}
		}

		if (diceCount.size() == 1)
		{
			cout << "You have all dice with the same value. You should keep all dice." << endl;
			diceToKeep = currentDiceValues;
		}
		else if (ScoreCard::isCategoryAvailable("Five Straight") && isStraightPossible)
		{
			cout << "You might pursue a Five Straight!" << endl;
			int count = 0;
			for (int die : currentDiceValues)
			{
				if (die == pairs[0] && count < 1)
				{
					diceToRollAgain.push_back(die);
					count++;
				}
				else
				{
					diceToKeep.push_back(die);
				}
			}
		}
		else if (pairs.size() == 2 && ScoreCard::isCategoryAvailable("Full House"))
		{
			if (find(rolledDice.begin(), rolledDice.end(), nonPairs[0]) != rolledDice.end())
			{
				cout << "You might pursue a Full House!" << endl;
				for (int die : currentDiceValues)
				{
					if (die == pairs[0] || die == pairs[1])
					{
						diceToKeep.push_back(die);
					}
					else
					{
						diceToRollAgain.push_back(die);
					}
				}
			}
			else
			{
				int minPairValue = min(pairs[0], pairs[1]);
				int maxPairValue = max(pairs[0], pairs[1]);

				if (count(rolledDice.begin(), rolledDice.end(), minPairValue) == 2)
				{
					cout << "You might want to pursue a Full House!" << endl;
					for (int die : currentDiceValues)
					{
						if (die == minPairValue)
						{
							diceToRollAgain.push_back(die);
						}
						else
						{
							diceToKeep.push_back(die);
						}
					}
				}
				else if (count(rolledDice.begin(), rolledDice.end(), maxPairValue) == 2)
				{
					cout << "You might want to pursue a Full House!" << endl;
					for (int die : currentDiceValues)
					{
						if (die == maxPairValue)
						{
							diceToRollAgain.push_back(die);
						}
						else
						{
							diceToKeep.push_back(die);
						}
					}
				}
				else
				{
					cout << "\nYou should stand as you cannot reroll the non-pair die!" << endl;
					diceToKeep = currentDiceValues;
				}
			}
		}
		else if (pairs.size() == 1)
		{
			bool atLeastOneAvailableForReroll = false;
			bool isAllNonPairAvailableForReroll = true;

			for (int die : nonPairs)
			{
				if (find(rolledDice.begin(), rolledDice.end(), die) != rolledDice.end())
				{
					atLeastOneAvailableForReroll = true;
				}

				if (find(rolledDice.begin(), rolledDice.end(), die) == rolledDice.end())
				{
					isAllNonPairAvailableForReroll = false;
				}
			}

			if (ScoreCard::isCategoryAvailable("Yahtzee") || ScoreCard::isCategoryAvailable("Four of a Kind") ||
					ScoreCard::isCategoryAvailable("Three of a Kind") || ScoreCard::isCategoryAvailable("Full House"))
			{

				if (isAllNonPairAvailableForReroll)
				{
					cout << "You might pursue ";

					if (ScoreCard::isCategoryAvailable("Yahtzee"))
					{
						cout << "Yahtzee | ";
					}
					if (ScoreCard::isCategoryAvailable("Four of a Kind"))
					{
						cout << "Four of a Kind | ";
					}
					if (ScoreCard::isCategoryAvailable("Three of a Kind"))
					{
						cout << "Three of a Kind | ";
					}
					if (ScoreCard::isCategoryAvailable("Full House"))
					{
						cout << "Full House | ";
					}

					cout << endl;
					for (int die : currentDiceValues)
					{
						if (die == pairs[0])
						{
							diceToKeep.push_back(die);
						}
						else
						{
							diceToRollAgain.push_back(die);
						}
					}
				}
				else if (atLeastOneAvailableForReroll)
				{
					cout << "You might reroll one die to try to get maximum points as the non-pair die cannot be rerolled!" << endl;
					for (int die : currentDiceValues)
					{
						if (die == pairs[0])
						{
							diceToKeep.push_back(die);
						}
						else
						{
							if (find(rolledDice.begin(), rolledDice.end(), die) != rolledDice.end())
							{
								diceToRollAgain.push_back(die);
							}
							else
							{
								diceToKeep.push_back(die);
							}
						}
					}
				}
				else
				{
					cout << "You should stand as you cannot reroll the non-pair dice!" << endl;
					diceToKeep = currentDiceValues;
				}
			}
			else
			{
				if (isAllNonPairAvailableForReroll)
				{
					cout << "You might reroll non-pair dice to try to get higher dice!" << endl;
					for (int die : currentDiceValues)
					{
						if (die == pairs[0])
						{
							diceToKeep.push_back(die);
						}
						else
						{
							if (die != 6)
								diceToRollAgain.push_back(die);
							else
								diceToKeep.push_back(die);
						}
					}
				}
				else if (atLeastOneAvailableForReroll)
				{
					cout << "You might reroll one die to try to get maximum points as the non-pair die cannot be rerolled!" << endl;
					for (int die : currentDiceValues)
					{
						if (die == pairs[0])
						{
							diceToKeep.push_back(die);
						}
						else
						{
							if (find(rolledDice.begin(), rolledDice.end(), die) != rolledDice.end() && die != 6)
							{
								diceToRollAgain.push_back(die);
							}
							else
							{
								diceToKeep.push_back(die);
							}
						}
					}
				}
				else
				{
					cout << "You should stand as you cannot reroll the non-pair dice!" << endl;
					diceToKeep = currentDiceValues;
				}
			}
		}
		else
		{
			bool hasNoPairs = true;
			for (const auto &pair : diceCount)
			{
				if (pair.second >= 2)
				{
					hasNoPairs = false;
					break;
				}
			}

			if (hasNoPairs)
			{
				if (ScoreCard::isCategoryAvailable("Four Straight") || ScoreCard::isCategoryAvailable("Five Straight"))
				{
					if (find(rolledDice.begin(), rolledDice.end(), 1) != rolledDice.end())
					{
						cout << "No pairs found. You might attempt to pursue a Straight!" << endl;

						for (int value : currentDiceValues)
						{
							if (value == 1)
							{
								diceToRollAgain.push_back(value);
							}
							else
							{
								diceToKeep.push_back(value);
							}
						}

						if (!diceToRollAgain.empty())
						{
							cout << "You might reroll Aces to pursue a straight." << endl;
						}
					}
					else
					{
						cout << "You might reroll currently rolled dice to try to get higher die values!" << endl;
						for (int value : currentDiceValues)
						{
							if (find(rolledDice.begin(), rolledDice.end(), value) != rolledDice.end())
							{
								diceToRollAgain.push_back(value);
							}
							else
							{
								diceToKeep.push_back(value);
							}
						}
					}
				}
			}
			else
			{
				for (int value : currentDiceValues)
				{
					if (value == targetValue)
					{
						diceToKeep.push_back(value);
					}
					else
					{
						if (find(rolledDice.begin(), rolledDice.end(), value) != rolledDice.end())
							diceToRollAgain.push_back(value);
						else
							diceToKeep.push_back(value);
					}
				}
				if (!diceToRollAgain.empty())
					cout << "You might reroll to try to get more " << targetValue << "'s." << endl;
				else
					cout << "You should stand on " << targetValue << " as you cannot reroll the remaining dice!" << endl;
			}
		}
	}
	else
	{
		int maxCount = 0;
		int maxValue = -1;

		for (const auto &pair : diceCount)
		{
			if (pair.second > maxCount)
			{
				maxCount = pair.second;
				maxValue = pair.first;
			}
		}

		bool pursuedCategory = false;

		if (ScoreCard::isCategoryAvailable("Yahtzee"))
		{
			if (maxCount >= 2)
			{
				bool canReroll = true;
				for (int die : currentDiceValues)
				{
					if (die != maxValue && find(rolledDice.begin(), rolledDice.end(), die) == rolledDice.end())
					{
						canReroll = false;
						break;
					}
				}

				if (canReroll)
				{
					cout << "You might pursue a Yahtzee!" << endl;
					for (int die : currentDiceValues)
					{
						if (die == maxValue)
						{
							diceToKeep.push_back(die);
						}
						else
						{
							diceToRollAgain.push_back(die);
						}
					}
					pursuedCategory = true;
				}
				else
				{
					cout << "Cannot reroll necessary dice to pursue Yahtzee." << endl;
				}
			}
			else
			{
				cout << "Not enough matching dice to pursue Yahtzee." << endl;
			}
		}

		if (!pursuedCategory && ScoreCard::isCategoryAvailable("Full House"))
		{
			vector<int> pairs;
			vector<int> singles;
			for (const auto &pair : diceCount)
			{
				if (pair.second >= 2)
				{
					pairs.push_back(pair.first);
				}
				else
				{
					singles.push_back(pair.first);
				}
			}

			if (!pairs.empty())
			{
				bool canReroll = true;
				for (int die : currentDiceValues)
				{
					if (diceCount[die] == 1 && find(rolledDice.begin(), rolledDice.end(), die) == rolledDice.end())
					{
						canReroll = false;
						break;
					}
				}

				if (canReroll)
				{
					cout << "You might pursue a Full House!" << endl;
					for (int die : currentDiceValues)
					{
						if (diceCount[die] >= 2)
						{
							diceToKeep.push_back(die);
						}
						else
						{
							diceToRollAgain.push_back(die);
						}
					}
					pursuedCategory = true;
				}
				else
				{
					cout << "Cannot reroll necessary dice to pursue Full House." << endl;
				}
			}
			else
			{
				cout << "No pairs to pursue Full House." << endl;
			}
		}

		if (!pursuedCategory)
		{
			cout << "You should stand as you cannot pursue Yahtzee or Full House." << endl;
			diceToKeep = currentDiceValues;
		}
	}

	cout << "\nYou should keep these dice: ";
	if (diceToKeep.empty())
		cout << "None";
	else
	{
		for (int die : diceToKeep)
		{
			cout << die << " ";
		}
	}
	cout << endl;

	cout << "\nYou should reroll these dice: ";
	if (diceToRollAgain.empty())
		cout << "None";
	else
	{
		for (int die : diceToRollAgain)
		{
			cout << die << " ";
		}
	}
	cout << endl;
}