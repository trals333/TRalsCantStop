#include "player.hpp"


//Player Constructor
Player::Player(string name, ECcolor color) : playerName(name), playerColor(color), score(0)
{
    for (int itr = 0; itr < 3; itr++) {
        scoreboard[itr] = 0;
    }
}

//Player Destructor
Player::~Player() {}

//Return color player selected
ECcolor
Player::getColor() { return playerColor; }

//Players current score
int
Player::getScore()
{
    return score;
}

//Scoreboard of the current game
bool
Player::wonColumn(int colNum)
{
    if (score < 3) {
        scoreboard[score++] = colNum; // store colnum in scoreboard
        return score == 3; //Return true if this wins game for the player
    }
    return false;
}

bool
Player::isFirstTurn()
{
    return firstTurn;
}

void
Player::changeFirstTurn(bool value)
{
    if (!value) {
        firstTurn = false;
    }
    else {
        firstTurn = true;
    }
}

bool
Player::checkThreeTowers() 
{
    return hasThreeTowers;
}

void
Player::changeThreeTowers(bool value)
{
    if (!value) {
        hasThreeTowers = false;
    }
    else {
        hasThreeTowers = true;
    }
}

ostream& 
Player::print(ostream& os) 
{
    return os << "Player " << playerName << "\tColor: " << ECcolorArr[(int)playerColor] << " \tScore: " << score; 
}