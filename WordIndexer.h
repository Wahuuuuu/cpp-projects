#ifndef WORDINDEXER_H
#define WORDINDEXER_H

#include "BinaryTree.h"
#include "Position.h"
#include "Tuple.h"
#include <iostream>

using namespace std;

class WordIndexer { 
public:
    WordIndexer(); 
    WordIndexer(string path); 
    WordIndexer(const WordIndexer& orig); 
    virtual ~WordIndexer(); 

    int size() const; 
    int height() const; 
    bool contains(const string &word) const; 
    void printOccurrences(const string &word) const; 
    void printDictionary(Position<string, Tuple<int> > *node = nullptr) const;

protected:
    BinaryTree<string, Tuple<int> > *tree; 
    void addText(string path);

private:
    void insertWord(const string &word, const int &line, const int &position); 
    /* Metodes auxiliars, definiu-los aquí sota */
};


// constructors and destructor
// -------------------------------

/**
 * @brief Default constructor. Creates a WordIndexer with an empty tree.
 */
WordIndexer::WordIndexer() {
    this->tree = new BinaryTree<string, Tuple<int>>();
}

/**
 * @brief Reads the file and creates a WordIndexer with a tree based on the content of the file.
 */
WordIndexer::WordIndexer(string path) {
    this->addText(path);
}

/**
 * @brief Copy constructor. Creates a WordIndexer with a cloned tree of the orig WordIndexer.
 */
WordIndexer::WordIndexer(const WordIndexer& orig) {

}

/**
 * @brief Destructor.
 */
WordIndexer::~WordIndexer() {
    delete this->tree;
}


// methods:
// -------------------------------

/**
 * @brief Returns the size of the tree.
 */
int WordIndexer::size() const {
    return this->tree->size();
}

/**
 * @brief Returns the height of the tree
 */
int WordIndexer::height() const {
    return this->tree->height();
}

/**
 * @brief Returns whether the tree contains the word
 */
bool WordIndexer::contains(const string &word) const {
    return this->tree->contains(word);
}

/**
 * @brief Prints all occurrences of the word
 */
void WordIndexer::printOccurrences(const string &word) const; 

/**
 * @brief Prints all occurrences of all word in alphabetical order
 */
void WordIndexer::printDictionary(Position<string, Tuple<int> > *node = nullptr) const;

/**
 * @brief Reads the file and save it's words into the tree.
 * 
 * The words will be saved in lowercase. 
 * The punctuation marks will be removed.
 * 
 * @param Path to the file.
 */
void WordIndexer::addText(string path);

/**
 * @brief Given the word and it's line and position of the word in text. Add it to the tree.
 * 
 * If the word is not in tree, adds a new node;
 * if it already exists, appends value to the node.
 */
void WordIndexer::insertWord(const string &word, const int &line, const int &position); 


#endif  // WORDINDEXER_H