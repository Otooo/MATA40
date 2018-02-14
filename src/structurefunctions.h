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

extern Node *root; //variavel global com do nó raiz

extern Node getRoot(); //Retorna raiz da arvore
extern bool isEmpty(); //verifica se arvore esta vazia
extern int qtdNodes(Node *r); //retorna a quantidade de nós
extern int height(Node *r); // retorna a altura da arvore
extern void createByPostfix(char* postfix); //cria a arvore a partir da sequencia postfix
extern void printTreeInLevel(); // Imprime por nivel
extern void preOrder(Node *r); //imprime a sequencia preordem
extern void inOrder(Node *r); //imprime a sequencia em ordem
extern void posOrder(Node *r); //imprime a sequencia posordem (postfix)
extern void whoLeaf(Node *r); // imprime folhas e seus pais

#endif // TREE_H_
