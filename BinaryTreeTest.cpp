#include "Position.h"
#include "BinaryTree.h"
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

void testDefaultConstructor() {
    BinaryTree<int, int>* bt = new BinaryTree<int, int>();
    assert(bt->isEmpty());
    assert(bt->size() == 0);
    assert(bt->getRoot() == nullptr);

    delete bt;
    cout << "1. testDefaultConstructor ended" << endl;
}

void testInsert() {
    BinaryTree<int, int>* bt = new BinaryTree<int, int>();

    /* test emptytree and insert new node*/
    Position<int, int>* pos1 = bt->insert(5, 5);  // case empty tree
    Position<int, int>* pos2 = bt->insert(2, 2);  // cases insert new node
    Position<int, int>* pos3 = bt->insert(3, 3);
    Position<int, int>* pos4 = bt->insert(1, 1);
    Position<int, int>* pos5 = bt->insert(6, 6);

    assert(bt->getRoot()->getKey() == 5);
    assert(bt->getRoot()->getLeft()->getKey() == 2);
    assert(bt->getRoot()->getLeft()->getRight()->getKey() == 3);
    assert(bt->getRoot()->getLeft()->getLeft()->getKey() == 1);
    assert(bt->getRoot()->getRight()->getKey() == 6);

    assert(pos1->getKey() == 5);
    assert(pos2->getKey() == 2);
    assert(pos3->getKey() == 3);
    assert(pos4->getKey() == 1);
    assert(pos5->getKey() == 6);

    assert(bt->height() == 3);

    /* test key exists */
    bt->insert(5, 55);
    bt->insert(2, 22);
    bt->insert(3, 33);

    vector<int> v1 = {5, 55}; assert(pos1->getValues() == v1);
    vector<int> v2 = {2, 22}; assert(pos2->getValues() == v2);
    vector<int> v3 = {3, 33}; assert(pos3->getValues() == v3);

     // bt->printPreOrder(bt->getRoot()); cout << endl;

    cout << "2. testInsert ended" << endl;
}

/*
 *           10
 *       5       15
 *   -5          12  20
 *                       30
*/
BinaryTree<int, string>* initTree() {
    BinaryTree<int, string>* bt = new BinaryTree<int, string>();
    bt->insert(10, "10"); bt->insert(5, "5"); bt->insert(-5, "-5");
    bt->insert(15, "15"); bt->insert(12, "12"); bt->insert(20, "20"); bt->insert(30, "30");
    return bt;
}

void testCopyConstructor() {
    BinaryTree<int, string> orig(*initTree());
    BinaryTree<int, string> bt(orig);

    assert(*orig.getRoot() == *bt.getRoot());  // orig tree and cloned tree refers to different address
    assert(orig.getRoot()->getValues()[0] == "10");

    assert(bt.getRoot()->getKey() == 10);
    assert(bt.getRoot()->getValues().size() == 1);

    assert(bt.getRoot()->getLeft()->getKey() == 5);
    assert(bt.getRoot()->getLeft()->getLeft()->getKey() == -5);
    assert(bt.getRoot()->getLeft()->getRight()== nullptr);


    assert(bt.getRoot()->getRight()->getKey() == 15);
    assert(bt.getRoot()->getRight()->getLeft()->getKey() == 12);
    assert(bt.getRoot()->getRight()->getRight()->getKey() == 20);
    assert(bt.getRoot()->getRight()->getRight()->getRight()->getKey() == 30);

    assert(bt.size() == 7);
    assert(bt.height() == 4);

    cout << "3. testCopyConstructor ended" << endl;
}

void testDestructorDoesNotCrash() {
    BinaryTree<int, string>* bt(initTree());

    delete bt;

    cout << "4. testDestructorDoesNotCrash ended" << endl;
}

void testContains() {
    BinaryTree<int, string>* bt (initTree());

    assert(bt->contains(10));
    assert(bt->contains(5));
    assert(bt->contains(-5));
    assert(bt->contains(15));
    assert(bt->contains(12));
    assert(bt->contains(20));
    assert(bt->contains(30));

    assert(!bt->contains(0));
    assert(!bt->contains(10086));

    delete bt;
    cout << "5. testContains ended" << endl;
}

void testGetValues() {
    BinaryTree<int, string>* bt(initTree());

    vector<string> v1 = {"5"}; assert(bt->getValues(5) == v1);
    vector<string> v2 = {"-5"}; assert(bt->getValues(-5) == v2);
    vector<string> v3 = {"30"}; assert(bt->getValues(30) == v3);

    /* assert throw */
    bool emptyTree = false; bool notInTree = false;

    try { bt->getValues(10086); }
    catch (const out_of_range& e) { notInTree = true; }

    BinaryTree<int, string>* emptybt = new BinaryTree<int, string>();
    try { emptybt->getValues(1); }
    catch (const out_of_range& e) { emptyTree = true; }

    assert(emptyTree && notInTree);

    delete bt;
    cout << "6. testGetValues ended" << endl;
}

