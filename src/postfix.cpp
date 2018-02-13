/*
 * postfix.cpp
 *
 *  Created on: 13 de fev de 2018
 *      Author:
 */

#include "postfix.h"
#include <stack>
#include <ctype.h>
#include <string>

#include <stdio.h>

using namespace std;

Postfix::Postfix() {
	// TODO Auto-generated constructor stub

}

Postfix::~Postfix() {
	// TODO Auto-generated destructor stub
}

/*
* metodo para criacao da sequencia pos-ordem, posteriormente utilizada pra criacao da arvore
* 
* @param inFix Sequencia da expressao aritmetic
*/

void Postfix::create(char* inFix){
	stack<char> sOps;
	postf = "";

	for (int i = 0; inFix[i] != '\0'; i++) {
		if (isdigit(inFix[i])) {
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
		//	count++;
	}

	//postfix = (char *) postf.c_str();
	//printf("%s\n", inFix);
	//printf("%s\n", postfix);
}

/*
* metodo de ordem de precedencia dos operadores e parenteses
* 
* @param value Caractere de operador/parentese
* @return Valor de precedencia 
*/

int Postfix::preced(char value) {
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
