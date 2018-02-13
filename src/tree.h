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

/*
* Struct de cada node
* p node pai
* lc node filho da esquerda
* rc node filho da direita
* value Dado salvo no node
*/
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

/*
* Classe Tree e seus metodos e atributos publicos 
*/
class Tree {
    Node *root; // Nó raiz

    public:
        Tree();  // Construtor
        ~Tree(); // Destrutor
        Node *getRoot(); //Retorna raiz da arvore
        bool isEmpty(); //verifica se arvore esta vazia
        int qtdNodes(Node *r); //retorna a quantidade de nós
        int height(Node *r); // retorna a altura da arvore
        void createByPostfix(char *postfix); //cria a arvore a partir da sequencia postfix
        void printTreeInLevel(); // Imprime por nivel
        void preOrder(Node *r); //imprime a sequencia preordem
        void inOrder(Node *r); //imprime a sequencia em ordem
        void posOrder(Node *r); //imprime a sequencia posordem (postfix)
        void whoLeaf(Node *r); // imprime folhas e seus pais
};

#endif // TREE_H_
