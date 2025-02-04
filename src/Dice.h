#pragma once
#include <vector>
#include <cstdlib>
#include "Player.h"

class Dice
{
public:
    Dice();
    vector<int> rollDice(int numDice);
    int rollSingleDice();

private:
    // Vector to store the results of the dice rolls
    vector<int> diceResult;
};
