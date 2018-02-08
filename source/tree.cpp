#include <stdio.h>
#include <stdlib.h>        

using namespace Node; // Tambem não sei se funciona

/**
 * Construtor 
 */
Tree::Tree() {
    root = NULL;
}

/**
 * Destrutor 
 */
Tree::~Tree() {
    free(root); // liberar raiz ou algo do tipo.. talvez liberar todos
}

/**
 * 
 * @param
 */
Node Tree::getRoot() {
    return root;
}

/**
 * 
 */
bool Tree::isEmpty() {
    return (root == NULL);
}

/**
 * 
 * @param
 */
int Tree::height(Node root) {

}

/**
 * 
 * @param
 */
void Tree::insert(char new_value) {
    Node new_node = new Node(new_value);
    if (root == NULL) {
        root = new_node;
    } else {

    }
}

/**
 * 
 */
void Tree::printTree() {

}

/**
 * 
 */
void Tree::preOrder() {}

/**
 * 
 */
void Tree::inOrder() {}

/**
 * 
 */
void Tree::posOrder() {}

/**
 * 
 * @param
 */
Node Tree::whoFather(Node node) {
    Node p = NULL;
    Node c = root;
    while (c != NULL) {
        if (c == node)
            return p;
        p = c;
        // c = //esquerda ou direita // Decidir pra qual lado vai    
    }
    return NULL;
}

/**
 * 
 */
void Tree::whoLeaf() {} // Talvez retornar alguma coisa    