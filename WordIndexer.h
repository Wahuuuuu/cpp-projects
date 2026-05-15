#ifndef WORDINDEXER_H
#define WORDINDEXER_H

#include "BinaryTree.h"
#include "Position.h"
#include "Tuple.h"
#include <iostream>
#include <chrono>
#include <stdexcept>
#include <vector>

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
    void printDictionary(Position<string, Tuple<int>> *node = nullptr) const;

protected:
    BinaryTree<string, Tuple<int> > *tree; 
    void addText(string path);

private:
    bool askWhetherContinue() const;
    void insertWord(const string &word, const int &line, const int &position); 
    void printNode(const Position<string, Tuple<int>>* node) const;
    
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
 * @brief Creates a WordIndexer with a tree based on the content of the file. 
 * And prints the execution time of the creation.
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
void WordIndexer::printOccurrences(const string &word) const {
    Position<string, Tuple<int>>* node = this->tree->search(word);

    if (node == nullptr) throw new out_of_range("No s'ha pogut print occurrences: la palaura \"" + word + "\" no està en l'arbre");
    
    printNode(node);
}

/**
 * @brief Prints all occurrences of all word in alphabetical order. For each 40 words, asks whether to continue.
 */
void WordIndexer::printDictionary(Position<string, Tuple<int> > *node = nullptr) const {
    if(this->tree->isEmpty()) return;

    vector< Position<string, Tuple<int>>* > pending;
    pending.push_back(this->tree->getRoot());


    while(!pending.empty()) {
        for (int i = 0; i < 40 && !pending.empty(); i++) {
            Position<string, Tuple<int>>* current = pending.back();
            pending.pop_back();

            printNode(current); cout << endl;

            if (current->getRight() != nullptr) {
                pending.push_back(current->getRight());
            }

            if (current->getLeft() != nullptr) {
                pending.push_back(current->getLeft());
            }
        }

        if (!pending.empty()) {
            bool cont = askWhetherContinue();
            if (!cont) return;
        }
    }
}

/**
 * @brief Asks user whether to continue.
 */
bool WordIndexer::askWhetherContinue() const {
    cout << "Voleu seguir mostrant l'arbre (s/n)?" << endl;
    
    string option = ""; cin >> option;
    while ((option != "s") && (option != "n")) {
        cout << "Opció invalida, torneu a introduir una opció (s/n): " << endl;
        cin >> option;
    }

    if (option == "s") return true;
    return false;
}


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

/**
 * @brief Prints the node. If node == nullptr, prints nothing.
 * 
 * Format:
 * key [(value[0].line, value[0].word), ...,  (value[n].line, value[n].word)]
 */
void WordIndexer::printNode(const Position<string, Tuple<int>>* node) const {
    if (node == nullptr) return;

    vector<Tuple<int>> occurences = node->getValues();
    cout << node->getKey() << " [";

    // Prints (value[0].line, value[0].word)
    for (vector<Tuple<int>>::iterator it = occurences.begin(); it != occurences.end(); ++it) {
        cout << "(" << it->getLine() << ", " << it->getWord() << ")";
    }

    cout << "]";
}

#endif  // WORDINDEXER_H