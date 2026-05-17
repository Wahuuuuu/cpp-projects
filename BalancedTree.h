#ifndef BALANCEDTREE_H
#define BALANCEDTREE_H

#include "BinaryTree.h"
#include "Position.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

template <class Key, class Value>
class BalancedTree : public BinaryTree<Key, Value> {
public:
    /**
     * @brief Constructor. Creates an empty balanced binary search tree.
     *
     * Worst-case cost: O(1)
     */
    BalancedTree();
    /**
     * @brief Copy constructor. Creates a deep copy of orig.
     *
     * Worst-case cost: O(n)
     */
    BalancedTree(const BalancedTree<Key, Value>& orig);
    /**
     * @brief Destructor.
     *
     * Worst-case cost: O(n)
     */
    virtual ~BalancedTree();

    /**
     * @brief Inserts a key-value pair and rebalances the tree if needed.
     *
     * Worst-case cost: O(log n) if the tree is correctly balanced.
     */
    virtual Position<Key, Value>* insert(const Key& key, const Value& value);

private:
    /**
     * @brief Returns the balance factor of a node. If node == nullptr, returns -1;
     *
     * Worst-case cost depends on the height implementation.
     */
    int balanceFactor(Position<Key, Value>* node) const;
    /**
     * @brief Rebalances the tree from a given node upwards.
     *
     * Worst-case cost: O(log n)
     */
    void rebalance(Position<Key, Value>* node);
    /**
     * @brief Performs a left rotation.
     *
     * Worst-case cost: O(1)
     */
    Position<Key, Value>* rotateLeft(Position<Key, Value>* node);
    /**
     * @brief Performs a right rotation.
     *
     * Worst-case cost: O(1)
     */
    Position<Key, Value>* rotateRight(Position<Key, Value>* node);
    /**
     * @brief Performs a left rotation and a right rotation.
     *
     * Worst-case cost: O(1)
     */
    Position<Key, Value>* rotateLeftRight(Position<Key, Value>* node);
    /**
     * @brief Performs a right rotation and aleft rotation.
     *
     * Worst-case cost: O(1)
     */
    Position<Key, Value>* rotateRightLeft(Position<Key, Value>* node);
    /**
     * @brief Connects the rotated subtree with its parent.
     *
     * Worst-case cost: O(1)
     */
    void replaceParentChild(Position<Key, Value>* oldChild, Position<Key, Value>* newChild);
};


// constructors and destructor:
// --------------------------------

/**
 * @brief Constructor. Creates an empty balanced binary search tree.
 *
 * Worst-case cost: O(1)
 */
template <class Key, class Value>
BalancedTree<Key, Value>::BalancedTree() 
    : BinaryTree<Key, Value>() {
}

/**
 * @brief Copy constructor. Creates a deep copy of orig.
 *
 * Worst-case cost: O(n)
 */
template <class Key, class Value>
BalancedTree<Key, Value>::BalancedTree(const BalancedTree<Key, Value>& orig)
    : BinaryTree<Key, Value>(orig) {
}

/**
 * @brief Destructor.
 *
 * Worst-case cost: O(n)
 */
template <class Key, class Value>
BalancedTree<Key, Value>::~BalancedTree() {
}


// methods:
// --------------------------------

/**
 * @brief Inserts a key-value pair and rebalances the tree if needed.
 * 
 * If the key already exists, adds value to the existing position.
 * Otherwise, a new position is created, and check whether to rebalance.
 *
 * Worst-case cost: O(log n) if the tree is correctly balanced.
 */
template <class Key, class Value>
Position<Key, Value>* BalancedTree<Key, Value>::insert(const Key& key, const Value& value) {
    bool alreadyExists = this->contains(key);

    Position<Key, Value>* posInserted = BinaryTree<Key, Value>::insert(key, value);

    if (!alreadyExists && posInserted != nullptr) {
        rebalance(posInserted->getParent());
    }

    return posInserted;
}

/**
 * @brief Returns the balance factor of a node. If node == nullptr, returns -1;
 *
 * Worst-case cost depends on the height implementation.
 */
