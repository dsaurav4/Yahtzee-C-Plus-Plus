#include "stdafx.h"
#include "ScoreCard.h"
#include "Round.h"

//rows is an array of strings that contains the names of the categories in the scorecard
const char* ScoreCard::rows[12] = { "Aces", "Twos", "Threes", "Fours", "Fives", "Sixes", "Three of a Kind", "Four of a Kind", 
"Full House", "Four Straight", "Five Straight", "Yahtzee" };

// scores is an unordered map that contains the category name as the key and a pair as the value. 
// The pair contains the name of the player who chose the category, the points earned in that category, 
// and the round in which the category was chosen.
unordered_map <string, pair<string, pair<int, int>>> ScoreCard::scores = {
	{ "Aces", make_pair("", make_pair(0, 0)) },
	{ "Twos", make_pair("", make_pair(0, 0)) },
	{ "Threes", make_pair("", make_pair(0, 0)) },
	{ "Fours", make_pair("", make_pair(0, 0)) },
	{ "Fives", make_pair("", make_pair(0, 0)) },
	{ "Sixes", make_pair("", make_pair(0, 0)) },
	{ "Three of a Kind", make_pair("", make_pair(0, 0)) },
	{ "Four of a Kind", make_pair("", make_pair(0, 0)) },
	{ "Full House", make_pair("", make_pair(0, 0)) },
	{ "Four Straight", make_pair("", make_pair(0, 0)) },
	{ "Five Straight", make_pair("", make_pair(0, 0)) },
	{ "Yahtzee", make_pair("", make_pair(0, 0)) }
};


/****************************************************************
 * Function Name: ScoreCard::displayScoreCard
 * Purpose: To display the current scorecard with categories,
 *          winners, points, and round information in a formatted table.
 * Parameters: None
 * Return Value: None
 * Reference: None
 ****************************************************************/
void ScoreCard::displayScoreCard() {
	// headers stores the names of the columns for the scorecard table
	const char* headers[] = { "Category", "Winner", "Points", "Round" };

	// Sets the output alignment to left for consistent column formatting
	cout << left;

	// Prints the table headers with specified widths and separators
	cout << setw(20) << headers[0] << "|"
		<< setw(10) << headers[1] << "|"
		<< setw(10) << headers[2] << "|"
		<< setw(10) << headers[3]
		<< endl;

	// Prints a separator line to distinguish headers from data rows
	cout << string(53, '-') << endl;

	// Iterates through each category to display its corresponding details
	for (int i = 0; i < 12; ++i) {
		// rows stores the names of all categories in the scorecard
		// scores stores the scoring information for each category
		cout << setw(20) << rows[i] << "|"
			<< setw(10) << scores[rows[i]].first << "|"
			<< setw(10) << scores[rows[i]].second.first << "|"
			<< setw(10) << scores[rows[i]].second.second
			<< endl;
	}
}


/****************************************************************
 * Function Name: ScoreCard::isAllCategoriesFilled
 * Purpose: To check whether all categories in the scorecard have been filled.
 * Parameters: None
 * Return Value:
 *         bool - Returns true if all categories are filled, false otherwise.
 * Reference: None
 ****************************************************************/
bool ScoreCard::isAllCategoriesFilled() {
	for (auto& score : scores) {
		if (score.second.first == "") {
			// If any category has an empty winner, not all categories are filled
			return false;
		}
	}
	// All categories have been filled
	return true;
}


/****************************************************************
 * Function Name: ScoreCard::displayAllAvailableCategories
 * Purpose: To display all categories in the scorecard that are still available
 *          in a formatted list.
 * Parameters: None
 * Return Value: None
 * Reference: None
 ****************************************************************/
void ScoreCard::displayAllAvailableCategories() {
	// Display the heading for available categories
	cout << "\nAvailable categories: " << endl;

	// Iterate through each category in the scorecard
	for (int i = 0; i < 12; ++i) {
		// category stores the name of the current category being checked
		string category = rows[i];

		// Check if the current category has not been scored yet
		if (scores[category].first == "") {
			// Display the available category
			cout << category << "\n";
		}
	}
	cout << endl;
}



/****************************************************************
 * Function Name: ScoreCard::displayPossiblePoints
 * Purpose: To display potential points in all available categories
 *          based on the current dice values.
 * Parameters:
 *         diceValues, a vector of integers passed by value.
 *             It stores the current dice values rolled by the player.
 * Reference: None
 * Return Value: None
 ****************************************************************/
