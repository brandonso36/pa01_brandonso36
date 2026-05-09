// card.cpp
// Author: Brandon So
// Implementation of the classes defined in card.h

#include "card.h"

Card::Card(char s, string v) : suit(s), value(v) {}

char Card::getSuit() const { return suit; }
string Card::getValue() const { return value; }

int Card::suitToRank() const {
    if (suit == 'c') return 1;
    if (suit == 'd') return 2;
    if (suit == 's') return 3;
    if (suit == 'h') return 4;
    return 0;
}

int Card::valueToRank() const {
    if (value == "a") return 1;
    if (value == "j") return 11;
    if (value == "q") return 12;
    if (value == "k") return 13;
    // For values "2" through "10", convert string to int
    return stoi(value);
}

bool Card::operator<(const Card& other) const {
    if (suitToRank() != other.suitToRank()) {
        return this -> suitToRank() < other.suitToRank();
    }
    return this -> valueToRank() < other.valueToRank();
}

bool Card::operator>(const Card& other) const {
    return other < *this;
}

bool Card::operator==(const Card& other) const {
    return (this -> suit == other.suit && this -> value == other.value);
}

ostream& operator<<(ostream& os, const Card& c) {
    os << c.getSuit() << " " << c.getValue();
    return os;
}