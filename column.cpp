#include "column.hpp"

// Constructor to initiaize the coliumn, set it's column number and the length
// of the column
Column::Column(const int colNum)
    : columnNumber(colNum), state(EState::AVAILABLE) {
  for (int itr = 0; itr < 5; itr++) {
    columnContents[itr] = 0;
  }
}

// Destructor
Column::~Column() {}

// initialize the columnLength array here
const int Column::columnLengths[13] = {0,  0,  3, 5, 7, 9, 11,
                                       13, 11, 9, 7, 5, 3};

// Return the state of the column
EState Column::getState() { return state; }

// Place a marker on the column
bool Column::startTower(Player *player) {
  int colorIndex = (int)player->getColor();

  if (state != EState::AVAILABLE) {
    return false;
  }

  columnContents[colorIndex] = 1;
  return true;
}

// Move the column one space forward
bool Column::move(ECcolor playerColor) {
  int colorIndex = (int)playerColor;

  if (columnContents[colorIndex] <= 0 ||
      columnContents[colorIndex] >= columnLengths[columnNumber]) {
    return false;
  }

  columnContents[colorIndex]++;

  if (columnContents[colorIndex] == columnLengths[columnNumber]) {
    state = EState::PENDING;
  }
  return true;
}

// End the players turn
void Column::stop(Player *player) {
  int colorIndex = (int)player->getColor();
  EState columnState = getState();

  if (columnContents[colorIndex] > 0 &&
      columnContents[colorIndex] <= columnLengths[columnNumber])
    if (columnContents[colorIndex] == columnLengths[columnNumber] && columnState == EState::PENDING) {
      state = EState::CAPTURED;
      player->wonColumn(columnNumber);

      for (int itr = 1; itr < 5; itr++) {
        if (itr != colorIndex) {
          columnContents[itr] = 0;
        }
      }
    }
}

void Column::bust(Player *player) {
  int colorIndex = (int)player->getColor();
  columnContents[colorIndex] = 0;
}

// Print the column and its status in the game
ostream &Column::print(ostream &os) {
  os << columnNumber << " " << setw(10) << left << EStateStrings[(int)state];

  for (int itr = 1; itr <= columnLengths[columnNumber]; itr++) {
    os << "  ";
    string square = "-----";

    if (columnContents[0] == itr) {
      square[0] = 'T';
    }

    for (int player = 1; player < 5; player++) {
      if (columnContents[player] == itr) {
        square[player] = "OYGB"[player - 1];
      }
    }

    os << square;
  }
  return os;
}