void ScoreCard::displayPossiblePoints(const vector<int> diceValues) {
	// Display the heading for potential points in available categories
	cout << "\nPotential points in available categories: " << endl;

	// Iterate through each category in the scorecard
	for (int i = 0; i < 12; ++i) {
		// category stores the name of the current category being checked
		string category = rows[i];

		// Check if the current category has not been scored yet
		if (scores[category].first == "") {
			// points stores the calculated points for the current category
			int points = calculatePoints(category, diceValues);

			// If the category yields non-zero points, display it
			if (points != 0) {
				cout << category << ": " << points << "\n";
			}
		}
	}

	// Add an empty line after listing potential points
	cout << endl;
}


/****************************************************************
 * Function Name: ScoreCard::isCategoryAvailable
 * Purpose: To check if a specific category is available in the scorecard.
 * Parameters:
 *         Category, a string passed by value.
 *             It stores the name of the category to be checked.
 * Return Value:
 *         bool - Returns true if the category is available, false otherwise.
 * Reference: None
 ****************************************************************/
bool ScoreCard::isCategoryAvailable(string Category) {
	//iterate through the scorecard
	for (auto& score : scores) {
		if (score.first == Category) {
			//if the category is available, return true
			if (score.second.first == "") {
				return true;
			}
		}
	}
	//if the category is not available, return false
	return false;
}

/****************************************************************
 * Function Name: ScoreCard::getCategoryToChoose
 * Purpose: To return a vector of strings containing the names of all
 *          available categories in the scorecard based on the current dice values.
 * Parameters:
 *         diceValues, a vector of integers passed by value.
 *             It stores the current dice values rolled by the player.
 * Return Value:
 *         vector<string> - A vector of strings containing the names of all available categories.
 * Reference: None
 ****************************************************************/
vector<string> ScoreCard::getCategoryToChoose(const vector<int> diceValues) {
	//availableCategories stores the names of all available categories
	vector<string> availableCategories;

	for (int i = 0; i < 12; i++) {
		//category stores the name of the current category being checked
		string category = rows[i];
		//if the category is available
		if (scores[category].first == "") {
			//if the category yields non-zero points, add it to the list of available categories
			if (calculatePoints(category, diceValues) != 0) {
				availableCategories.push_back(category);
			}
		}
	}
	return availableCategories;
}

/****************************************************************
 * Function Name: ScoreCard::chooseCategory
 * Purpose: To update the scorecard with the chosen category, winner, points, and round information.
 * Parameters:
 *         category, a string passed by value.
 *             It stores the name of the category to be chosen.
 *         diceValues, a vector of integers passed by value.
 *             It stores the current dice values rolled by the player.
 *         winner, a string passed by value.
 *             It stores the name of the player who chose the category.
 *         round, an integer passed by value.
 *             It stores the round in which the category was chosen.
 * Return Value: None
 * Reference: None
 ****************************************************************/
void ScoreCard::chooseCategory(string category, vector<int> diceValues, string winner, int round) {
	//if the category is available
	if (scores[category].first == "") {
		//points stores the calculated points for the chosen category
		int points = calculatePoints(category, diceValues);
		//update the scorecard with the chosen category, winner, points, and round information
		scores[category] = make_pair(winner, make_pair(points, round));
	}
	//if the category is already filled
	else {
		cout << "Category already filled!" << endl;
	}
}

/****************************************************************
 * Function Name: ScoreCard::getBestHands
 * Purpose: To return the best possible hand based on the current dice values.
 * Parameters:
 *         diceValues, a vector of integers passed by value.
 *             It stores the current dice values rolled by the player.
 * Return Value:
 *         pair<string, int> - A pair containing the name of the best hand and the points earned.
 * Algorithm:
*			1. Initialize bestHand as an empty string and 0 points.
*			2. Iterate through each category in the scorecard.
*			3. If the category is not filled, calculate the points for the category.
*			4. If the points are greater than 0, set pointsEarned as true.
*			5. If the points are greater than or equal to the bestHand points, update bestHand with the category and points.
*			6. If no points are earned, return an empty pair.
*			7. Return the bestHand pair.
 * Reference: None
 ****************************************************************/
