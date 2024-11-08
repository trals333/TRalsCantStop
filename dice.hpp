#ifndef DICE_HPP
#define DICE_HPP
#include "tools.hpp"


class Dice {
protected:
    int nDice;
    int* diceValues;
    vector<int> fakeDiceArray;
public:
    Dice(int n = 4);
    virtual ~Dice();
    virtual const int* roll();
    ostream& print(ostream&);
};

class CantStopDice : public Dice {
public:
    int pairValues[2];
    CantStopDice() : Dice() {}

    const int* roll() override;
};

class FakeDice : public Dice {
public: 
    int pairValues[2];
    FakeDice(): Dice() {}

    const int* roll() override;
};

//Inline function to overide << operator
inline ostream& operator <<( ostream& os, Dice& dice) {
    dice.print(os);
    return os;
}

#endif //DICE_HPP