/*
 * BNode.h
 *
 *  Created on: 7 de jun. de 2016
 *      Author: acacia
 */

using namespace std;
#ifndef STRUCTURES_BNODE_H_
#define STRUCTURES_BNODE_H_
template<class AnyType>
class BNode {
public:
	BNode(int pMinimunDegree, bool pLeaf);
	virtual ~BNode();

private:
	AnyType* Keys; //Arreglo de llaves
	int minimunDegree; //Dato minimo del arreglo
	BNode<AnyType> **childNode; //Puntero a los arrays hijos
	int nKeys; //Numero de llaves de cada elemento
	bool leaf; //Define si el arrreglo es una hoja

public:
	void insertNonFull(AnyType pkey);
	void splitChild(int pNumber, BNode<AnyType> *child);
	void traverse();
	BNode<AnyType>* search(AnyType pKey);
	int findKey(AnyType pkey);
	void remove(AnyType pKey);
	void removeFromLeaf(int pIndexPosition);
	void removeFromNonLeaf(int pIndexPosition);
	int getPredecessorKey(int pIndexPosition);
	int getSuccesorKey(int pIndexPosition);
	void fill(int pIndexPosition);
	void borrowFromPrev(int pIndexPosition);
	void borrowFromNext(int pIndexPosition);
	void merge(int pIndexPosition);
	void setKey(int position,AnyType pKey);
	AnyType getKey(int position);
	void setMinimunDegree(int pMinimun);
	int getMinimunDegree();
	void setChildNode(BNode<AnyType> *pChild,int position);
	BNode<AnyType>* getChildNode(int position);
	void setNumberKeys(int pNumber);
	int getNumberKeys();
	bool isLeaf();
	void setLeaf(bool pLeaf);


};
template<class AnyType>
BNode<AnyType>::BNode(int pMinimunDegree, bool pLeaf) {
	this->minimunDegree=pMinimunDegree;
	this->leaf=pLeaf;

	this->Keys= new AnyType[2*minimunDegree-1];
	this->childNode = new BNode<AnyType> *[2*minimunDegree];

	this->nKeys=0;
}

template<class AnyType>
BNode<AnyType>::~BNode() {
}

template<class AnyType>
void BNode<AnyType>::insertNonFull(AnyType pkey) {
	int i = this->nKeys-1;

    // If this is a leaf node
    if (this->leaf == true)
    {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while (i >= 0 && this->Keys[i] > pkey)
        {
            this->Keys[i+1] = this->Keys[i];
            i--;
        }

        // Insert the new key at found location
        this->Keys[i+1] = pkey;
        this->nKeys = this->nKeys+1;
    }
    else // If this node is not leaf
    {
        // Find the child which is going to have the new key
        while (i >= 0 && this->Keys[i] > pkey){
            i--;
        }

        // See if the found child is full
        if (this->childNode[i+1]->nKeys == 2*this->minimunDegree-1)
        {
            // If the child is full, then split it
            splitChild(i+1, this->childNode[i+1]);

            // After split, the middle key of C[i] goes up and
            // C[i] is splitted into two.  See which of the two
            // is going to have the new key
            if (this->Keys[i+1] < pkey){
                i++;
            }
        }
        this->childNode[i+1]->insertNonFull(pkey);
    }
}

template<class AnyType>
void BNode<AnyType>::splitChild(int pNumber, BNode<AnyType>* child) {

	// Create a new node which is going to store (t-1) keys
	// of y
	BNode<AnyType> *tmp = new BNode<AnyType>(child->minimunDegree, child->leaf);
	tmp->nKeys = this->minimunDegree - 1;

	// Copy the last (t-1) keys of y to z
	for (int j = 0; j < this->minimunDegree-1; j++){
		tmp->Keys[j] = child->Keys[j+this->minimunDegree];
	}

	// Copy the last t children of y to z
	if (child->leaf == false)
	{
		for (int j = 0; j < this->minimunDegree; j++){
			tmp->childNode[j] = child->childNode[j+this->minimunDegree];
		}
	}

	// Reduce the number of keys in y
	child->nKeys = this->minimunDegree - 1;

	// Since this node is going to have a new child,
	// create space of new child
	for (int j = this->nKeys; j >= pNumber+1; j--){
		this->childNode[j+1] = this->childNode[j];
	}
	// Link the new child to this node
	this->childNode[pNumber+1] = tmp;

	// A key of y will move to this node. Find location of
	// new key and move all greater keys one space ahead
	for (int j = this->nKeys-1; j >= pNumber; j--){
		this->Keys[j+1] = this->Keys[j];
	}
	// Copy the middle key of y to this node
	this->Keys[pNumber] = child->Keys[this->minimunDegree-1];

	// Increment count of keys in this node
	this->nKeys = this->nKeys + 1;
}

