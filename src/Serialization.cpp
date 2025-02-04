#include "stdafx.h"
#include "Serialization.h"
#include "ScoreCard.h"
#include "Round.h"


/****************************************************************
 * Function Name: Serialization::saveGame
 * Purpose: To save the current game state to a specified file.
 * Parameters: None
 * Return Value: None
 * Reference: none
 ****************************************************************/
void Serialization::saveGame() {
    // fileName stores the name of the file where the game will be saved
    string fileName;
    // outFile is an output file stream used to write data to the file
    ofstream outFile;

    // Continuously prompt the user for a valid filename until successful
    while (true) {
        // Prompt the user to enter the filename
        cout << "Enter the filename to save the game to: ";
        cin >> fileName;

        // Attempt to open the file with the provided filename and a .txt extension
        outFile.open(fileName + ".txt");

        // Check if the file was opened successfully
        if (!outFile) {
            // Display an error message if the file cannot be opened
            cerr << "Error opening file for saving. Please try again." << endl;
        }
        else {
            // Exit the loop if the file is opened successfully
            break;
        }
    }

    // scoreCard is an instance of ScoreCard used to retrieve scoring information
    ScoreCard scoreCard;

    // categoryList stores all the category names from the scorecard
    vector<string> categoryList = scoreCard.getAllCategories();

    // scores stores the scoring information for each category
    unordered_map<string, pair<string, pair<int, int>>> scores = scoreCard.getScoreBoard();


    outFile << "Round: " << Round::getRoundNumber() << "\n\n";
    outFile << "Scorecard:\n";

    // Iterate through each category to save its score details
    for (int i = 0; i < 12; ++i) {
        // category stores the name of the current category being processed
        string category = categoryList[i];

        // Check if the current category has been scored 
        if (scores[category].first != "") {
            // points stores the points earned in the current category
            int points = scores[category].second.first;
            // winner stores the name of the player who won the current category
            string winner = scores[category].first;
            // roundScored stores the round number when the current category was scored
            int roundScored = scores[category].second.second;

            // Write the points, winner, and round number to the file for the current category
            outFile << points << " " << winner << " " << roundScored << "\n";
        }
        else {
            // If the category has not been scored yet, write a default value of 0
            outFile << "0\n";
        }
    }

    // Close the file 
    outFile.close();
    // Inform the user that the game has been saved successfully
    cout << "Game saved successfully to " << fileName << std::endl;
}


/****************************************************************
 * Function Name: Serialization::loadGame
 * Purpose: To load the game state from a specified file, restoring
 *          the current round number and scorecard information.
 * Parameters: None
 * Return Value: None
 * Reference: none
 ****************************************************************/
void Serialization::loadGame() {
    // fileName stores the name of the file from which the game will be loaded
    string fileName;
    // inFile is an input file stream used to read data from the file
    ifstream inFile;
    // scoreCard is an instance of ScoreCard used to retrieve and set scoring information
    ScoreCard scoreCard;

    // Continuously prompt the user for a valid filename until the file is successfully opened
    while (true) {
        // Prompt the user to enter the filename
        cout << "Enter the filename to load the game from: ";
        cin >> fileName;

        inFile.open(fileName);

        // Check if the file was opened successfully
        if (!inFile) {
            // Display an error message if the file cannot be opened
            cerr << "Error opening file for loading. Please try again." << endl;
        }
        else {
            // Exit the loop if the file is opened successfully
            break;
        }
    }

    // line stores each line read from the file
    string line;

    // Read the first line to get the round number
    getline(inFile, line);
    if (line.find("Round:") != string::npos) {
        // ss is a string stream used to parse the round number
        istringstream ss(line);
        // temp stores the "Round:" keyword
        string temp;
        // roundNumber stores the extracted round number
        int roundNumber;
        ss >> temp >> roundNumber;
        // Set the current round number using the extracted value
        Round::setRoundNumber(roundNumber);
    }
    else {
        // Display an error message if the "Round:" keyword is missing
        cerr << "Invalid save file format: Missing 'Round:'." << endl;
        return;
    }

    // Read the next line (expected to be empty)
    getline(inFile, line);

    // Read the line that should contain "Scorecard:"
    getline(inFile, line);
    if (line != "Scorecard:") {
        // Display an error message if the "Scorecard:" header is missing
        cerr << "Invalid save file format: Missing 'Scorecard:' header." << endl;
        return;
    }

    // categoryList stores all the category names from the scorecard
    vector<string> categoryList = scoreCard.getAllCategories();
    // scores stores the scoring information for each category
    unordered_map<string, pair<string, pair<int, int>>> scores = scoreCard.getScoreBoard();

    // Iterate through each category to load its score details
    for (int i = 0; i < 12; ++i) {
        getline(inFile, line);
        if (line == "0") {
            // If the line is "0", the category is unscored
            scores[categoryList[i]] = make_pair("", make_pair(0, 0));
        }
        else {
            // ss is a string stream used to parse points, winner, and roundScored
            istringstream ss(line);
            // points stores the points earned in the current category
            int points;
            // winner stores the name of the player who won the current category
            string winner;
            // roundScored stores the round number when the current category was scored
            int roundScored;
            ss >> points >> winner >> roundScored;
            // Update the scores map with the loaded data
            scores[categoryList[i]] = make_pair(winner, make_pair(points, roundScored));
        }
    }

    // categoryIndex keeps track of the current category being processed
    int categoryIndex = 0;
    // Continue reading lines and updating scores until all categories are processed
    while (getline(inFile, line) && categoryIndex < categoryList.size()) {
        // category stores the name of the current category being processed
        string category = categoryList[categoryIndex];

        if (line == "0") {
            // If the line is "0", the category is unscored
            scores[category] = make_pair("", make_pair(0, 0));
        }
        else {
            // ss is a string stream used to parse points, winner, and roundScored
            istringstream ss(line);
            // points stores the points earned in the current category
            int points;
            // winner stores the name of the player who won the current category
            string winner;
            // roundScored stores the round number when the current category was scored
            int roundScored;
            ss >> points >> winner >> roundScored;

            // Update the scores map with the loaded data
            scores[category] = make_pair(winner, make_pair(points, roundScored));
        }

        // Move to the next category
        categoryIndex++;
    }

    // Update the scoreCard with the loaded scores
    scoreCard.setScoreBoard(scores);

    // Close the input file after loading all necessary information
    inFile.close();
    cout << "Game loaded successfully from " << fileName << std::endl;
}
