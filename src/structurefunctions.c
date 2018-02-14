//============================================================================
// Name        : MATA40.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description :  Ansi-style
//============================================================================

#include "structurefunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stack>
#include <ctype.h>

#define STACK_MAX 100

struct Stack {
	int data[STACK_MAX];
	int size;
};
typedef struct Stack Stack;

void initStack(Stack *s) {
	s->size = 0;
}

int top(Stack *s) {
	if (s->size > 0)
		return s->data[s->size-1];
	printf("Pilha vazia\n");
	return -1; //pilha vazia
}

void push(Stack *s, int d) {
	if (s->size < STACK_MAX)
		s->data[s->size++] = d;
	else
		printf("Pilha cheia\n");
}

void pop(Stack *s) {
	if (s->size == 0)
		printf("Pilha vazia!\n");
	else
		S->size--;
}


/**
 * Metodo que recupera o nó raiz da árvore
 *
 * @return O nó raiz da árvore
 */
Node *getRoot() {
    return root;
}

/**
 * Metodo que verifica se a árvore está vazia ou não
 *
 * @return Verdadeiro se a árvore estiver vazia, falso caso contrário
 */
bool isEmpty() {
    return (root == NULL);
}

/**
 * Metodo que recupera a quantidade de nós na árvore/sub-árvore
 *
 * @param r Nó de referência
 * @return Quantidade de nós na árvore/sub-árvore
 */
int qtdNodes(Node *r) {
	if (r == NULL)
		return 0;
	return 1 + qtdNodes(r->lc) + qtdNodes(r->rc);
}

/**
 * Metodo que recupera a altura da árvore/sub-árvore
 *
 * @param r Nó de referência
 * @return Altura da árvore/sub-árvore
 */
int height(Node *r) {
	if (r == NULL)
		return 0;
	int lh = height(r->lc);
	int rh = height(r->rc);
	return (lh > rh)? lh+1 : rh+1;
}

/**
 * Metodo que cria a árvore binária de expressão a partir
 * da expressão pós-fixada
 *
 * @param postfix Expressão pós-fixada
 */
void createByPostfix(char* postfix) {
	stack<Node*> sNode;

	int i;
	for (i = 0; postfix[i] != '\0'; i++) {
		Node *node = new Node(postfix[i]);
		if (isdigit(postfix[i])) {
			sNode.push(node);
		} else {
			// filhos
			node->rc = sNode.top(); sNode.pop();
			node->lc = sNode.top(); sNode.pop();
			// pai
			node->rc->p = node;
			node->lc->p = node;

			sNode.push(node);
		}
	}
	root = sNode.top();
}

/**
 * Metodo que imprime os valores na árvore por largura/nível
 */
void printTreeInLevel() {
	queue<Node*> fila;
	int totalNodes = qtdNodes(root);
	int limit = pow(2, totalNodes) - 1;
	int nivel = 0;
	int auxNivel = 0;
	bool print = false;

	fila.push(root);
	auxNivel++;

	while(limit--) {
		Node *n = fila.front();
		fila.pop();

		if ((int)pow(2, nivel) == auxNivel) {
			print = true;
			nivel++;
		}
		auxNivel++;

		if (print && n != NULL) {
			printf("\nNivel %d: ", nivel-1);
			print = false;
		}

		if (n != NULL) {
			printf("%c ", n->value);

			fila.push(n->lc);
			fila.push(n->rc);
		} else {
			fila.push(NULL);
			fila.push(NULL);
		}
	}
}


/**
 * Metodo que imprime os elementos da árvore em pré ordem recursivamente
 *
 * @param r Nó de referência
 */
void preOrder(Node *r) {
	if (r != NULL) {
		printf("%c ", r->value);
		preOrder(r->lc);
		preOrder(r->rc);
	}
}

/**
 * Metodo que imprime os elementos da árvore em ordem recursivamente
 *
 * @param r Nó de referência
 */
void inOrder(Node *r) {
	if (r != NULL) {
		inOrder(r->lc);
		printf("%c ", r->value);
		inOrder(r->rc);
	}
}

/**
 * Metodo que imprime os elementos da árvore em pós ordem recursivamente
 *
 * @param r Nó de referência
 */
void posOrder(Node *r) {
	if (r != NULL) {
		posOrder(r->lc);
		posOrder(r->rc);
		printf("%c ", r->value);
	}
}

/**
 * Metodo que imprime as folhas (valores inteiros) em conjunto
 * com seus respectivos pais (operadores)
 *
 * @param r Nó de referência
 */
void whoLeaf(Node *r) {
	if (r == NULL)
		return;
	if (r->lc == NULL && r->rc == NULL) {
		printf("%c(%c) ", r->value, r->p->value);
		return;
	}

	whoLeaf(r->lc);
	whoLeaf(r->rc);
}