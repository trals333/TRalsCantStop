#ifndef GAME_HPP
#define GAME_HPP

#include "dice.hpp"
#include "enums.hpp"
#include "board.hpp"
#include "clist.cpp"

class Game {
private:
    //CantStopDice myDice; //Select the dice you would like to use
    FakeDice myDice;
    Player player1; //player2, player3, player4; //Add other players as neccessary
    Board board;
public:
    Game();
    ~Game() = default;
    Player getNewPlayer();
    void oneTurn(CList CList);
    ostream& print(ostream& os);
};

inline ostream& operator <<(ostream& os, Game& game) {
    return game.print(os);
}


#endif //GAME_HPP