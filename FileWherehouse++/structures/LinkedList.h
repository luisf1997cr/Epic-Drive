/**
 * @file LinkedList.h
 * @date 4/3/16
 * @title LinkedList
 * @brief Abstracion de una lista simple para el proyecto xC++2
 */

#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <string>
using namespace std;

#include "NodoSimple.h"

template<class AnyType>
class LinkedList
{
private:
    NodoSimple<AnyType> * _Head;
    int _Length;

public:
    /**
     * @brief Metodo constructor de LinkedList
     */
    LinkedList();

    /**
     * @brief Metodo inserta un nodo en la lista
     * @param NodoSimple<AnyType>* pNewItem
     */
    void insertItem( NodoSimple<AnyType> * pNewItem);

    /**
     * @breif Metodo inserta un elemento a la lista
     * @param AnyType* pItem
     */
    void insertData(AnyType* pItem);

    /**
     * @brief Metodo elimina el elemento de la lista que contenga el mismo pItemKey
     * @param string pItemKey
     */
    bool removeItem( string pItemKey );

    /**
     * @brief Metodo obtiene el elemento que contiene el mismo pItemKey
     * @param string pItemKey
     * @return NodoSimple<AnyType>*
     */
    NodoSimple<AnyType> * getItem( string pItemKey );

    void insertarOrdenadoNodo( NodoSimple<AnyType> * pNewItem);

    void insertarDatoOrdenado(AnyType* pItem);



    /**
     * @brief Metodo devuelve el nodo en la posicion
     * @param int pPosition
     * @return NodoSimple<AnyType>*
     */
    NodoSimple<AnyType> * getItemByPosition(int pPosition);

    /**
     * @brief Metodo devuelve el dato segun la clave
     * @param string pItemKey
     * @return AnyType*
     */
    AnyType* getDataItem(string pItemKey);

    /**
     * @brief Metodo imprime la lista
     */
    void printList();

    void ordenarLista();

    /**
     * @brief Metodo devuelve el atributo _Lenght
     * @return int
     */
    int getLength();

    /**
     * @brief Metodo destructor de LinkedList
     */
    ~LinkedList();
};


template<class AnyType>
LinkedList<AnyType>::LinkedList()
{
    this->_Head = new NodoSimple<AnyType>{"c",NULL,NULL};
    this->_Length = 0;
}

template <class AnyType>
void LinkedList<AnyType>::insertItem( NodoSimple<AnyType> * newItem )
{
    if (!_Head->getNext())
    {
        _Head->setNext(newItem);
        this->_Length++;
        return;
    }
    NodoSimple<AnyType> * aux1 = this->_Head;
    NodoSimple<AnyType> * aux2 = this->_Head;
    while (aux2)
    {
        aux1 = aux2;
        aux2 = aux1->getNext();
    }
    aux1->setNext(newItem);

    newItem->setNext(NULL);
    this->_Length++;
}

template <class AnyType>
void LinkedList<AnyType>::insertarOrdenadoNodo(NodoSimple<AnyType> * pNewItem)
{
	NodoSimple<AnyType> * current;
	    /* Special case for the head end */
	    if (_Head == NULL || (_Head)->_Val >= pNewItem->_Val)
	    {
	    	pNewItem->setNext(*_Head);
	    	_Head= pNewItem;
	    }
	    else
	    {
	        /* Locate the node before the point of insertion */
	        current = _Head;
	        while (current->getNext()!=NULL &&
	               current->getNext()->_Val < pNewItem->_Val)
	        {
	            current = current->getNext();
	        }
	        pNewItem->setNext(current->getNext());
	        current->setNext(pNewItem);
	    }
	    this->_Length++;
}

template<class AnyType>
void LinkedList<AnyType>::insertData(AnyType* pItem){
	NodoSimple<AnyType> *nodo = new NodoSimple<AnyType>{"c", pItem, NULL};
	insertItem(nodo);
}

template<class AnyType>
void LinkedList<AnyType>::insertarDatoOrdenado(AnyType* pItem){
	NodoSimple<AnyType> *nodo = new NodoSimple<AnyType>{"c", pItem, NULL};
	insertarOrdenadoNodo(nodo);
}

template<class AnyType>
bool LinkedList<AnyType>::removeItem( string itemKey )
{
    if (!_Head->getNext()) return false;
    NodoSimple<AnyType> * aux1 = this->_Head;
    NodoSimple<AnyType> * aux2 = this->_Head;
    while (aux2)
    {
        if (aux2->getKey() == itemKey)
        {
            aux1->setNext(aux2->getNext());
            free (aux2);
            this->_Length--;
            return true;
        }
        aux1 = aux2;
        aux2 = aux1->getNext();
    }
    return false;
}

template<class AnyType>
NodoSimple<AnyType> * LinkedList<AnyType>::getItem( string itemKey )
{
    NodoSimple<AnyType> * aux1 = this->_Head;
    NodoSimple<AnyType> * aux2 = this->_Head;
    while (aux2)
    {
        aux1 = aux2;
        if ((aux1 != this->_Head) && (aux1->getKey() == itemKey))
            return aux1;
        aux2 = aux1->getNext();
    }
    return NULL;
}

template<class AnyType>
NodoSimple<AnyType>* LinkedList<AnyType>::getItemByPosition(int pPosition){
	NodoSimple<AnyType>* nodo = this->_Head;
	for(int index = 1; index < pPosition+1; index++){
		nodo = nodo->getNext();
	}
	return nodo;
}

template<class AnyType>
AnyType* LinkedList<AnyType>::getDataItem(string pItemKey){
	NodoSimple<AnyType>* nodo = getItem(pItemKey);
	return nodo->getVal();
}

template<class AnyType>
void LinkedList<AnyType>::printList()
{
    if (this->_Length == 0)
    {
        cout << "\n{ }\n";
       return;
    }
    NodoSimple<AnyType> * aux1 = this->_Head;
    NodoSimple<AnyType> * aux2 = this->_Head;
    cout << "\n{ ";
    while (aux2)
    {
    	aux1 = aux2;
        if (aux1 != this->_Head)
        {
            cout << (void*)aux1->getVal() << ":"<< aux1->getKey(); //AQUI CAMBIE KEY POR VAL
            if (aux1->getNext()) cout << ", ";
            else cout << " ";
        }
        aux2 = aux1->getNext();
    }
    cout << "}\n";
}

template<class AnyType>
int LinkedList<AnyType>::getLength()
{
    return this->_Length;
}

template<class AnyType>
LinkedList<AnyType>::~LinkedList()
{
    NodoSimple<AnyType> * aux1 = this->_Head;
    NodoSimple<AnyType> * aux2 = this->_Head;
    while (aux2)
    {
    	aux1 = aux2;
    	aux2 = aux1->getNext();
        if (aux2) delete aux1;
    }
}

#endif
