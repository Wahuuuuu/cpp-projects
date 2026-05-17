/* 
 * Temps en ms
 *
 *                  Insercio SHORT   Insercio LONG   Insercio UNBALANCED   Cerca SHORT   Cerca LONG   Cerca UNBALANCED
 * BinaryTree       4.95              253.12         800000              338.11       443.70       molt gran
 * BalancedTree     8.26              381.55         100000             370.24       460.50       240
 *
 * ====================================================================================================================
 * 
 * BinaryTree:  
 *    - Inserció: O(n), on n és l'alçada de l'arbre.  
 *      Si l'arbre està bastant equilibrat, pot aproximar-se a O(log n).  
 *  
 *    - Cerca: O(n).  
 *      En el pitjor cas, O(n).  
 *      En un arbre equilibrat, O(log n).  
 *  
 * BalancedTree:  
 *    - Inserció: O(log n), perquè després d'inserir es reequilibra l'arbre.  
 *    - Cerca: O(log n), perquè l'alçada es manté equilibrada.  
 *  
 * En fitxers desbalancejats, BalancedTree hauria de tenir millor temps de cerca i una alçada molt menor. 
 * En canvi, en fitxers petits, BinaryTree és una mica més ràpid, perquè BalancedTree hereta del BinaryTree.
 */


#include "WordIndexer.h"
#include "WordIndexerBalanced.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <stdexcept>

void mainExercici1(){ 
    BinaryTree<int, int> tree1; 
    int testKeys[] = {2, 0, 8, 45, 76, 5, 3, 40}; 
    int testValues[] = {5, 5, 1, 88, 99, 12, 9, 11};

    for (int i = 0; i < 8 ; i++) { 
        cout << "Inserta a l'arbre la key " << testKeys[i] << " amb valor " << testValues[i] << endl;
        tree1.insert(testKeys[i], testValues[i]); 
    } 
    
    cout << "Preorder = ["; tree1.printPreOrder(); cout << "]" << endl; 
    cout << "Postorder = ["; tree1.printPostOrder(); cout << "]" << endl;
    
    BinaryTree<int, int> tree2(tree1); 
    cout << " identics " << tree1.identicalTree(tree2) << endl;
    cout << "Preorder = ["; tree1.printPreOrder(); cout << "]" << endl;
    
    tree2.insert(4, 4); 
    cout << " identics " << tree2.identicalTree(tree1) << endl;
    cout << "Preorder = ["; tree2.printPreOrder(); cout << "]" << endl;
    
    vector<int> result = tree2.getLeaves(); 
    cout << "fulles arbres = " ;
    for (vector<int>::iterator it = result.begin(); it != result.end(); ++it) { 
        cout << *it << " ";
    } 
    cout << endl; 

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



int main() {
    mainExercici1();
    mainExercici3();
}