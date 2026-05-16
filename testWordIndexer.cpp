#include "BinaryTree.h"
#include "Position.h"
#include "Tuple.h"
#include "WordIndexer.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

void testConstructor() {
    WordIndexer wi;
    assert(wi.size() == 0);
    assert(wi.height() == 0);
    assert(wi.contains("Something") == false);

    cout << "0. testConstructor" << endl; 
}

void testFileConstructor() {
    WordIndexer wi("testFile.txt");

    assert(wi.size() != 0);
    assert(wi.height() != 0);
    assert(wi.contains("seventeen") == true);
    assert(wi.contains("Wahuuuuu") == false);
    assert(wi.contains("Now") == false);

    cout << "1. testFileConstructor" << endl;
}

void testCopyConstructor() {
    WordIndexer wi("testFile.txt");
    WordIndexer CopyWi(wi);

    assert(wi.size() != 0);
    assert(wi.height() != 0);
    assert(wi.contains("seventeen") == true);
    assert(wi.contains("Wahuuuuu") == false);
    assert(wi.contains("Now") == false);

    cout << "2. testCopyConstructor" << endl;
}

void testContains() {
    // test nonempty tree
    WordIndexer wi("testFile.txt");
    assert(wi.contains("seventeen") == true);
    assert(wi.contains("Wahuuuuu") == false);
    assert(wi.contains("Now") == false);
    assert(wi.contains("") == false);  // empty string

    WordIndexer emptyWi;
    assert(wi.contains("Something") == false);
    
    cout << "3. testContains" << endl;
}

void testPrintOccurrences() {
    WordIndexer wi("testFile.txt");

 /*    cout << "Exp: now [(3, 1), (6, 1)]" << endl;
    cout << "Actual: ";  wi.printOccurrences("now"); cout << endl; */

    bool throwed = false;
    try {
        wi.printOccurrences("Wahuuuuu");
    } catch (const exception& e) {
        throwed = true; 
    }
    assert(throwed);

    cout << "4. testPrintOccurrences" << endl;
}

void testPrintDictionary() {
    WordIndexer wi("testFile.txt");

    cout << wi.size() << endl;
    wi.printDictionary();

}


int main() {
    testConstructor();
    testFileConstructor();
    testCopyConstructor();
    testContains();
    testPrintOccurrences();
    testPrintDictionary();
}