#include "Position.h"
#include <iostream>
#include <vector>
#include <cassert>

void testDefaultConstructor() {
    Position<int, int> *p1 = new Position<int, int>(11);
    assert(p1->getKey() == 11);
    assert(p1->getValues().size() == 0);
    assert(p1->getParent() == nullptr);
    assert(p1->getLeft() == nullptr);
    assert(p1->getRight() == nullptr);

    Position<int, int> *p2 = new Position<int, int>(11);
    assert(&p1->getValues() != &p2->getValues());

    cout << "Default constructor is tested" << endl;
}




int main() {
    testDefaultConstructor();
}