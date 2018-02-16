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
#include <ctype.h>

#define MAX 100

// NEW NODE
Node *new_Node(char new_value) {
	Node *novo = (Node*) malloc(sizeof(Node));
	novo->value = new_value;
	novo->p = null;
	novo->lc = null;
	novo->rc = null;

	return novo;
}

// PILHA
typedef struct Stack {
	//Node *data[100];
	Node **data;
	int size;
} Stack;

void freeStack(Stack *s) {
	free(s->data);
	free(s);
}

Stack *new_Stack() {
	Stack *stack = (Stack *) malloc(sizeof(Stack));
	stack->data = (Node **) malloc(sizeof(stack->data)*MAX);
	stack->size = 0;

	return stack;
}

Node *stack_top(Stack *s) {
	if (s->size > 0)
		return s->data[s->size-1];
	return null; //pilha vazia
}

void stack_push(Stack *s, Node *node) {
	if (s->size < MAX)
		s->data[s->size++] = node;
}

void stack_pop(Stack *s) {
	if (s->size > 0)
        s->size--;
}

// FILA
typedef struct Queue {
	//Node *data[MAX];
	Node **data;
	int size;
} Queue;

void freeQueue(Queue *q) {
	free(q->data);
	free(q);
}

Queue *new_Queue() {
	Queue *queue = (Queue *) malloc(sizeof(queue));
	queue->data = (Node **) malloc(sizeof(queue->data)*100);
	queue->size = 0;

	return queue;
}

Node *queue_front(Queue *q) {
	if (q->size > 0)
		return q->data[0];
}

void queue_push(Queue *q, Node* node) {
	if (q->size < MAX)
		q->data[q->size++] = node;
}

void queue_pop(Queue *q) {
	if (q->size == 1) {
		q->size--;
	} else if (q->size > 1) {
		Node *naux1, *naux2;
		naux1 = q->data[q->size-2];
		q->data[q->size-2] = q->data[q->size-1];

		int i;
		for (i = (q->size-2); i > 0; i--) {
			naux2 = q->data[i-1];
			q->data[i-1] = naux1;
			naux1 = naux2;
		}
		q->size--;
	}
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
int isEmpty() {
    return (root == null)? 0:1;
}

/**
 * Metodo que recupera a quantidade de nós na árvore/sub-árvore
 *
 * @param r Nó de referência
 * @return Quantidade de nós na árvore/sub-árvore
 */
int qtdNodes(Node *r) {
	if (r == null)
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
	if (r == null)
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
	//stack<Node*> sNode;
	Stack *sNode = new_Stack();
	int i;
	for (i = 0; postfix[i] != '\0'; i++) {		
		Node *node = new_Node(postfix[i]);
		if (isdigit(postfix[i])) {
			stack_push(sNode, node); //sNode.push(node);
		} else {
			// filhos
			node->rc = stack_top(sNode); stack_pop(sNode);//node->rc = sNode.top(); sNode.pop();
			node->lc = stack_top(sNode); stack_pop(sNode);//node->lc = sNode.top(); sNode.pop();
			// pai
			if(node->rc != null)
                node->rc->p = node;
			if(node->lc != null)
                node->lc->p = node;

			stack_push(sNode, node); //sNode.push(node);
		}
	}
	root = stack_top(sNode);// root = sNode.top();
}

/**
 * Metodo que imprime os valores na árvore por largura/nível
 */
void printTreeInLevel() {
	//queue<Node*> fila;
	Queue *fila = new_Queue();

	int totalNodes = qtdNodes(root);
	int limit = pow(2, totalNodes) - 1;
	int nivel = 0;
	int auxNivel = 0;
	int print = 0; // print 1:true, 0:false

	queue_push(fila, root);//fila.push(root);
	auxNivel++;

	while(limit--) {
		Node *n = queue_front(fila);//fila.front();
		queue_pop(fila);//fila.pop();

		if ((int)pow(2, nivel) == auxNivel) {
			print = 1; // true
			nivel++;
		}
		auxNivel++;

		if (print && n != null) {
			printf("\nNivel %d: ", nivel-1);
			print = 0; // false
		}

		if (n != null) {
			printf("%c ", n->value);

			queue_push(fila, n->lc);//fila.push(n->lc);
			queue_push(fila, n->rc);//fila.push(n->rc);
		} else {
			queue_push(fila, null);//fila.push(NULL);
			queue_push(fila, null);//fila.push(NULL);
		}
	}
}


/**
 * Metodo que imprime os elementos da árvore em pré ordem recursivamente
 *
 * @param r Nó de referência
 */
void preOrder(Node *r) {
	if (r != null) {
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
	if (r != null) {
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
	if (r != null) {
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
	if (r == null)
		return;
	if (r->lc == null && r->rc == null && r->p != null) {
		printf("%c(%c) ", r->value, r->p->value);
		return;
	}
	whoLeaf(r->lc);
	whoLeaf(r->rc);
}
