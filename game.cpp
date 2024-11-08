#include "game.hpp"

Game::Game()
    : myDice(), player1(getNewPlayer()),
      // player2(getNewPlayer()),
      // player3(getNewPlayer()),
      // player4(getNewPlayer()),
      board() {
  CList playerList;
  playerList.addCell(player1);
  // playerList.addCell(player2);
  // playerList.addCell(player3);
  // playerList.addCell(player4);
  playerList.init();
  oneTurn(playerList);
}

Player Game::getNewPlayer() {
  string name;
  ECcolor color;
  char colorInput;
  char upColorInput;
  int playerLoop = 1;
  while (playerLoop) {

    cout << "Please enter the name of the player: ";
    cin >> name;

    cout << "Enter player color (w)hite, (o)range, (y)ellow, (g)reen, or "
            "(b)lue: ";
    cin >> colorInput;
    upColorInput = toupper(colorInput);

    if (upColorInput == 'W') {
      color = ECcolor::WHITE;
      playerLoop = 0;
    } else if (upColorInput == 'O') {
      color = ECcolor::ORANGE;
      playerLoop = 0;
    } else if (upColorInput == 'Y') {
      color = ECcolor::YELLOW;
      playerLoop = 0;
    } else if (upColorInput == 'G') {
      color = ECcolor::GREEN;
      playerLoop = 0;
    } else if (upColorInput == 'B') {
      color = ECcolor::BLUE;
      playerLoop = 0;
    } else {
      cout << "Invalid color. Please enter a valid color.\n";
    }
  }

  return Player(name, color);
}

void Game::oneTurn(CList CList) {
  int action, firstPair, secondPair;
  int loop = 1;
  while (loop) {
    CList.isCurrent()->print(cout);
    cout << endl;
    cout << "Would you like to (1)roll, (2)stop, (3)resign? ";
    cin >> action;
    switch (action) {
    case 1:
      myDice.roll();
      firstPair = myDice.pairValues[0];
      secondPair = myDice.pairValues[1];

      if (CList.isCurrent()->isFirstTurn()) {
        board.startTurn(CList.isCurrent());
        board.placeTower(firstPair);
        board.placeTower(secondPair);
        CList.isCurrent()->threePieces.push_back(firstPair);
        CList.isCurrent()->threePieces.push_back(secondPair);
        board.print(cout);
        CList.isCurrent()->changeFirstTurn(false);
      } else {

        for (size_t i = 0; i < CList.isCurrent()->threePieces.size(); ++i) {
          if (CList.isCurrent()->threePieces[i] == firstPair) {
            board.move(firstPair);
          } else if (CList.isCurrent()->threePieces[i] == secondPair) {
            board.move(secondPair);
          } else if (!CList.isCurrent()->checkThreeTowers() &&
                     CList.isCurrent()->threePieces[i] != firstPair &&
                     CList.isCurrent()->threePieces[i] != secondPair) {
            board.placeTower(firstPair);
            CList.isCurrent()->threePieces.push_back(firstPair);
            CList.isCurrent()->changeThreeTowers(true);
            break;
          } else if (CList.isCurrent()->threePieces[0] != firstPair &&
                     CList.isCurrent()->threePieces[0] != secondPair &&
                     CList.isCurrent()->threePieces[1] != firstPair &&
                     CList.isCurrent()->threePieces[1] != secondPair &&
                     CList.isCurrent()->threePieces[2] != firstPair &&
                     CList.isCurrent()->threePieces[2] != secondPair) {
            cout << "You went bust" << endl;
            board.bust();
            board.stop();
            CList.isCurrent()->changeFirstTurn(true);
            CList.isCurrent()->changeThreeTowers(false);
            CList.isCurrent()->threePieces.clear();
            CList.next();
            if (!CList.isCurrent()->isFirstTurn()) {
              board.startTurn(CList.isCurrent());
            }
            break;
          }
        }
        board.print(cout);

        if (CList.isCurrent()->getScore() == 3) {
          cout << "Congratulations! You won the game" << endl;
          CList.isCurrent()->print(cout);
          cout << "\nGame Over" << endl;
          loop = 0;
        }
      }
      break;

    case 2:
      CList.next();
      board.stop();
      if (!CList.isCurrent()->isFirstTurn()) {
        board.startTurn(CList.isCurrent());
      }
      break;
    case 3:
      loop = 0;
      break;
    default:
      cout << "Error: Incorrect option\n";
      break;
    }
  }
}

ostream &Game::print(ostream &os) {
  player1.print(os);
  os << endl;
  board.print(os);
  os << endl;
  return os;
}