pair<string, int> ScoreCard::getBestHands(vector<int> diceValues) {
	//bestHand stores the name of the best hand and the points earned
	pair<string, int> bestHand = { "", 0 };  
	//pointsEarned stores whether points are earned in any category
	bool pointsEarned = false; 

	//iterate through each category in the scorecard
	for (int i = 0; i < 12; ++i) {
		//category stores the name of the current category being checked
		string category = rows[i];

		//if the category is not filled
		if (scores[category].first == "") {
			//points stores the calculated points for the category
			int points = calculatePoints(category, diceValues);

			// if points are greater than 0
			if (points > 0) {
				pointsEarned = true;

				//if the points are greater than or equal to the bestHand points, update bestHand
				if (points >= bestHand.second) {
					bestHand = make_pair(category, points);
				}
			}
		}
	}

	//if no points are earned, return an empty pair
	if (!pointsEarned) {
		return { "", 0 };
	}

	//return the bestHand pair
	return bestHand;
}

/****************************************************************
 * Function Name: ScoreCard::getTotalScore
 * Purpose: To calculate the total score of a player based on the categories filled in the scorecard.
 * Parameters:
 *         name, a string passed by value.
 *             It stores the name of the player whose total score is to be calculated.
 * Return Value:
 *         int - The total score of the player.
 * Algorithm:
 *			1. Initialize totalScore as 0.
 *			2. Iterate through each category in the scorecard.
 *			3. If the player's name matches the winner of the category, add the points to the total score.
 *			4. Return the total score.
 * Reference: None
 ****************************************************************/
int ScoreCard::getTotalScore(string name) {
	int totalScore = 0;

	for (auto& score : scores) {
		if (score.second.first == name) {
			totalScore += score.second.second.first;
		}
	}

	return totalScore;
}

/****************************************************************
 * Function Name: ScoreCard::calculatePoints
 * Purpose: To calculate the points earned in a specific category based on the current dice values.
 * Parameters:
 *         category, a string passed by value.
 *             It stores the name of the category for which points are to be calculated.
 *         diceValues, a vector of integers passed by value.
 *             It stores the current dice values rolled by the player.
 * Return Value:
 *         int - The points earned in the category.
 * Algorithm:
 *			1. Initialize points as 0.
 *			2. If the category is "Aces", "Twos", "Threes", "Fours", "Fives", or "Sixes", calculate the points based on the dice values.
 *			3. If the category is "Three of a Kind" or "Four of a Kind", calculate the points based on the dice values.
 *			4. If the category is "Full House", calculate the points based on the dice values.
 *			5. If the category is "Four Straight", calculate the points based on the dice values.
 *			6. If the category is "Five Straight", calculate the points based on the dice values.
 *			7. If the category is "Yahtzee", calculate the points based on the dice values.
 *			8. If the category is invalid, display an error message.
 *			9. Return the points earned.
 * Reference: None
 ****************************************************************/
