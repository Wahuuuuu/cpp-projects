#ifndef POSITION_H
#define POSITION_H

#include <vector>
using namespace std;

template <class Key, class Value>
class Position 
{
public: 
	Position(const Key key); 
		// 给出一个 key，新建一个 position
	Position(const Position<Key, Value>& orig); 
		// 给出一个 position，新建一个它的拷贝 position
	virtual ~Position(); 

	/* Modificadors */ 
	// setParent
	// setLeft
	// setRight
	
	/* Consultors */ 
	const Key& getKey() const; 
	const vector<Value>& getValues() const; 
	// getKey
	// getValues
	// parent
	// left
	// right
	
	/* Operacions */ 
	bool isRoot() const;
	bool isLeaf() const; 
	int depth() const;  // 应用递归实现
	int height() const; // 没指定实现方法
	void addValue(const Value& value);  // 往 vector 中新增 value
	bool operator==(const Position<Key, Value>& other) const;

private: 
    Key key; 
	vector<Value> values; 
	// Afegiu-hi aquí els atributs que manquen
};



// Constructors i Destructor
// -----------------------------

template <class Key, class Value>
Position<Key, Value>::Position(const Key key) {
    this->key = key;
}


template <class Key, class Value>
Position<Key, Value>::Position(const Position<Key, Value>& orig) {
    this->key = orig.getKey();
    this->value = orig.getValue();
}


template <class Key, class Value>
Position<Key, Value>::~Position();


// Modificadors
// ----------------

// setParent
// setLeft
// setRight


// Consultors
// --------------



/* Operacions */



#endif // POSITION_H