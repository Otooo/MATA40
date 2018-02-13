//============================================================================
// Name        : MATA40.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "tree.h"
#include "postfix.h"
#include <stdio.h>
#include <string.h>
#include <fstream>

using namespace std;


/**
 *
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
 *
 */
int main() {
	ifstream file("entrada.txt");
	char line[100];
	int caso = 1;
	Postfix pf;
	if (file.is_open()) {
		while (! file.eof()) {
			file.getline(line, 100);
			Tree tree;
			string inFix = "";
			for (int i=0; line[i] != '\0'; i++) {
				if (line[i] != ' ')
					inFix += line[i];
			}
			pf.create((char *)inFix.c_str());
			tree.createByPostfix((char *)pf.postf.c_str());

			printf("Caso %d:", caso);
			printf("\nPré-Ordem: ");       tree.preOrder(tree.getRoot());
			printf("\nOrdem Simétrica: "); tree.inOrder(tree.getRoot());
			printf("\nPós-Ordem: ");       tree.posOrder(tree.getRoot());
			tree.printTreeInLevel();
			printf("\nAltura: %d",         tree.height(tree.getRoot()));
			printf("\nFolhas: ");          tree.whoLeaf(tree.getRoot());
			printf("\nResultado: %.3f", resolutionTree(tree.getRoot()));
			printf("\n\n");



			caso++;
		}
	}
    return 0;
}
