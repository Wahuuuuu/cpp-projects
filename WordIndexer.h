#ifndef WORDINDEXER_H
#define WORDINDEXER_H

#include "BinaryTree.h"
#include "Position.h"
#include "Tuple.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <stdexcept>
#include <string>
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
    void insertWord(const string &word, const int &line, const int &position); 

    void printDictionary_(Position<string, Tuple<int> > *node) const;
    void addLineText(const string& lineText, const int& lineCount) const;
    bool askWhetherContinue() const;
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
    this->tree = new BinaryTree<string, Tuple<int>>();
    this->addText(path);
}

/**
 * @brief Copy constructor. Creates a WordIndexer with a cloned tree of the orig WordIndexer.
 */
WordIndexer::WordIndexer(const WordIndexer& orig) {
    this->tree = new BinaryTree<string, Tuple<int>>(*orig.tree);
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
 * 
 * @throw out_of_range If the word is not in tree.
 */
void WordIndexer::printOccurrences(const string &word) const {
    Position<string, Tuple<int>>* node = this->tree->search(word);

    if (node == nullptr) throw out_of_range("No s'ha pogut print occurrences: la palaura \"" + word + "\" no està en l'arbre");
    
    printNode(node);
}


void WordIndexer::printDictionary(Position<string, Tuple<int> > *node) const {
    if (this->tree->isEmpty()) return;
    if (node == nullptr) {
        printDictionary_(this->tree->getRoot()); 
        return;
    }
    if (this->contains(node->getKey())) {
        printDictionary_(node); 
        return;
    }
    else throw out_of_range("Not able to print dictionary: the node is not in tree!");
}


/**
 * @brief Prints all occurrences of all word in alphabetical order. For each 40 words, asks whether to continue.
 */
void WordIndexer::printDictionary_(Position<string, Tuple<int> > *node) const {
    if(this->tree->isEmpty()) return;

    vector< Position<string, Tuple<int>>* > pending;
    pending.push_back(node);


    
    bool cont = true;
    while(!pending.empty()) {
        for (int i = 0; i < 40 && !pending.empty(); i++) {
            Position<string, Tuple<int>>* current = pending.back();

            while (current->getRight() != nullptr) {
                pending.push_back(current->getRight());
            }

            printNode(current); cout << endl;
            pending.pop_back();

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
 * @throw runtime_error if not able to open the file
 */
void WordIndexer::addText(string path) 
{
    ifstream file(path);
    if (!file.is_open()) throw runtime_error("No s'ha pogut obrir el fitxer");

    string lineText;
    int lineCount = 0;
    while (getline(file, lineText)) 
    {
        lineCount++;
        addLineText(lineText, lineCount);
    }

    file.close();

}

/**
 * @brief Add each word of a line into the tree.
 */
void WordIndexer::addLineText(const string& lineText, const int& lineCount) const {
    string word = "";
    int wordCount = 0;
    for (string::const_iterator it = lineText.begin(); it != lineText.end(); it++) {
        char letter = *it;
        if (isalnum(letter)) {
            word += tolower(letter);
        }
        else {
            // if not empty and not alnum: end of a word, should add occurence
            if (!word.empty()) {
                wordCount++;

                Tuple<int> occurence(lineCount, wordCount);
                tree->insert(word, occurence);

                word = "";
            }
            // if empty and not alnum: not a word, do nothing
        }
    }
}

/**
 * @brief Given the word and it's line and position of the word in text. Add it to the tree.
 * 
 * If the word is not in tree, adds a new node;
 * if it already exists, appends value to the node.
 */
void WordIndexer::insertWord(const string &word, const int &line, const int &position) {
    Tuple<int> occurence(line, position);
    this->tree->insert(word, occurence);
}

/**
 * @brief Prints the node. If node == nullptr, prints nothing.
 * 
 * Format:
 * key [(value[0].line, value[0].word), ...,  (value[n].line, value[n].word)]
 * 
 * @throw out_of_range If the node is not in tree or if the tree is empty
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