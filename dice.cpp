#include "dice.hpp"

//Dice Constructor
Dice::Dice(int n) : nDice(n)
{
    diceValues = new int[nDice]; //Dynamically allocate array of dice
    srand(time(NULL));//randomizer for dice values
}

Dice::~Dice() { delete[] diceValues; }//Dice Destructor

//Rolling the dice
const int* 
Dice::roll() 
{
    for (int itr = 0; itr < nDice; itr++) { //Generate random value 1...6 for each die
        int randomNumber = (rand() % 6) + 1;
        diceValues[itr] = randomNumber;
        //arrayIn[itr] = diceValues[itr];
    }
    return diceValues;
}

const int*
CantStopDice::roll()
{
    Dice::roll();
    cout << "Dice Values: ";
    for (int k = 0; k < 4; k++) {
        cout << diceValues[k] << " ";
    }
    cout << endl;

    int pair1, pair2;
    cout << "Enter the numbers of the two dice (1-4) for the first pair: ";
    cin >> pair1 >> pair2;

    while (pair1 < 1 || pair1 > 4 || pair2 < 1 || pair2 > 4 || pair1 == pair2) {
        cout << "Invalid input. Enter the numbers of two different dice (1-4): ";
        cin >> pair1 >> pair2;
    }

    pairValues[0] = diceValues[pair1 - 1] + diceValues[pair2 -1];

    int total = 0;
    for (int k = 0; k < 4; k++ ) {
        if (k != pair1 - 1 && k != pair2 - 1) {
            total += diceValues[k];
        }
    }
    pairValues[1] = total;

    cout << pairValues[0] << " " << pairValues[1] << endl;

    return diceValues;
}

const int*
FakeDice::roll()
{
    if (fakeDiceArray.empty()) {

        ifstream fakeDiceFile("fake_dice.txt", ios::in);

        int number;
        
        if (!fakeDiceFile.is_open()) {
            fatal("Could not open file");
        }

        while (!fakeDiceFile.eof()) {
            fakeDiceFile >> number;
            fakeDiceArray.push_back(number);
        }
    }

    cout << "Dice Values: ";
    for (int k = 0; k < 4; k++) {
        diceValues[k] = fakeDiceArray.front();
        fakeDiceArray.erase(fakeDiceArray.begin());
        cout << diceValues[k] << " ";
        if (diceValues[k] > 6 || diceValues[k] <= 0) {
            cout << "1-6 Sided die only!";
            break;
        } 
    }
    cout << endl;

    int pair1, pair2;
    cout << "Enter the numbers of the two dice (1-4) for the first pair: ";
    cin >> pair1 >> pair2;

    pairValues[0] = diceValues[pair1 - 1] + diceValues[pair2 -1];

    int total = 0;
    for (int k = 0; k < 4; k++ ) {
        if (k != pair1 - 1 && k != pair2 - 1) {
            total += diceValues[k];
        }
    }
    pairValues[1] = total;

    cout << pairValues[0] << " " << pairValues[1] << endl;

    return diceValues;
}

//Print dice to either terminal or specified output
ostream& 
Dice::print(ostream& os) 
{
    for (int itr = 0; itr < nDice; itr++) { //Print the value of each dice
        os << diceValues[itr] << " ";
    }
    return os;
}