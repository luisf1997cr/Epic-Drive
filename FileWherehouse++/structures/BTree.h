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
	BTree(int pMinimunDegree);
	virtual ~BTree();
private:
	BNode<AnyType>* root;
	int minimunDegree;

public:
	void traverse();
	BNode<AnyType>* searchNode(AnyType pKey);
	void insert(AnyType pKey);
	void remove(AnyType pKey);
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

#endif /* STRUCTURES_BTREE_H_ */
