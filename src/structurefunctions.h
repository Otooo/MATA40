/**
 *
 *
 *
 *
 *
 */

#ifndef STRUCTUREFUNCTIONS_H_
#define STRUCTUREFUNCTIONS_H_

#include "structurefunctions.h"
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

Node *new_Node(char new_value);

Node *root; //variavel global com do nó raiz

Node *getRoot(); //Retorna raiz da arvore
int isEmpty(); //verifica se arvore esta vazia
int qtdNodes(Node *r); //retorna a quantidade de nós
int height(Node *r); // retorna a altura da arvore
void createByPostfix(char* postfix); //cria a arvore a partir da sequencia postfix
void printTreeInLevel(); // Imprime por nivel
void preOrder(Node *r); //imprime a sequencia preordem
void inOrder(Node *r); //imprime a sequencia em ordem
void posOrder(Node *r); //imprime a sequencia posordem (postfix)
void whoLeaf(Node *r); // imprime folhas e seus pais

#endif // STRUCTUREFUNCTIONS_H_
