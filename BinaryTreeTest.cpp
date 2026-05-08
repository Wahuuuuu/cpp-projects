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
    cout << "testDefaultConstructor ended" << endl;
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

    cout << "testInsert ended" << endl;
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

    assert(*orig.getRoot() == *bt.getRoot());

    assert(bt.getRoot()->getKey() == 10);

    assert(bt.getRoot()->getLeft()->getKey() == 5);
    assert(bt.getRoot()->getLeft()->getLeft()->getKey() == -5);
    assert(bt.getRoot()->getLeft()->getRight()== nullptr);


    assert(bt.getRoot()->getRight()->getKey() == 15);
    assert(bt.getRoot()->getRight()->getLeft()->getKey() == 12);
    assert(bt.getRoot()->getRight()->getRight()->getKey() == 20);
    assert(bt.getRoot()->getRight()->getRight()->getRight()->getKey() == 30);

    assert(bt.size() == 7);
    assert(bt.height() == 4);

    cout << "testCopyConstructor ended" << endl;
}

void testDestructorDoesNotCrash() {
    BinaryTree<int, string>* bt(initTree());

    delete bt;

    cout << "testDestructorDoesNotCrash ended" << endl;
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

    cout << "testContains ended" << endl;
}

void testGetValues() {


}


int main() {
    testDefaultConstructor();
    testInsert();
    testCopyConstructor();
    testDestructorDoesNotCrash();
    testContains();
    testGetValues();
}