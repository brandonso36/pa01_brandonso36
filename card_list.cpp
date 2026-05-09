// card_list.cpp
// Author: Brandon So
// Implementation of the classes defined in card_list.h

#include "card_list.h"

// --- Memory Management ---
CardBST::~CardBST() { clear(root); }
void CardBST::clear(Node* n) {
    if (n) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

// --- Basic BST Ops ---
void CardBST::insert(Card c) {
    Node* newNode = new Node(c);
    if (!root) { 
        root = newNode; return;
    }
    
    Node* curr = root;
    Node* parent = nullptr;
    while (curr) {
        parent = curr;
        if (c < curr -> data) curr = curr -> left;
        else if (curr -> data < c) curr = curr -> right;
        else { 
            delete newNode; 
            return; 
        }
    }
    
    newNode->parent = parent;
    if (c < parent -> data){
        parent -> left = newNode;
    }

    else {
        parent -> right = newNode;
    }
}

// --- Iterator Logic ---
CardBST::Iterator& CardBST::Iterator::operator++() {
    if (curr -> right) {
        curr = curr -> right;
        while (curr -> left){
            curr = curr -> left;
        }
    } 
    
    else {
        Node* p = curr -> parent;
        while (p && curr == p -> right) {
            curr = p;
            p = p -> parent;
        }
        curr = p;
    }
    return *this;
}

CardBST::Iterator& CardBST::Iterator::operator--() {
    if (curr == nullptr) {
        return *this;
    }
    if (curr -> left) {
        curr = curr -> left;
        while (curr -> right) curr = curr -> right;
    } else {
        Node* p = curr -> parent;
        while (p && curr == p -> left) {
            curr = p;
            p = p -> parent;
        }
        curr = p;
    }
    return *this;
}

// --- Helper for begin/rbegin ---
CardBST::Iterator CardBST::begin() const {
    Node* n = root;
    while (n && n -> left) n = n -> left;
    return Iterator(n); 
}

CardBST::Iterator CardBST::rbegin() const {
    Node* n = root;
    while (n && n -> right) n = n -> right;
    return Iterator(n);
}

// Implement contains, printInOrder, and remove similarly...
bool CardBST::contains(const Card& c) const {
    Node* curr = root;
    while (curr) {
        if (c < curr -> data) curr = curr -> left;
        else if (curr -> data < c) curr = curr -> right;
        else return true; // Found it
    }
    return false;
}

void CardBST::printInOrder() const {
    printInOrder(root);
}

void CardBST::printInOrder(Node* n) const {
    if (n == nullptr){
        return;
    }

    printInOrder(n -> left);
    cout << n -> data << endl; // This uses your Card operator<<
    printInOrder(n -> right);
}

void CardBST::remove(Card c) {
    Node* curr = root;
    while (curr && !(curr -> data == c)) {
        if (c < curr -> data){
            curr = curr -> left;
        }

        else{
            curr = curr -> right;
        }
    }

    if (!curr){
        return; // Card not found
    }

    // Case 1 & 2: 0 or 1 child
    if (!curr -> left || !curr -> right) {
        Node* child = (curr -> left) ? curr -> left : curr -> right;

        if (!curr -> parent) {
            root = child;
        } 

        else if (curr == curr -> parent -> left) {
            curr -> parent -> left = child;
        } 
        
        else {
            curr -> parent -> right = child;
        }

        if (child){
            child -> parent = curr -> parent;
        }

        delete curr;
    } 
    // Case 3: 2 children
    else {
        // Find successor (smallest in right subtree)
        Node* successor = curr -> right;
        while (successor -> left){
            successor = successor -> left;
        }
        
        Card successorData = successor -> data;
        remove(successorData); // Recursively delete successor
        curr -> data = successorData; // Replace curr's data with successor's
    }
}