template<class AnyType>
void BNode<AnyType>::traverse() {
	// There are n keys and n+1 children, travers through n keys
	// and first n children
	int i;
	for (i = 0; i < this->nKeys; i++)
	{
		// If this is not leaf, then before printing key[i],
		// traverse the subtree rooted with child C[i].
		if (this->leaf == false)
			this->childNode[i]->traverse();
		cout << " " << this->Keys[i];
	}

	// Print the subtree rooted with last child
	if (leaf == false){
		this->childNode[i]->traverse();
	}
}

template<class AnyType>
BNode<AnyType>* BNode<AnyType>::search(AnyType pKey) {
	// Find the first key greater than or equal to k
	    int i = 0;
	    while (i < this->nKeys && pKey > this->Keys[i]){
	        i++;
	    }
	    // If the found key is equal to k, return this node
	    if (this->Keys[i] == pKey){
	        return this;
	    }
	    // If key is not found here and this is a leaf node
	    if (this->leaf == true){
	        return 0;
	    }
	    // Go to the appropriate child
	    return this->childNode[i]->search(pKey);
}

template<class AnyType>
int BNode<AnyType>::findKey(AnyType pkey) {

	int indexNumber=0;
	while(indexNumber<this->nKeys && this->Keys[indexNumber]<pkey){
		++indexNumber;
	}
	return indexNumber;
}

template<class AnyType>
void BNode<AnyType>::remove(AnyType pKey) {

	int indexNumber = findKey(pKey);

	if(indexNumber<this->nKeys && this->Keys[indexNumber]==pKey){
		if(this->leaf){
			removeFromLeaf(indexNumber);
		}else{
			removeFromNonLeaf(indexNumber);
		}
	}else{

		if(this->leaf){
			cout<<"No se encontro el valor en el arbol:"<< pKey <<endl;
			return;
		}

		bool flag = ((indexNumber==this->nKeys)? true: false);

		if(this->childNode[indexNumber]->nKeys<this->minimunDegree){
			fill(indexNumber);
		}

		if(flag && indexNumber>this->nKeys){
			childNode[indexNumber-1]->remove(pKey);
		}else{
			childNode[indexNumber]->remove(pKey);
		}
	}
	return;
}

template<class AnyType>
void BNode<AnyType>::removeFromLeaf(int pIndexPosition) {

	for(int i=pIndexPosition+1;i<this->nKeys;++i){
		Keys[i-1]=Keys[i];
	}

	nKeys--;
}

template<class AnyType>
void BNode<AnyType>::removeFromNonLeaf(int pIndexPosition) {
	int key = this->Keys[pIndexPosition];

	if(childNode[pIndexPosition]->nKeys>=this->minimunDegree){
		int pred = getPredecessorKey(pIndexPosition);
		Keys[pIndexPosition] = pred;
		childNode[pIndexPosition]->remove(pred);
	}

	else if(childNode[pIndexPosition+1]->nKeys>=this->minimunDegree){
		int succ = getSuccesorKey(pIndexPosition);
		Keys[pIndexPosition]=succ;
		childNode[pIndexPosition+1]->remove(succ);
	}

	else{
		merge(pIndexPosition);
		childNode[pIndexPosition+1]->remove(key);
	}
}

template<class AnyType>
int BNode<AnyType>::getPredecessorKey(int pIndexPosition) {

	BNode<AnyType>* curNode=childNode[pIndexPosition];
	while(!curNode->leaf){
		curNode = curNode->childNode[curNode->nKeys];
	}
	return curNode->Keys[curNode->nKeys-1];
}

template<class AnyType>
int BNode<AnyType>::getSuccesorKey(int pIndexPosition) {
	BNode<AnyType>* curNode=childNode[pIndexPosition+1];
	while(!curNode->leaf){
		curNode = curNode->childNode[0];
	}
	return curNode->Keys[0];
}

