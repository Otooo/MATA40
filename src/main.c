//============================================================================
// Name        : MATA40.cpp
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

int preced(char value);
void create(char* inFix);

void create(char* inFix){
	stack<char> sOps;
	string postf = "";
	int i;
	for (i = 0; inFix[i] != '\0'; i++) {
		if (isdigit(inFix[i])) { //funcao da biblioteca ctype.h para verificar se um caractere eh um digito
			postf[i] = sOps.top().pop();
			postf += inFix[i];
		} else {
			switch(inFix[i]) {
				case '(': sOps.push(inFix[i]); break;
				case ')':
					while ( !sOps.empty() && (sOps.top() != '(') ) {
						postf += sOps.top();
						sOps.pop();
					}

					if ( !sOps.empty() && (sOps.top() == '(') )
						sOps.pop();

					break;
				default: // +, -, *, /
					if (!sOps.empty()) {
						if (preced(inFix[i]) > preced(sOps.top())) {
							sOps.push(inFix[i]);
						} else {
							while( !sOps.empty() && (preced(inFix[i]) <= preced(sOps.top())) && (sOps.top() != '(') ) {
								if (sOps.top() != ')')
									postf += sOps.top();
								sOps.pop();
							}
							sOps.push(inFix[i]);
						}
					} else {
						sOps.push(inFix[i]);
					}

					break;
			}
		}
	}
	// Inserir os ultimos operadores
	while (!sOps.empty()) {
		if (sOps.top() != ')')
			postf += sOps.top();
		sOps.pop();
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

string getPostf(){
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
