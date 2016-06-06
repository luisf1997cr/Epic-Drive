/**
 * @file NodoSimple.h
 * @date 4/3/16
 * @title Nodo Simple
 * @brief Abstracion de un nodo de lista simple para el proyecto xC++2
 */

/*
 * NodoSimple.h
 *
 *  Created on: 4 de mar. de 2016
 *      Author: gabriel
 */

#ifndef SRC_MANEJODATOS_NODOSIMPLE_H_
#define SRC_MANEJODATOS_NODOSIMPLE_H_

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

template <class AnyType>
class NodoSimple {
private:
	string _Key;
	AnyType* _Val;
	NodoSimple * _Next;
public:
	/**
	 * @brief Metodo constructor de NodoSimple
	 * @param string pClave
	 * @param AnyType* pValor
	 * @param NodoSimple* pSiguiente
	 */
	NodoSimple(string pClave, AnyType* pValor, NodoSimple * pSiguiente);
	/**
	 * @brief Metodo destructor de NodoSimple
	 */
	virtual ~NodoSimple();

	/**
	 * @brief Metodo define el argumento _Key
	 * @param string pKey
	 */
	void setKey(string pKey);
	/**
	 * @brief Metodo define el argumento _Val
	 * @param AnyType* pValor
	 */
	void setVal(AnyType* pValor);
	/**
	 * @brief Metodo define el argumento _Next
	 * @param NodoSimple* pNext
	 */
	void setNext(NodoSimple* pNext);

	/**
	 * @brief Metodo devuelve el atributo _Key
	 * @return string
	 */
	string getKey();
	/**
	 * @brief Metodo devuelve el atributo _Val
	 * @return AnyType*
	 */
	AnyType* getVal();
	/**
	 * @brief Metodo devuelve el atributo _Next
	 * @return NodoSimple*
	 */
	NodoSimple* getNext();
};

template <class AnyType>
NodoSimple<AnyType>::NodoSimple(string clave, AnyType* valor, NodoSimple* siguiente){
	this->_Key = clave;
	this->_Val = valor;
	this->_Next = siguiente;
}

template<class AnyType>
NodoSimple<AnyType>::~NodoSimple() {
	this->_Key.erase();
	free(this->_Val);
	free(this->_Next);
}

template<class AnyType>
void NodoSimple<AnyType>::setKey(string pKey){
	this->_Key = pKey;
}

template<class AnyType>
void NodoSimple<AnyType>::setNext(NodoSimple<AnyType>* pNext){
	this->_Next = pNext;
}

template<class AnyType>
void NodoSimple<AnyType>::setVal(AnyType* pValor){
	this->_Val = pValor;
}

template<class AnyType>
string NodoSimple<AnyType>::getKey(){
	return this->_Key;
}

template<class AnyType>
NodoSimple<AnyType>* NodoSimple<AnyType>::getNext(){
	return this->_Next;
}

template<class AnyType>
AnyType* NodoSimple<AnyType>::getVal(){
	return this->_Val;
}

#endif /* SRC_MANEJODATOS_NODOSIMPLE_H_ */
