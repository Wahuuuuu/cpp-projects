#include "BalancedTree.h"
#include <iostream>
#include <vector>

using namespace std;

void mainExercici3();

int main() {
    mainExercici3();
    return 0;
}


void mainExercici3() {
    BalancedTree<int, int> tree1;

    int testKeys[] = {2, 0, 8, 45, 76, 5, 3, 40};
    int testValues[] = {5, 5, 1, 88, 99, 12, 9, 11};

    for (int i = 0; i < 8; i++) {
        cout << "Inserta a l'arbre la key "
             << testKeys[i]
             << " amb valor "
             << testValues[i]
             << endl;

        tree1.insert(testKeys[i], testValues[i]);
    }

    cout << "Preorder = [";
    tree1.printPreOrder();
    cout << "]" << endl;

    cout << "Postorder = [";
    tree1.printPostOrder();
    cout << "]" << endl;

    BalancedTree<int, int> tree2(tree1);

    cout << "identics " << tree1.identicalTree(tree2) << endl;

    cout << "Preorder = [";
    tree1.printPreOrder();
    cout << "]" << endl;

    tree2.insert(4, 4);

    cout << "identics " << tree2.identicalTree(tree1) << endl;

    cout << "Preorder = [";
    tree2.printPreOrder();
    cout << "]" << endl;

    vector<int> result = tree2.getLeaves();

    cout << "fulles arbres = ";

    for (vector<int>::iterator it = result.begin(); it != result.end(); ++it) {
        cout << *it << " ";
    }

    cout << endl;
}