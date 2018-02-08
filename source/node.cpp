/**
 * 
 * 
 * 
 * 
 * 
 */

#include <node.h>
#include <stdlib.h>

using namespace std;

/**
 * Construtor
 * 
 * @param
 */
Node::Node(char value) {
    this.value = value;
}

/**
 * Destrutor
 */
Node::~Node() {
    // Libera os filhos ou algo do tipo...
    free(lc); 
    free(rc);
}

/**
 * @return 
 */
char Node::getValue() {
    return value;
}

/**
 * @return 
 */
Node Node::getLc() {
    return lc;
}

/**
 * @return 
 */
Node Node::getRc() {
    return rc;
}