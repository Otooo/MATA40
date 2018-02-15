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
char *create(char* inFix);
int LinesFile(char *fileName);
char *readFileLine(char* fileName, int line);

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
	else
		;// pilha de char cheia
}

void stackchar_pop(StackChar s) {
	if (s.size == 0)
		;//Pilha vazia
	else
		s.size--;
}


char *create(char* inFix) {
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
					while ( (stackchar_top(sOps) != ' ') && (stackchar_top(sOps) != '(') ) {
						postf[count] = stackchar_top(sOps); count++;//postf += sOps.top();
						stackchar_pop(sOps); //sOps.pop();
					}

					//if ( !sOps.empty() && (sOps.top() == '(') )
					if ( (stackchar_top(sOps) != ' ') && (stackchar_top(sOps) == '(') )
						stackchar_pop(sOps); //sOps.pop();
					break;

				default: // +, -, *, /
					if (stackchar_top(sOps) != ' ') { //if (!sOps.empty()) {
						if (preced(inFix[i]) > preced(stackchar_top(sOps)/*sOps.top()*/)) {
							stackchar_push(sOps, inFix[i]);//sOps.push(inFix[i]);
						} else {
							//while( !sOps.empty() && (preced(inFix[i]) <= preced(sOps.top())) && (sOps.top() != '(') ) {
							while( (stackchar_top(sOps) != ' ') && (preced(inFix[i]) <= preced(stackchar_top(sOps))) && (stackchar_top(sOps) == '(') ) {
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
	while (stackchar_top(sOps) != ' ') {//while (!sOps.empty()) {
		if (stackchar_top(sOps) == ')') //if (sOps.top() != ')')
			postf[count] = stackchar_top(sOps); count++;//postf += sOps.top();
		stackchar_pop(sOps); //sOps.pop();
	}

	return postf;
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

int LinesFile(char *fileName) {
	char ch;
	int count = 0;
	FILE *arq;

	arq = fopen(fileName, "r");
	if(arq != NULL) {
		while( (ch=fgetc(arq))!= EOF ) {
			if(ch == '\n')
			  count++;
		}
	}

	fclose(arq);

	return count+1;
}


char *readFileLine(char* fileName, int line) {
	char ch;
	char *retorno;
	FILE *arq;
	int countIndex = 0;
	int countLine = 1;

	arq = fopen(fileName, "r");
	if(arq != NULL) {
		while( (ch=fgetc(arq))!= EOF ) {
			printf("%c");
			if(ch == '\n')
				countLine++;
			if (countLine > line) {
				break;
			} else if (countLine == line) {

				//retorno = (char *) realloc(retorno, sizeof(char)*(++countIndex));
				//retorno[countIndex-1] = ch;
			}
		}
	}
	printf("\neita III");
	fclose(arq);
	return retorno;
}

/**
 * metodo principal de execucao 
 */
int main(int argc, char **argv) {
	//ifstream file(argv[1]); // melhor assim, ele executa e passa o nome do arquivo, dai pega do local onde ta o executavel (pra projeto ou pra compilação na mão)
	//char line[100] = ;
	char *fileName = (argc <= 1)? "entrada.txt" : argv[1]; // ele executa passando o nome do arquivo se for compilar na mão, ou pega o padrão se for de outro jeito
	int qtdLines = LinesFile(fileName);
	printf("\nLINHAS: %d\n", qtdLines);
	int currentLine = 1;
	char *line;

	int caso = 1;
	//char pf[100];
	char *pf;// = getPostf();
	//if (file.is_open()) {
		//while (!file.eof()) {
		for (; currentLine <= qtdLines; currentLine++) {
			//file.getline(line, 100);
			line = readFileLine(fileName, currentLine);
			// Zerar root; talvez
			char inFix[strlen(line)];
			int countInfix = 0;
			int i;
			for (i = 0; line[i] != '\0'; i++) {
				if (line[i] != ' ') {
					inFix[countInfix] = line[i]; countInfix++;
					//inFix += line[i];
				}
			}
			// Ciração da expressão pós-fixada
			pf = create((char *) inFix);
			
			// Criação da árvore
			createByPostfix(pf); //createByPostfix((char *) pf);

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
		 } // end For lines
		//} //end while file EOF
	//} //end if File
    return 0;
}
