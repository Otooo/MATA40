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
#include <ctype.h>

#define MAX 100

int preced(char value);
void *create(char* inFix, char* pf);
int LinesFile(char *fileName);
void readFileLine(char* fileName, int cline, char *line);

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
	stack->size = 0;

	return stack;
}

char stackchar_top(StackChar s) {
	if (s.size > 0)
		return s.data[s.size-1];

	return ' '; //pilha de char vazia
}

void stackchar_push(StackChar s, char ln) {
	if (s.size < MAX)
		s.data[s.size++] = ln;
    // pilha de char cheia
}

void stackchar_pop(StackChar s) {
	if (s.size == 0)
		;//Pilha vazia
	else
		s.size--;
}


void *create(char* inFix, char* pf) {
	StackChar sOps;//stack<char> sOps;
	sOps.size = 0;
	//char postf[100]; // string postf="";
	int count = 0;
	int i;
	for (i = 0; inFix[i] != '\0'; i++) {
		if (isdigit(inFix[i])) { //funcao da biblioteca ctype.h para verificar se um caractere eh um digito
            pf[count] = inFix[i]; count++;//postf += inFix[i];
            printf("\n>: %s", pf);
		} else {
			switch(inFix[i]) {
				case '(': stackchar_push(sOps, inFix[i]);//sOps.push(inFix[i]);
					break;
				case ')':
					//while ( !sOps.empty() && (sOps.top() != '(') ) {
					while ( (stackchar_top(sOps) != ' ') && (stackchar_top(sOps) != '(') ) {
                printf("\n>>: %c", inFix[i]);
						pf[count] = stackchar_top(sOps); count++;//postf += sOps.top();
						stackchar_pop(sOps); //sOps.pop();
					}

					//if ( !sOps.empty() && (sOps.top() == '(') )
					if ( (stackchar_top(sOps) != ' ') && (stackchar_top(sOps) == '(') )
						stackchar_pop(sOps); //sOps.pop();
					break;

				default: // +, -, *, /
					if (stackchar_top(sOps) != ' ') { //if (!sOps.empty()) {
						if (preced(inFix[i]) > preced(stackchar_top(sOps)/*sOps.top()*/)) {
							stackchar_push(sOps, inFix[i]);//sOps.push(inFix[i
						} else {
							//while( !sOps.empty() && (preced(inFix[i]) <= preced(sOps.top())) && (sOps.top() != '(') ) {
							while( (stackchar_top(sOps) != ' ') && (preced(inFix[i]) <= preced(stackchar_top(sOps))) && (stackchar_top(sOps) == '(') ) {
								if (stackchar_top(sOps) == ')') //if (sOps.top() != ')')
                                                    printf("\n>>>: %c", inFix[i]);
									pf[count] = stackchar_top(sOps); count++;//postf += sOps.top();
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
	while (stackchar_top(sOps) != ' ') {//while (!sOps.empty()) {
		if (stackchar_top(sOps) == ')') //if (sOps.top() != ')')
            printf("\n>>>>: %c", inFix[i]);
			pf[count] = stackchar_top(sOps); count++;//postf += sOps.top();

		stackchar_pop(sOps); //sOps.pop();
	}
	printf("\n>>>>>>>>>>>>>>>>>>%s\n", pf);
	//return postf;
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

/*char *getPostf(){
	return postf;
}*/


/**
 *  Metodo de calculo da expressao aritmetica atraves da iterecao da arvore binaria
 */
float resolutionTree(Node *node) {
	if (node == null)
		return 0;
	if (node->lc == null && node->rc == null)
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

int LinesFile(char *fileName) {
	char ch;
	int count = 0;
	FILE *arq;

	arq = fopen(fileName, "r");
	if(arq != null) {
		while( (ch=fgetc(arq))!= EOF ) {
			if(ch == '\n')
			  count++;
		}
	}

	fclose(arq);

	return count+1;
}


void readFileLine(char* fileName, int cline, char *line) {
	char ch;
	FILE *arq;
	int countIndex = 0;
	int countLine = 1;

	arq = fopen(fileName, "r");
	if(arq != null) {
		while( (ch = fgetc(arq))!= EOF ) {
			if(ch == '\n') {
				line[countIndex++] = '\0';
				countLine++;
			}
			if (countLine > cline) {
				break;
			} else if (countLine == cline) {
				line[countIndex++] = ch;
			}
		}
	}

	fclose(arq);
}

/**
 * metodo principal de execucao
 */
int main(int argc, char **argv) {
	char *fileName = (argc <= 1)? "entrada.txt" : argv[1]; // ele executa passando o nome do arquivo se for compilar na mão, ou pega o padrão se for de outro jeito
	int qtdLines = LinesFile(fileName);
	int currentLine = 1;
	char line[100];

	int caso = 1;
	char pf[100];
	for (; currentLine <= qtdLines; currentLine++) {
		readFileLine(fileName, currentLine, line);

		// Zerar root; talvez
		char inFix[strlen(line)];
		int countInfix = 0;
		int i;
		for (i = 0; line[i] != '\0'; i++) {
			if (line[i] != ' ') {
				inFix[countInfix] = line[i]; countInfix++;
			}
		}
		// Criação da expressão pós-fixada
		create((char *) inFix, "8 - 2*3");

		// Criação da árvore
		createByPostfix("832*-"); //createByPostfix((char *) pf);

		printf("Caso %d:", caso);
		printf("\nPre-Ordem: ");       preOrder(getRoot());
		printf("\nOrdem Simetrica: "); inOrder(getRoot());
		printf("\nPos-Ordem: ");       posOrder(getRoot());
		printTreeInLevel();
		printf("\nAltura: %d",         height(getRoot()));
		printf("\nFolhas: ");          whoLeaf(getRoot());
		printf("\nResultado: %.f", resolutionTree(getRoot()));
		printf("\n\n");

		caso++;
	 } // end For lines

    return 0;
}
