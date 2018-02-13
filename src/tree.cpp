//============================================================================
// Name        : MATA40.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description :  Ansi-style
//============================================================================

#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <math.h>
#include <stack>
#include <ctype.h>

using namespace std;

/**
 * Construtor
 */
Tree::Tree() {
    root = NULL;
}

/**
 * Destrutor
 */
Tree::~Tree() {
	// Serve pra nada ainda
}

/**
 * Metodo que recupera o nó raiz da árvore
 *
 * @return O nó raiz da árvore
 */
Node *Tree::getRoot() {
    return root;
}

/**
 * Metodo que verifica se a árvore está vazia ou não
 *
 * @return Verdadeiro se a árvore estiver vazia, falso caso contrário
 */
bool Tree::isEmpty() {
    return (root == NULL);
}

/**
 * Metodo que recupera a quantidade de nós na árvore/sub-árvore
 *
 * @param r Nó de referência
 * @return Quantidade de nós na árvore/sub-árvore
 */
int Tree::qtdNodes(Node *r) {
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
int Tree::height(Node *r) {
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
void Tree::createByPostfix(char* postfix) {
	stack<Node*> sNode;

	for (int i=0; postfix[i] != '\0'; i++) {
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
void Tree::printTreeInLevel() {
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
void Tree::preOrder(Node *r) {
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
void Tree::inOrder(Node *r) {
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
void Tree::posOrder(Node *r) {
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
void Tree::whoLeaf(Node *r) {
	if (r == NULL)
		return;
	if (r->lc == NULL && r->rc == NULL) {
		printf("%c(%c) ", r->value, r->p->value);
		return;
	}

	whoLeaf(r->lc);
	whoLeaf(r->rc);
}