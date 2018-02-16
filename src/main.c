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
void create(char *inFix, char *pf);
int LinesFile(char *fileName);
void readFileLine(char* fileName, int cline, char *line);
int isPermitted(char ch);
int isOperator(char ch);

typedef struct StackChar {
	char data[MAX];
	int size;
} StackChar;

//acho que não precisa
void freeStackChar(StackChar *s) {
	(*s).data[0] = '\0';
	(*s).size = 0;
}

int stackchar_isEmpty(StackChar *s) {
	return ((*s).size == 0);		
}

char stackchar_top(StackChar *s) {	
	if ((*s).size > 0)
		return (*s).data[(*s).size-1];

	return ' '; //pilha de char vazia
}

void stackchar_push(StackChar *s, char ln) {	
	if ((*s).size < MAX)
		(*s).data[(*s).size++] = ln;			
    // pilha de char cheia
}

void stackchar_pop(StackChar *s) {
	if ((*s).size == 0)
		;//Pilha vazia
	else
		(*s).size--;
}

/**
 *  
 */
void create(char *inFix, char *pf) {
	StackChar sOps;	
	sOps.size = 0;	
	int count = 0;
	int i;
	for (i = 0; inFix[i] != '\0'; i++) {		
		if (isdigit(inFix[i])) { //funcao da biblioteca ctype.h para verificar se um caractere eh um digito
            pf[count++] = inFix[i]; //postf += inFix[i];			
		} else {
			switch(inFix[i]) {
				case '(': stackchar_push(&sOps, inFix[i]);//sOps.push(inFix[i]);
					break;
				case ')':
					//while ( !sOps.empty() && (sOps.top() != '(') ) {
					while ( !stackchar_isEmpty(&sOps) && (stackchar_top(&sOps) != '(') ) {
						pf[count++] = stackchar_top(&sOps); //postf += sOps.top();
						stackchar_pop(&sOps); //sOps.pop();
					}

					//if ( !sOps.empty() && (sOps.top() == '(') )
					if ( !stackchar_isEmpty(&sOps) && (stackchar_top(&sOps) == '(') )
						stackchar_pop(&sOps); //sOps.pop();
					break;

				default: // +, -, *, /
					if (!stackchar_isEmpty(&sOps)) { //if (!sOps.empty()) {						
						if ((preced(inFix[i]) > preced(stackchar_top(&sOps))) || (stackchar_top(&sOps) == '(') )/*sOps.top()*/ {
							stackchar_push(&sOps, inFix[i]);//sOps.push(inFix[i])					
						} else {
							//while( !sOps.empty() && (preced(inFix[i]) <= preced(sOps.top())) && (sOps.top() != '(') ) {
							while( !stackchar_isEmpty(&sOps) && (preced(inFix[i]) <= preced(stackchar_top(&sOps)))) {
								if (stackchar_top(&sOps) != ')') //if (sOps.top() != ')')
									pf[count++] = stackchar_top(&sOps);//postf += sOps.top();
								stackchar_pop(&sOps); //sOps.pop();
							}
							stackchar_push(&sOps, inFix[i]);//sOps.push(inFix[i]);
						}
					} else {
						stackchar_push(&sOps, inFix[i]); //sOps.push(inFix[i]);
					}
					break;
			}
		}	
	}

	// Inserir os ultimos operadores
	while (!stackchar_isEmpty(&sOps)) {//while (!sOps.empty()) {
		if (stackchar_top(&sOps) != ')') { //if (sOps.top() != ')')
			pf[count++] = stackchar_top(&sOps);//postf += sOps.top();
		}
		stackchar_pop(&sOps); //sOps.pop();
	}
	pf[count++] = '\0';	
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

/**
 * 
 */
void readFileLine(char* fileName, int cline, char *line) {
	char ch;
	FILE *arq;
	int countIndex = 0;
	int countLine = 1;	

	arq = fopen(fileName, "r");
	if(arq != null) {
		while( (ch = fgetc(arq))!= EOF ) {			
			if(ch == '\n') {
				countLine++;
			}
			if (countLine > cline) {
				break;
			} else if (countLine == cline && ch != ' ' && ch != '\n') {
				line[countIndex++] = ch;				
			}
		}
	line[countIndex++] = '\0';
	}
	
	fclose(arq);
}

/**
 * metodo principal de execucao
 */
int main(int argc, char **argv) {
	char *fileName = (argc <= 1)? "entrada.txt" : argv[1]; // ele executa passando o nome do arquivo se for compilar na mão, ou pega o padrão se for de outro jeito
	int qtdLines = LinesFile(fileName);
	char line[101];	
	char pf[101];
	int caso = 1;
	for (; caso <= qtdLines; caso++) {		
		readFileLine(fileName, caso, line);			

		// Criação da expressão pós-fixada		
		create((char *) line, pf);
		
		// Criação da árvore
		createByPostfix(pf);

		// SAÍDA
		printf("Caso %d:", caso);
		printf("\nPre-Ordem: ");       preOrder(getRoot());
		printf("\nOrdem Simetrica: "); inOrder(getRoot());
		printf("\nPos-Ordem: ");       posOrder(getRoot());
		printTreeInLevel();
		printf("\nAltura: %d",         height(getRoot()));
		printf("\nFolhas: ");          whoLeaf(getRoot());
		printf("\nResultado: %.f", resolutionTree(getRoot()));
		printf("\n\n");		
	 } // end For lines

    return 0;
}
