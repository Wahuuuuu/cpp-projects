#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "Position.h"
#include <vector>
#include <cassert>
#include <stdexcept>

using namespace std;

template<class Key, class Value>
class BinaryTree {
public: 
	BinaryTree(); 
	BinaryTree(const BinaryTree<Key, Value>& orig); 
	virtual ~BinaryTree(); 

	bool isEmpty() const; 
	Position<Key, Value>* getRoot() const; 
	int size() const; 
	int height() const; 
	virtual Position<Key, Value>* insert(const Key& key, const Value& value); 
	bool contains(const Key& key) const; 
	const vector<Value>& getValues(const Key& key) const; 
	void printPreOrder(const Position<Key, Value> *node = nullptr) const; 
	void printPostOrder(const Position<Key, Value> *node = nullptr) const; 
	bool identicalTree(const BinaryTree<Key, Value>& other) const;
	
protected: 
	Position<Key, Value>* root;
	
private: 
    int _size; 
	Position<Key, Value>* findNodeOrParent(Key key) const;
	template <class Func> void inorder(const Position<Key, Value> *node, Func& action) const;  // Immutable traverse, which DO NOT allows to modify the tree
};


// Construcotrs and destructor
// -------------------------------

template<class Key, class Value>
BinaryTree<Key, Value>::BinaryTree() {
	this->_size = 0;
	this->root = nullptr;
}

template<class Key, class Value>
BinaryTree<Key, Value>::BinaryTree(const BinaryTree<Key, Value>& orig) {
	this->_size = orig.size();
	this->root = orig.getRoot();
}

template<class Key, class Value>
BinaryTree<Key, Value>::~BinaryTree() {

}


// Functions
// -------------

template<class Key, class Value>
bool BinaryTree<Key, Value>::isEmpty() const {
	return (this->size() == 0);
}


template<class Key, class Value>
Position<Key, Value>* BinaryTree<Key, Value>::getRoot() const {
	return this->root;
}


template<class Key, class Value>
int BinaryTree<Key, Value>::size() const 
{
	int count = 0;
	auto counter = [&count](const Position<Key, Value> /*position*/) -> void {
		count++;
	};

	this->inorder(this->root, counter);

	assert(count == this->size);
	return count;
}


template<class Key, class Value>
int BinaryTree<Key, Value>::height() const {
	return this->root->height();
}


/**
 * @brief Inserts a key-value pair into the tree.
 *
 * If the key already exists, the value is added to the existing position.
 * Otherwise, a new position is created.
 *
 * @param key The key to insert.
 * @param value The value associated with the key.
 * @return A pointer to the position where the value was inserted.
 */
template<class Key, class Value>
Position<Key, Value>* BinaryTree<Key, Value>::insert(const Key& key, const Value& value) {
	if (this->isEmpty()) {
		this->root = new Position<Key, Value>(key);
		this->root->addValue(value);
	}

	Position<Key, Value>* foundPos = this->nodeOrParent(key);
	Key foundKey = nodeParent->getKey();
	if (foundKey == key) {
		foundPos->addValue(value);  // the key already exists, add value
		return foundPos;
	}
	else {
		Position<Key, Value> newPos = new Position<Key, Value>(key);
		if (key < foundKey) {
			foundPos->setLeft(newPos);
		} else {
			foundPos->setLeft(newPos);
		}
		newPos->addValues(value);
		return newPos;
	}



}




// Immutable traverse, which DO NOT allows to modify the tree
template<class Key, class Value>
template<class Func>
void BinaryTree<Key, Value>::inorder(const Position<Key, Value> *node, Func &action) const {
	if (node == nullptr) return;

	// visit this->leftChild and do actions
	inorder(node->getLeft(), action);

	// do action to the current node
	action(node);

	// visit this->rightChild and do actions
	inorder(node->getRight(), action);
}


/**
 * @brief if key exists, returns a pointer of the position; if not, returns the pointer of the last non-empty position
 *
 * This function searches key in tree:
 *     - If key already exists, returns a pointer of the node which contains the key
 *     - In key do not exists, returns a pointer of the last non-empty node on the path 
 *       (if a new node key will added to the tree, that non-empty node will be it's parent node)
 * 
 * @param key The key to search
 * @return a pointer to the node with key, or tha last non-empty node
 * @throw out_of_range If the tree is empty
 */
template<class Key, class Value>
Position<Key, Value>* BinaryTree<Key, Value>::findNodeOrParent(Key key) const { 
	if (this->isEmpty()) throw out_of_range("Not able to find Node Or Parent: the tree is empty!");

	Position<Key, Value>* currPos = this->root;
	Position<Key, Value>* parent = nullptr;
	while (currPos != nullptr) {
		parent = currPos;
		Key currKey = currPos->getKey();
		/*
		 * Idea:
		 * 	- if currPos == nullptr, the key don't exists, should return parent of currPos
		 *  - if currPos != nullptr, the key may exists
		 *  	- if key < currKey, key may in the left subtree
		 *      - if key > currKey, key may in the right subtree
		 *      - if key == currKey, key is found!
		 */
        if (key < currKey) {
            currPos = currPos->getLeft();
        } else if (key > currKey) {
            currPos = currPos->getRight();
        } else {
			return currPos;  // the key exists, currPos is the pointer
		}
    }

	return Parent;           // the key don't exists, Parent is the last non-empty node on the path
}


#endif // BINARYTREE_H