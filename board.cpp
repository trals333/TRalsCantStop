#include "board.hpp"

Board::Board() {
  backBone[0] = nullptr;
  backBone[1] = nullptr;
  for (int itr = 2; itr < 13; itr++) {
    backBone[itr] = new Column(itr);
  }
}

Board::~Board()
{
    for (int itr = 0; itr < 13; itr++) {
            delete backBone[itr];
        }
}

void Board::startTurn(Player *player) { currentPlayer = player; }

bool Board::placeTower(int column) {
  // ECcolor playerColor = currentPlayer->getColor();
  EState currentState = backBone[column]->getState();
  if (currentState == EState::PENDING || currentState == EState::CAPTURED ||
      counter[(int)currentPlayer->getColor()] >= 3) {
    return false;
  } else {
    if (colTowers[counter[(int)currentPlayer->getColor()]]
                 [(int)currentPlayer->getColor()] == 0) {
      colTowers[counter[(int)currentPlayer->getColor()]]
               [(int)currentPlayer->getColor()] = column;
      backBone[column]->startTower(currentPlayer);
      counter[(int)currentPlayer->getColor()]++;
    }
  }
  return true;
}

void Board::move(int column) {
  ECcolor playerColor = currentPlayer->getColor();
  backBone[column]->move(playerColor);
}

void Board::stop() {
  for (int k = 0; k < 3; k++) {
    if (backBone[colTowers[k][(int)currentPlayer->getColor()]] == 0) {
      continue;
    } else {
      backBone[colTowers[k][(int)currentPlayer->getColor()]]->stop(
          currentPlayer);
    }
  }
}

void Board::bust() {
  // counter = 0;
  // counter[(int)currentPlayer->getColor()] = 0;
  for (int k = 0; k < 3; k++) {
    if (backBone[colTowers[k][(int)currentPlayer->getColor()]] == 0) {
      continue;
    } else {
      backBone[colTowers[k][(int)currentPlayer->getColor()]]->bust(
          currentPlayer);
      colTowers[k][(int)currentPlayer->getColor()] = 0;
    }
  }
  counter[(int)currentPlayer->getColor()] = 0;
}

ostream &Board::print(ostream &os) {
  for (int itr = 2; itr < 13; itr++) {
    backBone[itr]->print(os);
    os << endl;
  }
  return os;
}