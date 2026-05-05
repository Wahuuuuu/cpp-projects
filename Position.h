#ifndef POSITION_H
#define POSITION_H

#include <vector>
using namespace std;

template <class Key, class Value>
class Position 
{
public: 
	Position(const Key key); 
	Position(const Position<Key, Value>& orig); 
	virtual ~Position(); 

	/* Modificadors */ 
	void setParent(Position<Key, Value> *parent_);
	void setLeft(Position<Key, Value> *left_);
	void setRight(Position<Key, Value> *right_);

	
	/* Consultors */ 
	const Key& getKey() const; 
	const vector<Value>& getValues() const; 
	const Position<Key, Value>* getParent() const;
	const Position<Key, Value>* getLeft() const;
	const Position<Key, Value>* getRight() const;
	
	/* Operacions */ 
	bool isRoot() const;
	bool isLeaf() const; 
	int depth() const;
	int height() const;
	void addValue(const Value& value);
	bool operator==(const Position<Key, Value>& other) const;

private: 
    Key key; 
	vector<Value> values; 
	Position<Key, Value> *parent;
	Position<Key, Value> *leftChild;
	Position<Key, Value> *rightChild;
};



// Constructors i Destructor
// -----------------------------

template <class Key, class Value>
Position<Key, Value>::Position(const Key key) {
    this->key = key;
	this->values = vector<Value>();
	this->parent = nullptr;
	this->leftChild = nullptr;
	this->rightChild = nullptr;
}


template <class Key, class Value>
Position<Key, Value>::Position(const Position<Key, Value>& orig) {
    this->key = orig.getKey();
    this->values = orig.getValues();
	this->parent = nullptr;
	this->leftChild = nullptr;
	this->rightChild = nullptr;
}


template <class Key, class Value>
Position<Key, Value>::~Position() {}


// Modificadors
// ----------------

template <class Key, class Value>
void Position<Key, Value>::setParent(Position<Key, Value> *parent_) {
	this->parentNode = parent_;
}

template <class Key, class Value>
void Position<Key, Value>::setLeft(Position<Key, Value> *left_) {
	this->leftChild = left_;
}

template <class Key, class Value>
void Position<Key, Value>::setRight(Position<Key, Value> *right_) {
	this->rightChild = right_;
}


// Consultors
// --------------

template <class Key, class Value>
const Key& Position<Key, Value>::getKey() const {
	return this->key;
}

template <class Key, class Value>
const vector<Value>& Position<Key, Value>::getValues() const {
	return this->values;
}

template <class Key, class Value>
const Position<Key, Value>* Position<Key, Value>::getParent() const {
	return this->parent;
}

template <class Key, class Value>
const Position<Key, Value>* Position<Key, Value>::getLeft() const {
	return this->leftChild;
}

template <class Key, class Value>
const Position<Key, Value>* Position<Key, Value>::getRight() const {
	return this->rightChild;
}


// Operacions:
// ---------------

template <class Key, class Value>
bool Position<Key, Value>::isRoot() const {
	return (this.parent == nullptr);
}

template <class Key, class Value>
bool Position<Key, Value>::isLeaf() const {
	return (this.leftChild == nullptr || this.rightChild == nullptr);
}

template <class Key, class Value>
int Position<Key, Value>::depth() const {
	if (this->isRoot()) return 0;

	return (this->parent.depth() + 1);
}

template <class Key, class Value>
int Position<Key, Value>::height() const {
	int leftHeight, rightHeight = -1;

	if (this->leftChild != nullptr) {
		leftHeight = this->leftChild->height();
	}
	if (this->rightChild != nullptr) {
		rightHeight = this->rightChild->height();
	}

	return max(leftHeight, rightHeight) + 1;
}

template <class Key, class Value>
void Position<Key, Value>::addValue(const Value& value) {
	this->values.push_back(value);
}

template <class Key, class Value>
bool Position<Key, Value>::operator==(const Position<Key, Value>& other) const {
	return ( (this->key == other.getKey()) && (this->values == other.getValues()) );
}


#endif // POSITION_H