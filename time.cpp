#include "WordIndexer.h"
#include "WordIndexerBalanced.h"

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <iomanip>
#include <stdexcept>

using namespace std;

struct Result {
    double insertionUnbalanced;
    double searchUnbalanced;
};

double ms(
    const chrono::steady_clock::time_point& begin,
    const chrono::steady_clock::time_point& end
) {
    return chrono::duration<double, milli>(end - begin).count();
}

template <class Indexer>
void searchDictionary(Indexer& wi, const string& dictionaryPath) {
    ifstream dict(dictionaryPath);

    if (!dict.is_open()) {
        throw runtime_error("No s'ha pogut obrir " + dictionaryPath);
    }

    string word;

    while (dict >> word) {
        wi.contains(word);
    }

    dict.close();
}

template <class Indexer>
Result measureUnbalanced(const string& dictionaryPath) {
    Result result;

    cout << "Mesurant unbalancedText.txt..." << endl;

    chrono::steady_clock::time_point beginInsert = chrono::steady_clock::now();

    Indexer wi("unbalancedText.txt");

    chrono::steady_clock::time_point endInsert = chrono::steady_clock::now();

    chrono::steady_clock::time_point beginSearch = chrono::steady_clock::now();

    searchDictionary(wi, dictionaryPath);

    chrono::steady_clock::time_point endSearch = chrono::steady_clock::now();

    result.insertionUnbalanced = ms(beginInsert, endInsert);
    result.searchUnbalanced = ms(beginSearch, endSearch);

    return result;
}

void printTable(const Result& binary, const Result& balanced) {
    cout << endl;
    cout << "AVALUACIO D'ESTRUCTURES - UNBALANCED" << endl;
    cout << "Temps en ms" << endl;
    cout << string(70, '-') << endl;

    cout << fixed << setprecision(3);

    cout << left
         << setw(18) << "Estructura"
         << setw(26) << "Insercio UNBALANCED"
         << setw(24) << "Cerca UNBALANCED"
         << endl;

    cout << string(70, '-') << endl;

    cout << left
         << setw(18) << "BinaryTree"
         << setw(26) << binary.insertionUnbalanced
         << setw(24) << binary.searchUnbalanced
         << endl;

    cout << left
         << setw(18) << "BalancedTree"
         << setw(26) << balanced.insertionUnbalanced
         << setw(24) << balanced.searchUnbalanced
         << endl;

    cout << string(70, '-') << endl;
}

int main() {
    try {
        const string dictionaryPath = "dictionary.txt";

        cout << "Mesurant BinaryTree amb unbalancedText.txt..." << endl;
        Result binary = measureUnbalanced<WordIndexer>(dictionaryPath);

        cout << endl;

        cout << "Mesurant BalancedTree amb unbalancedText.txt..." << endl;
        Result balanced = measureUnbalanced<WordIndexerBalanced>(dictionaryPath);

        printTable(binary, balanced);

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}