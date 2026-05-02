#ifndef BINARYTREE_H
#define BINARYTREE_H

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
	/* Mètodes auxiliars definiu aquí els que necessiteu */
};


#endif // BINARYTREE_H