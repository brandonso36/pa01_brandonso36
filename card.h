// card.h
// Author: Brandon So
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

using namespace std;

class Card {
public:
    // Constructor
    Card(char s = 'c', string v = "a");

    // Accessors
    char getSuit() const;
    string getValue() const;

    // Overloaded operators for BST/Set logic
    // Must follow: clubs < diamonds < spades < hearts
    // Then: ace < 2 < 3 ... < 10 < jack < queen < king
    bool operator<(const Card& other) const;
    bool operator>(const Card& other) const;
    bool operator==(const Card& other) const;

private:
    char suit;
    string value;

    // Helper functions to convert suit/value to rank for easier comparison
    int suitToRank() const;
    int valueToRank() const;
};

ostream& operator<<(std::ostream& os, const Card& c);

#endif
