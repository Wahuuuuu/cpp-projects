#ifndef WORDINDEXERBALANCED_H
#define WORDINDEXERBALANCED_H

#include "WordIndexer.h"
#include "BalancedTree.h"
#include "Tuple.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

class WordIndexerBalanced : public WordIndexer {
public:
    /**
     * @brief Constructor with path. Creates a word indexer using a balanced tree.
     *
     * Worst-case cost: O(n log n), which n is the number of words inserted.
     */
    WordIndexerBalanced(string path);

    /**
     * @brief Copy constructor.
     *
     * Worst-case cost: O(n)
     */
    WordIndexerBalanced(const WordIndexerBalanced& orig);

    /**
     * @brief Destructor.
     *
     * Worst-case cost: O(n)
     */
    virtual ~WordIndexerBalanced();
};



WordIndexerBalanced::WordIndexerBalanced(string path)
    : WordIndexer() {
    delete this->tree;
    this->tree = new BalancedTree<string, Tuple<int>>();

    addText(path);
}


WordIndexerBalanced::WordIndexerBalanced(const WordIndexerBalanced& orig)
    : WordIndexer() {
    delete this->tree;

    BalancedTree<string, Tuple<int>>* origTree = static_cast<BalancedTree<string, Tuple<int>>*>(orig.tree);

    this->tree = new BalancedTree<string, Tuple<int>>(*origTree);
}


WordIndexerBalanced::~WordIndexerBalanced() {
}

#endif // WORDINDEXERBALANCED_H