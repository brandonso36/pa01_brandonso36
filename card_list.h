// card_list.h
// Author: Brandon So
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include "card.h"

class CardBST {
private:
    struct Node {
        Card data;
        Node *left, *right, *parent;
        Node(Card c) : data(c), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;
    void clear(Node* n);
    void printInOrder(Node* n) const;
    Node* find(Node* n, const Card& c) const;

public:
    CardBST() : root(nullptr) {}
    ~CardBST();

    void insert(Card c);
    void remove(Card c);
    bool contains(const Card& c) const;
    void printInOrder() const;

    // Iterator Class
    class Iterator {
    public:
        Iterator(Node* n = nullptr) : curr(n) {}
        Card& operator*() const { 
            return curr -> data; 
        }

        Card* operator->() const { 
            return &(curr -> data); 
        }
        
        bool operator==(const Iterator& other) const { return curr == other.curr; }
        bool operator!=(const Iterator& other) const { return curr != other.curr; }

        Iterator& operator++(); 
        Iterator& operator--(); 
    private:
        Node* curr;
    };

    Iterator begin() const;
    Iterator end() const { return Iterator(nullptr); }
    Iterator rbegin() const;
    Iterator rend() const { return Iterator(nullptr); }
};


#endif
