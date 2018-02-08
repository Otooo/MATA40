/**
 * 
 * 
 * 
 * 
 * 
 */

#ifndef TREE_H_
#define TREE_H_

#include "node.h"

class Tree {
    Node root;  // Nó raiz

    public:
        Tree();  // Construtor
        ~Tree(); // Destrutor
        Node getRoot();
        bool isEmpty();
        int height(Node root);
        void insert(char new_value);
        void printTree();
        void preOrder();
        void inOrder();
        void posOrder();
        Node whoFather(Node node);
        void whoLeaf(); // Talvez retornar alguma coisa        
};

#endif // TREE_H_