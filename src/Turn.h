#pragma once
#include "Player.h"

class Turn {
public:
	Turn(Player& firstPlayer, Player& secondPlayer);  
    void startTurns();  
	bool isRoundOver() const;  

private:
    Player& firstTurnPlayer;   
    Player& secondTurnPlayer;  
    bool roundOver;            
};
