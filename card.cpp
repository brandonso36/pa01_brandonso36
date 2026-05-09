// card.cpp
// Author: Brandon So
// Implementation of the classes defined in card.h

#include "card.h"

Card::Card(char s, string v) : suit(s), value(v) {}

// returns the default values
char Card::getSuit() const { return suit; }
string Card::getValue() const { return value; }

int Card::suitToRank() const {
    // determines rank of suit in increasing order
    if (suit == 'c') return 1; 
    if (suit == 'd') return 2;
    if (suit == 's') return 3;
    if (suit == 'h') return 4;
    return 0;
}

int Card::valueToRank() const {
    // determines value of non-integer values
    if (value == "a") return 1;
    if (value == "j") return 11;
    if (value == "q") return 12;
    if (value == "k") return 13;
    
    return stoi(value);
}

bool Card::operator<(const Card& other) const {
    if (suitToRank() != other.suitToRank()) { // checks if the ranks are not the same
        return this -> suitToRank() < other.suitToRank(); // returns if the rank is greater
    }
    return this -> valueToRank() < other.valueToRank(); // otherwise returns if the value is greater
}

bool Card::operator>(const Card& other) const {
    return other < *this; // uses the other in place operator "<"
}

bool Card::operator==(const Card& other) const {
    return (this -> suit == other.suit && this -> value == other.value); // compares both values together
}

ostream& operator<<(ostream& os, const Card& c) {
    os << c.getSuit() << " " << c.getValue(); // organizes the input values
    return os;
}