void testPrintPreOrder() {
    BinaryTree<int, string>* bt(initTree());
    string expTreePreOrder = " 10 5 -5 15 12 20 30";
    // bt->printPreOrder(bt->getRoot()); cout << endl;

    string expSubTreePreOrder = " 15 12 20 30";
    // bt->printPreOrder(bt->getRoot()->getRight()); cout << endl;

    BinaryTree<int, string>* emptybt = new BinaryTree<int, string>();
    string expEmptyTree = "";
    emptybt->printPreOrder(emptybt->getRoot());

    /* test not crash when parameter = nullptr */
    bt->printPreOrder(nullptr);
    bt->printPreOrder();

    /* assert exception if node not in tree */
    bool notInTree = false;
    Position<int, string> p(10086);
    try { bt->printPreOrder(&p); }
    catch (const out_of_range& e) { notInTree = true; }
    assert(notInTree);

    delete bt; delete emptybt;
    cout << "7. testPrintPreOrder ended" << endl;
}

void testPrintPostOrder() {
    BinaryTree<int, string>* bt(initTree());
    string expTreePostOrder = " -5 5 12 30 20 15 10";
    // bt->printPostOrder(bt->getRoot()); cout << endl;

    string expSubTreePostOrder = " 12 30 20 15";
    // bt->printPostOrder(bt->getRoot()->getRight()); cout << endl;

    BinaryTree<int, string>* emptybt = new BinaryTree<int, string>();
    string expEmptyTree = "";
    emptybt->printPostOrder(emptybt->getRoot());

    /* test not crash when parameter = nullptr */
    bt->printPostOrder(nullptr);
    bt->printPostOrder();

    /* assert exception if node not in tree */
    bool notInTree = false;
    Position<int, string> p(10086);
    try { bt->printPostOrder(&p); }
    catch (const out_of_range& e) { notInTree = true; }
    assert(notInTree);

    delete emptybt;
    cout << "8. testPrintPostOrder ended" << endl;
}

void testIdenticalTree() {
    // basic case
    BinaryTree<int, string>* bt = new BinaryTree<int, string>(*initTree());
    BinaryTree<int, string>* btCopy = new BinaryTree<int, string>(*initTree());
    assert(bt->identicalTree(*btCopy));

    bt->insert(8, "8");
    assert(!bt->identicalTree(*btCopy));

    // same tree
    assert(bt->identicalTree(*bt));

    // empty trees
    BinaryTree<int, string> emptyBt1;
    BinaryTree<int, string> emptyBt2;
    assert(emptyBt1.identicalTree(emptyBt2));

    delete bt;
    delete btCopy;
    cout << "9. testIdenticalTree ended" << endl;
}

void testSearch() {
    BinaryTree<int, string> bt(*initTree());

    assert(bt.search(10)->getValues()[0] == "10");
    assert(bt.search(5)->getValues()[0] == "5");
    assert(bt.search(-5)->getValues()[0] == "-5");
    assert(bt.search(15)->getValues()[0] == "15");
    assert(bt.search(12)->getValues()[0] == "12");
    assert(bt.search(20)->getValues()[0] == "20");
    assert(bt.search(30)->getValues()[0] == "30");

    assert(bt.search(10086) == nullptr);

    BinaryTree<int, string> emptyBt;
    assert(emptyBt.search(10086) == nullptr);

    cout << "10. testSearch ended" << endl;
}

void testGetLeaves() {
    vector<int> result;

    BinaryTree<int, string> bt(*initTree());
    vector<int> leavesBt = {-5, 12, 30};
    result = bt.getLeaves();
    assert(leavesBt == bt.getLeaves());

    BinaryTree<int, string> emptyBt;
    vector<int> leavesEmptyBt = {};
    assert(leavesEmptyBt == emptyBt.getLeaves());

    BinaryTree<int, string> rootBt; rootBt.insert(10, "10");
    vector<int> leavesRootBt = {10};
    assert(leavesRootBt == rootBt.getLeaves());

    cout << "11. testGetLeaves ended" << endl;
}

int main() {
    testDefaultConstructor();
    testInsert();
    testCopyConstructor();
    testDestructorDoesNotCrash();
    testContains();
    testGetValues();
    testPrintPreOrder();
    testPrintPostOrder();
    testIdenticalTree();
    testSearch();
    testGetLeaves();
}