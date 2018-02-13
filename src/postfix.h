/*
 * postfix.h
 *
 *  Created on: 13 de fev de 2018
 *      Author:
 */

#ifndef POSTFIX_H_
#define POSTFIX_H_

#include <string>

using namespace std;

/*
* Classe Postfix e seus metodos e atributos publicos 
*/
class Postfix {
	public:
		string postf; //atributo da sequencia posordem
		Postfix(); //construtor
		virtual ~Postfix(); //destrutor
		void create(char* inFix); //cria a sequencia posordem
		int preced(char value); //retorna o valor de precedencia do caractere
};

#endif /* POSTFIX_H_ */
