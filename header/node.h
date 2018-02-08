/**
 * 
 * 
 * 
 * 
 * 
 */

#ifndef NODE_H_
#define NODE_H_

#include "node.h"

class Node {
    char value; // Valor do nó 
    Node lc;    // Filho esquerdo
    Node rc;    // Filho direito 

    public:
        Node(char value); // Construtor
        ~Node();          // Destrutor
        /* Getters */ 
        char getValue();
        Node getLc();
        Node getRc();
};

#endif // NODE_H_