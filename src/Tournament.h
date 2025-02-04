#pragma once
#include "stdafx.h"
#include "Player.h"
#include "Round.h"

class Tournament
{
public:
	Tournament();
	~Tournament();
	void startNewTournament();
	void laodTournament();

private:
	vector<Player*> players;
};