int ScoreCard::calculatePoints(string category, vector<int> diceValues) {
    // points stores the total points calculated for the category
    int points = 0;

    if (category == "Aces") {
        // Iterate through each die to sum up the points for Aces
        for (int value : diceValues) {
            if (value == 1) {
                points += 1;
            }
        }
    }
    else if (category == "Twos") {
        // Iterate through each die to sum up the points for Twos
        for (int value : diceValues) {
            if (value == 2) {
                points += 2;
            }
        }
    }
    else if (category == "Threes") {
        // Iterate through each die to sum up the points for Threes
        for (int value : diceValues) {
            if (value == 3) {
                points += 3;
            }
        }
    }
    else if (category == "Fours") {
        // Iterate through each die to sum up the points for Fours
        for (int value : diceValues) {
            if (value == 4) {
                points += 4;
            }
        }
    }
    else if (category == "Fives") {
        // Iterate through each die to sum up the points for Fives
        for (int value : diceValues) {
            if (value == 5) {
                points += 5;
            }
        }
    }
    else if (category == "Sixes") {
        // Iterate through each die to sum up the points for Sixes
        for (int value : diceValues) {
            if (value == 6) {
                points += 6;
            }
        }
    }
    else if (category == "Three of a Kind") {
        // valueCount stores the count of each die value
        map<int, int> valueCount;
        for (int value : diceValues) {
            valueCount[value]++;
        }
        // Check if any die value appears at least three times
        for (auto& value : valueCount) {
            if (value.second >= 3) {
                // Sum all dice values if Three of a Kind is achieved
                for (int value : diceValues) {
                    points += value;
                }
                break;
            }
        }
    }
    else if (category == "Four of a Kind") {
        // valueCount stores the count of each die value
        map<int, int> valueCount;
        for (int value : diceValues) {
            valueCount[value]++;
        }
        // Check if any die value appears at least four times
        for (auto& value : valueCount) {
            if (value.second >= 4) {
                // Sum all dice values if Four of a Kind is achieved
                for (int value : diceValues) {
                    points += value;
                }
                break;
            }
        }
    }
    else if (category == "Full House") {
        // valueCount stores the count of each die value
        map<int, int> valueCount;
        for (int value : diceValues) {
            valueCount[value]++;
        }

        // temp stores the counts of dice values that are 2 or 3
        vector<int> temp;

        // Check for a combination of three of one kind and two of another
        for (auto& value : valueCount) {
            if (value.second == 3 || value.second == 2) {
                temp.push_back(value.second);
            }

            if (temp.size() == 2) {
                // If there is one three of a kind and one pair, assign 25 points
                temp[1] != temp[0] ? points += 25 : points += 0;
            }
        }
    }
    else if (category == "Four Straight")
    {
        // tempSet stores unique dice values
        set<int> tempSet(diceValues.begin(), diceValues.end());

        // temp stores the sorted unique dice values
        vector<int> temp(tempSet.begin(), tempSet.end());

        if (temp.size() >= 4) {
            // hasFourStraight indicates whether a four-number straight is found
            bool hasFourStraight = false;

            // Check for any sequence of four consecutive numbers
            for (size_t i = 0; i <= temp.size() - 4; ++i) {
                if (temp[i + 1] == temp[i] + 1 &&
                    temp[i + 2] == temp[i] + 2 &&
                    temp[i + 3] == temp[i] + 3) {
                    hasFourStraight = true;
                    break;
                }
            }

            if (hasFourStraight) {
                // Assign 30 points for Four Straight
                points = 30;
            }
            else {
                points = 0;
            }
        }
        else {
            points = 0;
        }
    }

    else if (category == "Five Straight")
    {
        // temp stores a sorted copy of diceValues
        vector<int> temp = diceValues;
        sort(temp.begin(), temp.end());
        // Check for specific five-number straights
        if (temp[0] == 1 && temp[1] == 2 && temp[2] == 3 && temp[3] == 4 && temp[4] == 5) {
            points += 40;
        }
        else if (temp[0] == 2 && temp[1] == 3 && temp[2] == 4 && temp[3] == 5 && temp[4] == 6) {
            points += 40;
        }
        else {
            points = 0;
        }
    }
    else if (category == "Yahtzee") {
        // valueCount stores the count of each die value
        map<int, int> valueCount;
        for (int value : diceValues) {
            valueCount[value]++;
            if (valueCount[value] == 5) {
                // Assign 50 points for Yahtzee
                points = 50;
                break;
            }
        }
    }
    else {
        // Handle invalid category input
        cout << category << endl;
        cout << "Invalid category!" << endl;
    }

    // Return the calculated points for the specified category
    return points;
}

/****************************************************************
 * Function Name: ScoreCard::getScoreBoard
 * Purpose: To return the scorecard with categories, winners, points, and round information.
 * Parameters: None
 * Return Value:
 *         unordered_map <string, pair<string, pair<int, int>>> - The scorecard with all categories and their details.
 * Reference: None
 ****************************************************************/
unordered_map <string, pair<string, pair<int, int>>> ScoreCard::getScoreBoard() const{
	return scores;
}

/****************************************************************
 * Function Name: ScoreCard::getAllCategories
 * Purpose: To return a vector of strings containing the names of all categories in the scorecard.
 * Parameters: None
 * Return Value:
 *         vector<string> - A vector of strings containing the names of all categories.
 * Reference: None
 ****************************************************************/
vector<string> ScoreCard::getAllCategories() const {
	//categories stores the names of all categories in the scorecard
	vector<string> categories;

	//iterate through the scorecard
	for (int i = 0; i < 12; i++) {
		categories.push_back(rows[i]);
	}

	return categories;
}

/****************************************************************
 * Function Name: ScoreCard::setScoreBoard
 * Purpose: To update the scorecard with a new scorecard.
 * Parameters:
 *         newScoreBoard, an unordered_map <string, pair<string, pair<int, int>>> passed by value.
 *             It stores the new scorecard to be set.
 * Return Value: None
 * Reference: None
 ****************************************************************/
void ScoreCard::setScoreBoard(unordered_map <string, pair<string, pair<int, int>>> newScoreBoard) {
	scores = newScoreBoard;
}