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

}

/**
 *
 * @param
 */
Node *Tree::getRoot() {
    return root;
}

/**
 *
 */
bool Tree::isEmpty() {
    return (root == NULL);
}

/**
 *
 * @param r
 */
int Tree::qtdNodes(Node *r) {
	if (r == NULL)
		return 0;
	return 1 + qtdNodes(r->lc) + qtdNodes(r->rc);
}

/**
 *
 * @param
 */
int Tree::height(Node *r) {
	if (r == NULL)
		return 0;
	int lh = height(r->lc);
	int rh = height(r->rc);
	return (lh > rh)? lh+1 : rh+1;
}

/**
 *
 * @param
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
 *
 */
void Tree::printTreeInLevel() {
	queue<Node*> fila;
	int totalNodes = qtdNodes(root);
	int limit = pow(2, totalNodes) - 1;
	int nivel = 0;
	int auxNivel = 0;

	fila.push(root);
	auxNivel++;
	//!fila.empty()

	while(limit--) {
		if ((int)pow(2, nivel) == auxNivel) {
			printf("\nNivel %d: ", nivel);
			nivel++;
		}

		Node *n = fila.front();
		fila.pop();
		auxNivel++;
		if (n != NULL) {
			printf("%c ", n->value);

			fila.push(n->lc);
			fila.push(n->rc);
		} else {
			fila.push(NULL);
			fila.push(NULL);
		}
		/*if (n->lc != NULL)
			fila.push(n->lc);
		if (n->rc != NULL)
			fila.push(n->rc);
			*/

	}
}


/**
 * Imprime os elementos da árvore em pré ordem recursivamente
 *
 * @param r
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
 * @param r
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
 * @param r
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
 * @param r
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
