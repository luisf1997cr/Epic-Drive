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

class BTree {
public:
	BTree(int pMinimunDegree);
	virtual ~BTree();

private:
	BNode* root;
	int minimunDegree;

public:
	void traverse();
	BNode* searchNode(int pKey);
	void insert(int pKey);
	void remove(int pKey);
};

BTree::BTree(int pMinimunDegree) {
	this->root=0;
	this->minimunDegree=pMinimunDegree;
}

BTree::~BTree() {
}

void BTree::traverse() {
	if(root != 0){
		this->root->traverse();
	}
}

BNode* BTree::searchNode(int pKey) {
	return (root==0)? 0: this->root->search(pKey);
}

void BTree::insert(int pKey) {
	 if (root == 0)
	    {
	        root = new BNode(this->minimunDegree, true);
	        root->Keys[0] = pKey;
	        root->nKeys = 1;
	    }
	    else
	    {
	        if (root->nKeys == 2*this->minimunDegree-1)
	        {
	            // Allocate memory for new root
	            BNode *s = new BNode(this->minimunDegree, false);

	            // Make old root as child of new root
	            s->childNode[0] = root;

	            // Split the old root and move 1 key to the new root
	            s->splitChild(0, root);

	            // New root has two children now.  Decide which of the
	            // two children is going to have new key
	            int i = 0;

	            if (s->Keys[0] < pKey){
	                i++;
	            }

	            s->childNode[i]->insertNonFull(pKey);

	            // Change root
	            root = s;
	        }
	        else  // If root is not full, call insertNonFull for root
	            root->insertNonFull(pKey);
	    }
}

void BTree::remove(int pKey) {
	 if (!root){
	        cout << "El arbol se encuentra vacio";
	        return;
	    }

	    // Call the remove function for root
	    root->remove(pKey);

	    // If the root node has 0 keys, make its first child as the new root
	    //  if it has a child, otherwise set root as NULL
	    if (root->nKeys==0)
	    {
	        BNode *tmp = root;
	        if (root->leaf){
	            root = 0;
	        }
	        else{
	            root = root->childNode[0];
	        }
	        // Free the old root
	        delete tmp;
	    }
	    return;
}

#endif /* STRUCTURES_BTREE_H_ */
