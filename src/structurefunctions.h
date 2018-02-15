/**
 *
 *
 *
 *
 *
 */

#ifndef STRUCTUREFUNCTIONS_H_
#define STRUCTUREFUNCTIONS_H_

#include <stddef.h>
#include <stdlib.h>

#define null NULL

/*
* Struct de cada Nó
* p node pai
* lc node filho da esquerda
* rc node filho da direita
* value Dado salvo no node
*/
typedef struct node {
    struct node *p;
    struct node *lc;
    struct node *rc;
    char value;
} Node;

extern Node* new_Node(char new_value) {
	Node *novo = malloc(sizeof(Node));
	novo->value = new_value;
	novo->p = null;
	novo->lc = null;
	novo->rc = null;

	return novo;
}

extern Node *root; //variavel global com do nó raiz

extern Node getRoot(); //Retorna raiz da arvore
extern int isEmpty(); //verifica se arvore esta vazia
extern int qtdNodes(Node *r); //retorna a quantidade de nós
extern int height(Node *r); // retorna a altura da arvore
extern void createByPostfix(char* postfix); //cria a arvore a partir da sequencia postfix
extern void printTreeInLevel(); // Imprime por nivel
extern void preOrder(Node *r); //imprime a sequencia preordem
extern void inOrder(Node *r); //imprime a sequencia em ordem
extern void posOrder(Node *r); //imprime a sequencia posordem (postfix)
extern void whoLeaf(Node *r); // imprime folhas e seus pais

#endif // STRUCTUREFUNCTIONS_H_
