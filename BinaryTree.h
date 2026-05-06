#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "Position.h"
#include <iostream>
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
	Position<Key, Value>* search(const Key& key) const;

protected: 
	Position<Key, Value>* root;
	
private: 
    int _size; 
	void addNode(Position<Key, Value>* parent, Position<Key, Value>* newNode);
	Position<Key, Value>* cloneSubtree(const Position<Key, Value>* origNode, Position<Key, Value>* parent);
	Position<Key, Value>* findNodeOrParent(const Key& key) const;
	template <class Func> void preOrder(const Position<Key, Value> *node, Func& action) const;  // Immutable traverse, which DO NOT allows to modify the tree
};


// Construcotrs and destructor
// -------------------------------

/**
 * @brief Creates an empty tree.
 */
template<class Key, class Value>
BinaryTree<Key, Value>::BinaryTree() {
	this->_size = 0;
	this->root = nullptr;
}

/**
 * @brief Creates a copy of the orig tree.
 *
 * @param orig 
 */
template<class Key, class Value>
BinaryTree<Key, Value>::BinaryTree(const BinaryTree<Key, Value>& orig) {
	this->root = cloneSubtree(orig.getRoot(), nullptr);
	this->_size = orig.size();

	assert(this->size() == orig.size());
}

/**
 * @brief Deep copy the subtree with root origNode, and returns a pointer of the root of the new subtree.
 *
 *
 * @param origNode Pointer of the root of the original tree
 * @param parent   Pointer of the parent of the new Node
 */
 template<class Key, class Value>
 Position<Key, Value>* BinaryTree<Key, Value>::cloneSubtree(const Position<Key, Value>* origNode, Position<Key, Value>* parent) 
 {
	if (origNode == nullptr) return nullptr;
	
	Position<Key, Value> newNode = new Position<Key, Value>(origNode->getKey());
	newNode->setParent(parent);

	newNode->setLeft(cloneSubtree(origNode->getLeft(), newNode));
	newNode->setRight(cloneSubtree(origNode->getRight(), newNode));

	return newNode;
 }


/**
 */
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

	this->preOrder(this->root, counter);

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

		this->size++;
		return this->root;
	}

	// This tree can't be empty now
	Position<Key, Value> *foundPos = this->findNodeOrParent(key);
	Key foundKey = foundPos->getKey();
	if (this->contains(key)) {    // the key already exists, add value
		foundPos->addValue(value);  
		return foundPos;
	}
	else {                        // the key is not in the tree yet, add new node
		Position<Key, Value> *newPos = new Position<Key, Value>(key);
		this->addNode(foundPos, newPos);
		newPos->addValues(value);

		return newPos;
	}
}

/**
 * @brief Returns true if this tree contains key, otherwise returns false.
 *
 * @param key The key to be searched.
 * @return true if this tree contains key, false otherwise.
 */
template<class Key, class Value>
bool BinaryTree<Key, Value>::contains(const Key& key) const {
	if (this->isEmpty()) return false;

	Position<Key, Value>* foundPos = this->findNodeOrParent(key);
	if (foundPos->getKey() == key) return true;
	else return false;
}

/**
 * @brief Returns a vector of values of the node "key". If the node is not in this tree, throws out_of_range exception
 *
 * @param key The key to be searched.
 * @return vector of values
 * @throw out_of_range If the node is not in this tree
 */
template<class Key, class Value>
const vector<Value>& BinaryTree<Key, Value>::getValues(const Key& key) const {
	if (this->isEmpty()) throw out_of_range("Not able to get value of the key " + key + ": the tree is empty!");

	if (this->contains(key)) return (this->findNodeOrParent(key)->getValues());
	else throw out_of_range("Not able to get value of the key " + key + ": the key is not in tree!");
}

/**
 * @brief Print the keys of the tree with root=node in preorder, separated with spaces
 *
 * If the tree is empty, prints nothing.
 * If there are no parameter, *node = nullptr.
 * Format: " k1 k2 k3 k4"
 *
 * @param *node, the node to begin
 */
template<class Key, class Value>
void BinaryTree<Key, Value>::printPreOrder(const Position<Key, Value> *node = nullptr) const {
	auto printNode = [](Position<Key, Value>* node) -> void {
		cout << " " + node->getKey();
	};
	
	this->preOrder(this->root, printNode);
}

/**
 * @brief Print the keys of the tree with root=node in postorder, separated with spaces
 *
 * If the tree is empty, prints nothing.
 * If there are no parameter, *node = nullptr.
 * Format: " k1 k2 k3 k4"
 *
 * @param *node, the node to begin
 */
template<class Key, class Value>
void BinaryTree<Key, Value>::printPostOrder(const Position<Key, Value> *node = nullptr) const {
	if (node == nullptr) return;

	printPreOrder(node->getLeft());
	printPreOrder(node->getRight());
	cout << " " + node->getKey();
}

/**
 * 
 */
template<class Key, class Value>
bool BinaryTree<Key, Value>::identicalTree(const BinaryTree<Key, Value>& other) const {
	// using operator ==
}


/**
 * 
 */
template<class Key, class Value>
bool BinaryTree<Key, Value>::search(const Key& key) const {
	if (this->isEmpty()) return nullptr;

	Position<Key, Value>* foundPos = this->findNodeOrParent(key);
	if (foundPos->getKey() == key) return foundPos;
	else return nullptr;
}

/**
 * @brief this function adds a new node to this tree
 *
 * This function do 3 actions:
 *     - setLeft/setRight of parent
 *     - setParent of newNode
 *     - increases the size of this tree
 *
 * @param parent The parent node
 * @param newNode The node to be add
 * @throw invalid_argument if parent==nullptr
 */
template<class Key, class Value>
void BinaryTree<Key, Value>::addNode(Position<Key, Value>* parent, Position<Key, Value>* newNode) {
	if (parent == nullptr) throw invalid_argument("Not able to add new node: the parent node is nullptr!");

	if (newNode->getKey() < parent->getKey()) {
		parent->setLeft(newNode);
	} else {
		parent->setRight(newNode);
	}
	newNode->setParent(parent);

	this->_size++;
}


// Immutable traverse, which DO NOT allows to modify the tree
template<class Key, class Value>
template<class Func>
void BinaryTree<Key, Value>::preOrder(const Position<Key, Value> *node, Func &action) const {
	if (node == nullptr) return;

	// do action to the current node
	action(node);

	// visit left subtree and do actions
	preOrder(node->getLeft(), action);

	// visit right subtree and do actions
	preOrder(node->getRight(), action);
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
 * @throw out_of_range If this tree is empty
 */
template<class Key, class Value>
Position<Key, Value>* BinaryTree<Key, Value>::findNodeOrParent(const Key& key) const { 
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

	return parent;           // the key don't exists, Parent is the last non-empty node on the path
}


#endif // BINARYTREE_H