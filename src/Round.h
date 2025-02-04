#pragma once
#include "Player.h"
class Round
{
public:
	Round(const vector<Player*>& players);
	void startRound();
	void incrementRound();
	static int getRoundNumber();
	static void setRoundNumber(int newRoundNumber);

private:
	static int roundNumber;
	vector<Player*> players;
};

