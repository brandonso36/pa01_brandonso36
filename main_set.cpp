// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

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
  set<Card> alice; // initializes a set for Alice and Bob as well as vars to get their data
  set<Card> bob;
  char suit;
  string value;

  // Read Alice's cards
  while (cardFile1 >> suit >> value){
    alice.insert(Card(suit, value));
  }
  cardFile1.close();

  // Read Bob's cards
  while (cardFile2 >> suit >> value){
    bob.insert(Card(suit, value));
  }
  cardFile2.close();

  bool cardsFound = true;
  while (cardsFound) { // runs until no duplicates are found
    cardsFound = false;

    // Alice's turn: Iterate forward (smallest to largest)
    for (auto it = alice.begin(); it != alice.end(); it++) { // iterate through every card in Alice's hand
      if (bob.count(*it)) { // Checks if the card is in Bob's hand
        cout << "Alice picked matching card " << *it << endl; 
        Card match = *it; // Creates a copy of the found card
        alice.erase(match); // removes the card from both hands
        bob.erase(match);
        cardsFound = true; // allows the loop to continue
        break; // Turn ends after one match
      }
    }

    if (!cardsFound) break; // Checks if there were not cards found

    cardsFound = false; // resets the boolean variable
    // Bob's turn: Iterate backward (largest to smallest)
    for (auto rit = bob.rbegin(); rit != bob.rend(); rit++) { // iterates through every element backwards
      if (alice.count(*rit)) { // checks if the card is in Alice's hand
        cout << "Bob picked matching card " << *rit << endl;
        Card match = *rit; // creates a copy of the found card
        alice.erase(match); // erases the card from both hands
        bob.erase(match);
        cardsFound = true; // coninutes the loop
        break; // Turn ends after one match
      }
    }
  }

  // Prints out the final hands
  cout << endl << "Alice's cards:" << endl;
  for (auto const& c : alice){
    cout << c << endl;
  }

  cout << endl << "Bob's cards:" << endl;
  for (auto const& c : bob){
    cout << c << endl;
  }

  
  return 0;
}
  /*

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
  
  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    
  }
  cardFile2.close();
  
  
  return 0;
}
*/