#include "BinaryTree.h"
#include "Position.h"
#include "Tuple.h"
#include "WordIndexer.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;


void menuWordIndexer();
void printMenu();
int askOption();
void createNewWithFile(WordIndexer*& wi);
void searchAllWordsInDictionary(WordIndexer* wi);


int main() 
{
    menuWordIndexer();
}


void printMenu() {
    cout << endl;
    cout << "===== MENU WORD INDEXER =====" << endl;
    cout << "1. Crear WordIndexer a partir d'un fitxer" << endl;
    cout << "2. Mostrar l'arbre" << endl;
    cout << "3. Cercar les paraules del dictionary.txt" << endl;
    cout << "4. Generar i mostrar l'index de paraules" << endl;
    cout << "5. Mostrar l'alcada de l'arbre" << endl;
    cout << "6. Sortir" << endl;
}


int askOption() {
    cout << "Escull una opció (1 a 6): ";
    int option = -1;  cin >> option;

    while (option < 1 || 6 < option) {
        cout << "Opció invàlida, torneu d'escollir: ";
        cin >> option;
    }

    return option;
}


void menuWordIndexer() {
    WordIndexer* wi;

    bool end = false;
    while (!end) {
        printMenu();
        int option = askOption();

        switch(option) {
            case 1: 
                createNewWithFile(wi);
                break;
            case 2:
                wi->printDictionary();
                break;
            case 3:
                searchAllWordsInDictionary(wi);
                break;
            case 4:
                wi->printDictionary();
                break;
            case 5:
                cout << "La profunditat de l'arbre és " << wi->height() - 1 << "." << endl;
                break;
            case 6:
                end = true;
                cout << "Fi de la programa" << endl;
                break;
        }
    }
}


void createNewWithFile(WordIndexer*& wi) {
    // Ask for path
    cout << "Quin fitxer vols (P/G)?";
    string f; cin >> f;
    while (f != "P" && f != "G") {
        cout << "Opció invàlida, torna d'introduir: ";
        cin >> f;
    }

    // create new indexer and delete old indexer
    string path = (f == "P")? "shortText.txt" : "longText.txt";
    try {
        chrono::steady_clock::time_point begin = chrono::steady_clock::now();
        WordIndexer* newWi = new WordIndexer(path);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();

        cout << "Nou word indexer creat correctament!" << endl;
        
        delete wi;
        wi = newWi;

        cout << "Temps transcorregut: " << chrono::duration_cast<chrono::seconds>(end - begin).count() << " s." << endl;

    } catch (const runtime_error& e) {
        cerr << "No s'ha pogut crear nou word indexer: " << e.what() << endl;
        cerr << "El valor del word indexer anterior s'ha canviat." << endl;
    }
}


void searchAllWordsInDictionary(WordIndexer* wi) {
    ifstream dict("dictionary.txt");
    if (!dict.is_open()) throw runtime_error("No s'ha pogut search in dictionary: el dictionary.txt no s'obre.");

    string word = "";
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    while (dict >> word) {
        if (!wi->contains(word)) {
            dict.close();
            throw runtime_error("No s'ha pogut search in dictionary: palaura \"" + word + "\" no encontrat.");
        }
    }
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << "Temps transcorregut: " << chrono::duration_cast<chrono::seconds>(end - begin).count() << " s." << endl;
    dict.close();
}