template <class Key, class Value>
int BalancedTree<Key, Value>::balanceFactor(Position<Key, Value>* node) const {
    if (node == nullptr) return -1;

    int leftHeight = -1;
    int rightHeight = -1;

    if (node->getLeft() != nullptr) leftHeight = node->getLeft()->height();
    if (node->getRight() != nullptr) rightHeight = node->getRight()->height();

    return (leftHeight - rightHeight);
}

/**
 * @brief Rebalances the tree from a given node upwards.
 *
 * Worst-case cost: O(log n)
 */
template <class Key, class Value>
void BalancedTree<Key, Value>::rebalance(Position<Key, Value>* node) {
    while (node != nullptr) {
        int bf = balanceFactor(node);

        if (bf > 1) {
            if (balanceFactor(node->getLeft()) >= 0) {  // cas left left
                node = rotateRight(node);
            } 
            else {  // cas left right
                node = rotateLeftRight(node);
            }

        }
        else if (bf < -1) {
            if (balanceFactor(node->getRight()) <= 0) { // case right right
                node = rotateLeft(node);
            } 
            else {  // case right left
                node = rotateRightLeft(node);
            }
        }

        node = node->getParent();
    }
}

/**
 * @brief Performs a left rotation.
 *
 * Worst-case cost: O(1)
 */
template <class Key, class Value>
Position<Key, Value>* BalancedTree<Key, Value>::rotateLeft(Position<Key, Value>* node) {
    Position<Key, Value>* pivot = node->getRight();
    Position<Key, Value>* subtreeB = pivot->getLeft();

    replaceParentChild(node, pivot);

    pivot->setLeft(node);
    node->setParent(pivot);

    node->setRight(subtreeB);

    if (subtreeB != nullptr) {
        subtreeB->setParent(node);
    }

    return pivot;

}

/**
 * @brief Performs a right rotation.
 *
 * Worst-case cost: O(1)
 */
template <class Key, class Value>
Position<Key, Value>* BalancedTree<Key, Value>::rotateRight(Position<Key, Value>* node) {
    Position<Key, Value>* pivot = node->getLeft();
    Position<Key, Value>* subtreeB = pivot->getRight();

    replaceParentChild(node, pivot);

    pivot->setRight(node);
    node->setParent(pivot);

    node->setLeft(subtreeB);

    if (subtreeB != nullptr) {
        subtreeB->setParent(node);
    }

    return pivot;
}

/**
 * @brief Performs a left rotation and a right rotation.
 *
 * Worst-case cost: O(1)
 */
template <class Key, class Value>
Position<Key, Value>* BalancedTree<Key, Value>::rotateLeftRight(Position<Key, Value>* node) {
    Position<Key, Value>* leftChild = node->getLeft();

    rotateLeft(leftChild);
    return rotateRight(node);
}

/**
 * @brief Performs a right rotation and aleft rotation.
 *
 * Worst-case cost: O(1)
 */
template <class Key, class Value>
Position<Key, Value>* BalancedTree<Key, Value>::rotateRightLeft(Position<Key, Value>* node) {
    Position<Key, Value>* rightChild = node->getRight();

    rotateRight(rightChild);
    return rotateLeft(node);
}

/**
 * @brief Connects the rotated subtree with its parent.
 *
 * Worst-case cost: O(1)
 */
template <class Key, class Value>
void BalancedTree<Key, Value>::replaceParentChild(Position<Key, Value>* oldChild,Position<Key, Value>* newChild) {
    Position<Key, Value>* parent = oldChild->getParent();

    if (parent == nullptr) {
        this->root = newChild;
        if (newChild != nullptr ) {
            newChild->setParent(nullptr);
        }
    }
    else if (parent->getLeft() == oldChild) {
        parent ->setLeft(newChild);

        if (newChild != nullptr) {
            newChild->setParent(parent);
        }
    }
    else if (parent->getRight() == oldChild) {
        parent->setRight(newChild);
        if (newChild != nullptr) {
            newChild->setParent(parent);
        }
    }

}

#endif // BALANCEDTREE_H