/*
 * postfix.h
 *
 *  Created on: 13 de fev de 2018
 *      Author: Anyone
 */

#ifndef POSTFIX_H_
#define POSTFIX_H_

#include <string>

using namespace std;

class Postfix {
	public:
		string postf;
		Postfix();
		virtual ~Postfix();
		void create(char* inFix);
		int preced(char value);
};

#endif /* POSTFIX_H_ */
