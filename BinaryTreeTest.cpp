#include "Position.h"
#include "BinaryTree.h"
#include <cassert>
#include <iostream>
#include <vector>

void testDefaultConstructor() {
    BinaryTree<int, int>* bt = new BinaryTree<int, int>();
    assert(bt->isEmpty());
    assert(bt->size() == 0);
    assert(bt->getRoot() == nullptr);
}

int main() {
    testDefaultConstructor();
}