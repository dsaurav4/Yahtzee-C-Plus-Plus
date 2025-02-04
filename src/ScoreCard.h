#pragma once
class ScoreCard
{
public:
	static void displayScoreCard();
	static bool isAllCategoriesFilled();
	static void displayAllAvailableCategories();
	static vector<string> getCategoryToChoose(const vector<int> diceValues);
	static void displayPossiblePoints(const vector<int> diceValues);
	static void chooseCategory(const string category, const vector<int> diceValues, const string winner, const int round);
	static int calculatePoints(string category, vector<int> diceValues);
	static pair<string, int> getBestHands(vector<int> diceValues);
	static bool isCategoryAvailable(string category);
	static int getTotalScore(string name);
	vector<string> getAllCategories() const;
	unordered_map <string, pair<string, pair<int, int>>> getScoreBoard() const;
	void setScoreBoard(unordered_map <string, pair<string, pair<int, int>>> newScoreBoard);


private:
	static const char* rows[12];
	static unordered_map <string, pair<string, pair<int, int>>> scores;
	
};

