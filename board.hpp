#ifndef BOARD_HPP
#define BOARD_HPP

#include "player.hpp"
#include "column.hpp"
#include "enums.hpp"

class Board {
private:
    int counter[5] = {0,0,0,0,0};
    int colTowers[3][5] = {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };
    Column* backBone[13];
    Player* currentPlayer;
public:
    Board();
    ~Board();
    void startTurn(Player* player);
    bool placeTower(int column);
    void move(int column);
    void stop();
    void bust();
    ostream& print(ostream& os);
};

inline ostream& operator <<( ostream& os, Board& board) {
    return board.print(os);
}


#endif //BOARD_HPP