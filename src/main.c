//============================================================================
// Name        : MATA40.c
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Ansi-style
//============================================================================

#include "structurefunctions.h"
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <ctype.h>

#define MAX 100

int preced(char value);
void create(char* inFix);

typedef struct StackChar {
	char data[MAX];
	int size;
} StackChar;

//acho que não precisa
void freeStackChar(StackChar *s) {
	free(s->data);
	free(s);
}

// acho que não precisa
StackChar *new_StackChar() {
	StackChar *stack = malloc(sizeof(StackChar));
	stack->data = malloc(sizeof(stack->data)*100);
	stack->size = 0;

	return stack;
}

char stackchar_top(StackChar s) {
	if (s.size > 0)
		return s.data[s.size-1];

	return ''; //pilha de char vazia
}

void stackchar_push(StackChar s, char ln) {
	if (s.size < MAX)
		s.data[s.size++] = ln;
	else
		;// pilha de char cheia
}

void stackchar_pop(StackChar s) {
	if (s.size == 0)
		;//Pilha vazia
	else
		s.size--;
}


void create(char* inFix){
	StackChar sOps;//stack<char> sOps;
	char postf[100]; // string postf="";
	int count=0;
	int i;
	for (i = 0; inFix[i] != '\0'; i++) {
		if (isdigit(inFix[i])) { //funcao da biblioteca ctype.h para verificar se um caractere eh um digito
			postf[count] = inFix[i]; count++;//postf += inFix[i];
		} else {
			switch(inFix[i]) {
				case '(': stackchar_push(sOps, inFix[i]);//sOps.push(inFix[i]);
					break;
				case ')':
					//while ( !sOps.empty() && (sOps.top() != '(') ) {
					while ( (stackchar_top(sOps) != '') && (stackchar_top(sOps) != '(') ) {
						postf[count] = stackchar_top(sOps); count++;//postf += sOps.top();
						stackchar_pop(sOps); //sOps.pop();
					}

					//if ( !sOps.empty() && (sOps.top() == '(') )
					if ( (stackchar_top(sOps) != '') && (stackchar_top(sOps) == '(') ) {
						stackchar_pop(sOps); //sOps.pop();

					break;
				default: // +, -, *, /
					if (stackchar_top(sOps) != '') {//if (!sOps.empty()) {
						if (preced(inFix[i]) > preced(stackchar_top(sOps)/*sOps.top()*/)) {
							stackchar_push(sOps, inFix[i]);//sOps.push(inFix[i]);
						} else {
							//while( !sOps.empty() && (preced(inFix[i]) <= preced(sOps.top())) && (sOps.top() != '(') ) {
							while( (stackchar_top(sOps) != '') && (preced(inFix[i]) <= preced(stackchar_top(sOps))) && (stackchar_top(sOps) == '(') ) {
								if (stackchar_top(sOps) == ')') //if (sOps.top() != ')')
									postf[count] = stackchar_top(sOps); count++;//postf += sOps.top();
								stackchar_pop(sOps); //sOps.pop();
							}
							stackchar_push(sOps, inFix[i]);//sOps.push(inFix[i]);
						}
					} else {
						stackchar_push(sOps, inFix[i]); //sOps.push(inFix[i]);
					}

					break;
			}
		}
	}
	// Inserir os ultimos operadores
	while (stackchar_top(sOps) != '') {//while (!sOps.empty()) {
		if (stackchar_top(sOps) == ')') //if (sOps.top() != ')')
			postf[count] = stackchar_top(sOps); count++;//postf += sOps.top();
		stackchar_pop(sOps); //sOps.pop();
	}
}

/*
* metodo de ordem de precedencia dos operadores e parenteses
* 
* @param value Caractere de operador/parentese
* @return Valor de precedencia 
*/

int preced(char value) {
	switch(value) {
		case '(':
		case ')': return 2;

		case '*':
		case '/': return 1;

		case '+':
		case '-': return 0;
	}
	return 0;
}

char *getPostf(){
	return postf;
}

/**
 *  Metodo de calculo da expressao aritmetica atraves da iterecao da arvore binaria
 */
float resolutionTree(Node *node) {
	if (node == NULL)
		return 0;
	if (node->lc == NULL && node->rc == NULL)
		return node->value - '0'; // Convertendo de Char para Numero

	switch (node->value) {
		case '+': return resolutionTree(node->lc) + resolutionTree(node->rc);
			break;
		case '-': return resolutionTree(node->lc) - resolutionTree(node->rc);
			break;
		case '*': return resolutionTree(node->lc) * resolutionTree(node->rc);
			break;
		case '/': return resolutionTree(node->lc) / resolutionTree(node->rc);
			break;
	}

	return 0;
}

/**
 * metodo principal de execucao 
 */
int main() {
	ifstream file("../entrada.txt");
	char line[100];
	int caso = 1;
	char pf[100];
	pf = getPostf();
	if (file.is_open()) {
		while (!file.eof()) {
			file.getline(line, 100);
			char inFix[100];
			int i;
			for (i = 0; line[i] != '\0'; i++) {
				if (line[i] != ' ')
					infix[]
					inFix += line[i];
			}
			create((char *) inFix);
			
			createByPostfix((char *) pf);

			printf("Caso %d:", caso);
			printf("\nPré-Ordem: ");       preOrder(getRoot());
			printf("\nOrdem Simétrica: "); inOrder(getRoot());
			printf("\nPós-Ordem: ");       posOrder(getRoot());
			printTreeInLevel();
			printf("\nAltura: %d",         height(getRoot()));
			printf("\nFolhas: ");          whoLeaf(getRoot());
			printf("\nResultado: %.f", resolutionTree(getRoot()));
			printf("\n\n");



			caso++;
		}
	}
    return 0;
}
