#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "tools.hpp"
#include "enums.hpp"

class Player {
private:
    string playerName;
    ECcolor playerColor;
    int score = 0;
    int scoreboard[3];
    bool firstTurn = true;
    bool hasThreeTowers = false;
public:
    Player(string name, ECcolor color);
    ~Player();
    int wonColumns = 0;
    vector<int> threePieces;
    ECcolor getColor();
    int getScore();
    bool wonColumn(int colNum);
    bool isFirstTurn();
    void changeFirstTurn(bool value);
    bool checkThreeTowers();
    void changeThreeTowers(bool value);
    ostream& print(ostream& os);
};

//Inline function to overide << operator
inline ostream& operator <<( ostream& os, Player& player) {
    player.print(os);
    return os;
}


#endif //PLAYER_HPP