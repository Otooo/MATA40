/**
 *
 *
 *
 *
 *
 */

#ifndef TREE_H_
#define TREE_H_

#include <stddef.h>

#define null NULL

struct Node {
    Node *p;
    Node *lc;
    Node *rc;
    char value;

	Node(char new_value) {
	   value = new_value;
	   p = null;
	   lc = null;
	   rc = null;
    }
};

class Tree {
    Node *root; // Nó raiz

    public:
        Tree();  // Construtor
        ~Tree(); // Destrutor
        Node *getRoot();
        bool isEmpty();
        int qtdNodes(Node *r);
        int height(Node *r);
        void insert(char new_value);
        void createByPostfix(char *postfix);
        void printTreeInLevel(); // Imprime por nivel
        void preOrder(Node *r);
        void inOrder(Node *r);
        void posOrder(Node *r);
        void whoLeaf(Node *r); // imprime folhas e seus pais
};

#endif // TREE_H_
