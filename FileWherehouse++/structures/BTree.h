/*
 * BTree.h
 *
 *  Created on: 7 de jun. de 2016
 *      Author: acacia
 */

#ifndef STRUCTURES_BTREE_H_
#define STRUCTURES_BTREE_H_
#include "BNode.h"
using namespace std;

template<class AnyType>
class BTree {
public:
	/**
	 * @brief Constructor de la clase del BTree.
	 * @param El tamano de de casillas por nodo.
	 */
	BTree(int pMinimunDegree);
	/**
	 * Destructor de la clase
	 */
	virtual ~BTree();
private:
	BNode<AnyType>* root;
	int minimunDegree;

public:
	/**
	 * @brief Metodo encargado de atravesar todo el alrbol por sus nodos y pintarlos en pantalla
	 */
	void traverse();

	/**
	 * @brief Metodo encargado de buscar una llave en el arbol
	 * @param La llave que se desea buscar
	 * @return Un puntero con la ubicacion de la llave
	 */
	BNode<AnyType>* searchNode(AnyType pKey);

	/**
	 * @brief Metodo encargado de insertar una llave en el arbol
	 * @param La llave que se desea insertar
	 */
	void insert(AnyType pKey);

	/**
	 * @brief Metodo encargado de eliminar una llave en el arbol
	 * @param La llave que se desea insertar
	 */
	void remove(AnyType pKey);

	/**
	 * Cambia el valor maximo de casillas por nodo
	 * @param el valor numerico
	 */
	void setMinimunDegree(int pNumber);

	/**
	 * @brief Metodo encargado de obtener el valor maximo de casillas por nodo
	 * @return el valor numerico
	 */
	int getMinimunDegree();
};

template<class AnyType>
BTree<AnyType>::BTree(int pMinimunDegree) {
	this->root=0;
	this->minimunDegree=pMinimunDegree;
}

template<class AnyType>
BTree<AnyType>::~BTree() {
}

template<class AnyType>
void BTree<AnyType>::traverse() {
	if(root != 0){
		this->root->traverse();
	}
}

template<class AnyType>
BNode<AnyType>* BTree<AnyType>::searchNode(AnyType pKey) {
	return (root==0)? 0: this->root->search(pKey);
}

template<class AnyType>
void BTree<AnyType>::insert(AnyType pKey) {
	 if (root == 0)
	    {
	        root = new BNode<AnyType>(this->minimunDegree, true);
	        root->setKey(0,pKey);
	        root->setNumberKeys(1);
	    }
	    else
	    {
	        if (root->getNumberKeys() == 2*this->minimunDegree-1)
	        {
	            // Allocate memory for new root
	            BNode<AnyType> *s = new BNode<AnyType>(this->minimunDegree, false);

	            // Make old root as child of new root
	            s->setChildNode(root,0);

	            // Split the old root and move 1 key to the new root
	            s->splitChild(0, root);

	            // New root has two children now.  Decide which of the
	            // two children is going to have new key
	            int i = 0;

	            if (s->getKey(0) < pKey){
	                i++;
	            }

	            s->getChildNode(i)->insertNonFull(pKey);

	            // Change root
	            root = s;
	        }
	        else  // If root is not full, call insertNonFull for root
	            root->insertNonFull(pKey);
	    }
}

template<class AnyType>
void BTree<AnyType>::remove(AnyType pKey) {
	 if (!root){
	        cout << "El arbol se encuentra vacio";
	        return;
	    }

	    // Call the remove function for root
	    root->remove(pKey);

	    // If the root node has 0 keys, make its first child as the new root
	    //  if it has a child, otherwise set root as NULL
	    if (root->getNumberKeys()==0)
	    {
	        BNode<AnyType> *tmp = root;
	        if (root->isLeaf()){
	            root = 0;
	        }
	        else{
	            root = root->getChildNode(0);
	        }
	        // Free the old root
	        delete tmp;
	    }
	    return;
}

template<class AnyType>
void BTree<AnyType>::setMinimunDegree(int pNumber){
	this->minimunDegree=pNumber;
}

template<class AnyType>
int BTree<AnyType>::getMinimunDegree(){
	return(this->minimunDegree);
}

#endif /* STRUCTURES_BTREE_H_ */
