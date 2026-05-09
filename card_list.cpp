// card_list.cpp
// Author: Brandon So
// Implementation of the classes defined in card_list.h

#include "card_list.h"

CardBST::~CardBST() { clear(root); }
void CardBST::clear(Node* n) {
    if (n) { 
        clear(n->left); // recursively clears left subtree
        clear(n->right); // recursively clears right subtree
        delete n; // deletes the current node
    }
}

void CardBST::insert(Card c) {
    Node* newNode = new Node(c); // allocates a new node for the card
    if (!root) { 
        root = newNode; return; // sets root if tree is empty
    }
    
    Node* curr = root;
    Node* parent = nullptr;
    while (curr) {
        parent = curr; // keeps track of the parent for the new node
        if (c < curr -> data) curr = curr -> left; // traverses left if smaller
        else if (curr -> data < c) curr = curr -> right; // traverses right if larger
        else { 
            delete newNode; 
            return; // discards duplicate cards
        }
    }
    
    newNode->parent = parent; // links the new node to its parent
    if (c < parent -> data){
        parent -> left = newNode; // inserts as left child
    }

    else {
        parent -> right = newNode; // inserts as right child
    }
}

CardBST::Iterator& CardBST::Iterator::operator++() {
    if (curr -> right) {
        curr = curr -> right;
        while (curr -> left){
            curr = curr -> left; // finds the smallest node in the right subtree
        }
    } 
    
    else {
        Node* p = curr -> parent;
        while (p && curr == p -> right) {
            curr = p; // moves up until we are no longer a right child
            p = p -> parent;
        }
        curr = p;
    }
    return *this;
}

CardBST::Iterator& CardBST::Iterator::operator--() {
    if (curr == nullptr) {
        return *this; // handles end() case
    }
    if (curr -> left) {
        curr = curr -> left;
        while (curr -> right) curr = curr -> right; // finds the largest node in the left subtree
    } else {
        Node* p = curr -> parent;
        while (p && curr == p -> left) {
            curr = p; // moves up until we are no longer a left child
            p = p -> parent;
        }
        curr = p;
    }
    return *this;
}

CardBST::Iterator CardBST::begin() const {
    Node* n = root;
    while (n && n -> left) n = n -> left; // finds the node with the minimum value
    return Iterator(n); 
}

CardBST::Iterator CardBST::rbegin() const {
    Node* n = root;
    while (n && n -> right) n = n -> right; // finds the node with the maximum value
    return Iterator(n);
}

bool CardBST::contains(const Card& c) const {
    Node* curr = root;
    while (curr) {
        if (c < curr -> data) curr = curr -> left; // searches left subtree
        else if (curr -> data < c) curr = curr -> right; // searches right subtree
        else return true; // match found
    }
    return false;
}

void CardBST::printInOrder() const {
    printInOrder(root); // calls the recursive helper function
}

void CardBST::printInOrder(Node* n) const {
    if (n == nullptr){
        return;
    }

    printInOrder(n -> left); // prints left subtree first
    cout << n -> data << endl; // prints the current card
    printInOrder(n -> right); // prints right subtree last
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
        return; // exits if card does not exist in tree
    }

    if (!curr -> left || !curr -> right) {
        Node* child = (curr -> left) ? curr -> left : curr -> right; // identifies the single child if it exists

        if (!curr -> parent) {
            root = child; // updates root if removing the root node
        } 

        else if (curr == curr -> parent -> left) {
            curr -> parent -> left = child; // bypasses the node via the parent's left pointer
        } 
        
        else {
            curr -> parent -> right = child; // bypasses the node via the parent's right pointer
        }

        if (child){
            child -> parent = curr -> parent; // updates the child's parent pointer
        }

        delete curr;
    } 
    else {
        Node* successor = curr -> right;
        while (successor -> left){
            successor = successor -> left; // finds the smallest node in the right subtree
        }
        
        Card successorData = successor -> data;
        remove(successorData); // removes the successor node from the tree
        curr -> data = successorData; // copies the successor's data into the current node
    }
}