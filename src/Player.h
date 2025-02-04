#pragma once
#include "stdafx.h"

class Player
{
public:
	virtual int turnChooseRoll() = 0;
	virtual bool isHuman() = 0;
	virtual void playTurn() = 0;
	int getTotalScore();
	string getName();

protected:
	string name;
	vector<int> rollOrSet(int diceCount);
};

class Human : public Player
{
public:
	Human();
	int turnChooseRoll();


private:
	bool isHuman();
	void playTurn();
	void chooseCategory(const vector<int> finalDiceValues);
	void firstRollHelp(const vector<int> currentDiceValues);
	void secondRollHelp(const vector<int> rolledDice, const vector<int> keptDice);
};

class Computer : public Player
{
public:
	Computer();
	int turnChooseRoll();

private:
	bool isHuman();
	void playTurn();
	pair<vector<int>, vector<int>> firstRollMove(const vector<int> currentDiceValues);
	pair<vector<int>, vector<int>> secondRollMove(const vector<int> rolledDice, const vector<int> keptDice);
};