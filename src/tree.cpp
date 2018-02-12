//============================================================================
// Name        : MATA40.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <math.h>

using namespace std;

/**
 * Construtor
 */
Tree::Tree() {
    root = NULL;
    PPosition = NULL;
    parentesesAbertos = 0;
}

/**
 * Destrutor
 */
Tree::~Tree() {
	// Serve pra nada ainda
}

/**
 * Recupera o nó raiz da árvore
 *
 * @return O nó raiz da árvore
 */
Node *Tree::getRoot() {
    return root;
}

/**
 * Verifica se a árvore está vazia ou não
 *
 * @return Verdadeiro se a árvore estiver vazia, falso caso contrário
 */
bool Tree::isEmpty() {
    return (root == NULL);
}

/**
 * Recupera a quantidade de nós na árvore/sub-árvore
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
 * Recupera a altura da árvore/sub-árvore
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
 * Insere um novo valor na árvore
 *
 * @param new_value Valor a ser inserido na árvore
 */
void Tree::insert(char new_value) {
	int isOperator = false;
	switch (new_value) {
		case '+':
		case '-':
		case '*':
		case '/': isOperator = true;
			break;
		default: isOperator = false;
			break;
	}

	if (new_value == '(') {
		parentesesAbertos++;
		return;
	} else if (new_value == ')') {
		parentesesAbertos--;
		if (PPosition != root)
			PPosition = PPosition->p;
		return;
	}

	Node *node = new Node(new_value);
    if (root == NULL) {
        root = node;
        PPosition = root;
    } else {
    	if (isOperator == true) {
    		node->p = PPosition->p;
    		node->lc = PPosition;
    		PPosition->p = node;
    		if (PPosition == root){
    			root = node;
    		}
    		PPosition = node;
    		if (PPosition->p != NULL)
    			PPosition->p->rc = node;

    	} else {
    		PPosition->rc = node;
    		node->p = PPosition;
    		if (parentesesAbertos > 1)
    			PPosition = node;
    	}
    }
}


/**
 * Imprime os valores na árvore por largura/nível
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
 * Imprime os elementos da árvore em pré ordem recursivamente
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
 * Imprime os elementos da árvore em ordem recursivamente
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
 * Imprime os elementos da árvore em pós ordem recursivamente
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
