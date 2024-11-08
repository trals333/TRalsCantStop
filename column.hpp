#ifndef COLUMN_HPP
#define COLUMN_HPP

#include "tools.hpp"
#include "enums.hpp"
#include "player.hpp"

class Column {
private:
    static const int columnLengths[13];
    const int columnNumber;
    int columnContents[5];
    EState state;

public:
    Column(const int colNum);
    ~Column();
    EState getState();
    bool startTower(Player* player);
    bool move(ECcolor playerColor);
    void stop(Player* player);
    void bust(Player* player);
    ostream& print(ostream& os);
};

//Inline function to overide << operator
inline ostream& operator <<( ostream& os, Column& column) {
    column.print(os);
    return os;
}

#endif //COLUMN_HPP