template<class AnyType>
void BNode<AnyType>::fill(int pIndexPosition) {

	if(pIndexPosition!=0 && childNode[pIndexPosition-1]->nKeys>=this->minimunDegree){
		borrowFromPrev(pIndexPosition);
	}

	else if(pIndexPosition!=nKeys && childNode[pIndexPosition+1]->nKeys>=this->minimunDegree){
		borrowFromNext(pIndexPosition);
	}

	else{
		if(pIndexPosition!=nKeys){
			merge(pIndexPosition);
		}else{
			merge(pIndexPosition-1);
		}
	}
}

template<class AnyType>
void BNode<AnyType>::borrowFromPrev(int pIndexPosition) {
	BNode<AnyType>* child=childNode[pIndexPosition];
	BNode<AnyType>* sibling= childNode[pIndexPosition-1];

	for(int i=child->nKeys-1;i>=0;--i){
		child->Keys[i+1] = child->Keys[i];
	}
	if(!child->leaf){
		for(int i=child->nKeys;i>=0;--i){
				child->childNode[i+1] = child->childNode[i];
			}
	}
	child->Keys[0] = this->Keys[pIndexPosition-1];

	if(!leaf){
		child->childNode[0] = sibling->childNode[sibling->nKeys];
	}
	this->Keys[pIndexPosition-1]=sibling->Keys[sibling->nKeys-1];

	child->nKeys += 1;
	sibling->Keys -=1;

	return;
}

template<class AnyType>
void BNode<AnyType>::borrowFromNext(int pIndexPosition) {

	BNode<AnyType>* child=childNode[pIndexPosition];
	BNode<AnyType>* sibling= childNode[pIndexPosition+1];

	child->Keys[child->nKeys]=this->Keys[pIndexPosition];

	if(!(child->leaf)){
		child->childNode[(child->nKeys)+1]=sibling->childNode[0];
	}

	this->Keys[pIndexPosition]=sibling->Keys[0];

	for(int i=1;i<sibling->nKeys;++i){
		sibling->Keys[i-1] = sibling->Keys[i];
	}

	if(!sibling->leaf){
		for(int i=1;i<=sibling->nKeys;++i){
				sibling->childNode[i-1] = sibling->childNode[i];
			}
	}

	child->nKeys += 1;
	sibling->Keys -=1;

	return;
}

template<class AnyType>
void BNode<AnyType>::merge(int pIndexPosition) {

	BNode<AnyType>* child=childNode[pIndexPosition];
	BNode<AnyType>* sibling= childNode[pIndexPosition+1];

	child->Keys[this->minimunDegree-1]=this->Keys[pIndexPosition];

	for(int i=0;i<sibling->nKeys;++i){
		child->Keys[i+this->minimunDegree] = sibling->Keys[i];
	}

	if(!child->leaf){
		for(int i=0;i<sibling->nKeys;++i){
			child->childNode[i+this->minimunDegree] = sibling->childNode[i];
		}
	}

	for(int i=pIndexPosition+1;i<this->nKeys;++i){
		this->Keys[i-1]=this->Keys[i];
	}

	for(int i=pIndexPosition+2;i<=this->nKeys;++i){
		this->childNode[i-1]=this->childNode[i];
	}

	child->nKeys += sibling->nKeys+1;
	this->nKeys-=1;

	delete(sibling);
	return;
}

template<class AnyType>
void BNode<AnyType>::setLeaf(bool pLeaf){
	this->leaf = pLeaf;
}

template<class AnyType>
bool BNode<AnyType>::isLeaf(){
	return(this->leaf);
}

template<class AnyType>
void BNode<AnyType>::setChildNode(BNode<AnyType>* pChildNode,int position){
	this->childNode[position] = pChildNode;
}

template<class AnyType>
BNode<AnyType>* BNode<AnyType>::getChildNode(int position){
	return (this->childNode[position]);
}

template<class AnyType>
void BNode<AnyType>::setKey(int position,AnyType pKeys){
	this->Keys[position]=pKeys;
}

template<class AnyType>
AnyType BNode<AnyType>::getKey(int position){
	return(this->Keys[position]);
}

template<class AnyType>
void BNode<AnyType>::setMinimunDegree(int pMinimun){
	this->minimunDegree=pMinimun;
}

template<class AnyType>
int BNode<AnyType>::getMinimunDegree(){
	return (this->minimunDegree);
}

template<class AnyType>
int BNode<AnyType>::getNumberKeys(){
	return this->nKeys;
}

template<class AnyType>
void BNode<AnyType>::setNumberKeys(int pNumber){
	this->nKeys=pNumber;
}

#endif /* STRUCTURES_BNODE_H_ */
