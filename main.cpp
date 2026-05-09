// This file should implement the game using a custom implementation of a BST (based on your earlier BST implementation)
#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"
//Do not include set in this file

using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  CardBST aliceHand;
  CardBST bobHand;
  string suitStr, value;
  
  // Read Alice's file
  while (cardFile1 >> suitStr >> value){
    aliceHand.insert(Card(suitStr[0], value));
  }
  cardFile1.close();

  // Read Bob's file
  while (cardFile2 >> suitStr >> value){
    bobHand.insert(Card(suitStr[0], value));
  }
  cardFile2.close();
  
  bool gameContinuing = true;
  while (gameContinuing) {
    gameContinuing = false;
    
    // Alice's turn: Search Bob's hand using Forward Iterator
    for (auto it = aliceHand.begin(); it != aliceHand.end(); ++it) {
      if (bobHand.contains(*it)) {
        cout << "Alice picked matching card " << (*it).getSuit() << " " << (*it).getValue() << endl;
        Card match = *it;
        aliceHand.remove(match);
        bobHand.remove(match);
        gameContinuing = true;
        break; // Restart turn after removal to avoid iterator invalidation
      }
    }

    if (!gameContinuing) break; // If Alice found nothing, the game might be over
    gameContinuing = false;

    // Bob's turn: Search Alice's hand using Reverse Iterator
    for (auto it = bobHand.rbegin(); it != bobHand.rend(); --it) {
      if (aliceHand.contains(*it)) {
        cout << "Bob picked matching card " << (*it).getSuit() << " " << (*it).getValue() << endl;
        Card match = *it;
        aliceHand.remove(match);
        bobHand.remove(match);
        gameContinuing = true;
        break; // Restart turn
      }
    }
  }

  cout << endl << "Alice's cards:" << endl;
  aliceHand.printInOrder();

  cout << endl << "Bob's cards:" << endl;
  bobHand.printInOrder();
  
  return 0;
}