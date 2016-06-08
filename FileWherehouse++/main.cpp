/*
 * main.cpp
 *
 *  Created on: 6 de jun. de 2016
 *      Author: acacia
 */

#include "main.h"
#include "FileWhereHouse++/FileWhereHouse.h"
#include "structures/BTree.h"
#include <iostream>
using namespace std;

int main(){

//	char* ip= "123.01.01";
//
//	FileWhereHouse* prueba = new FileWhereHouse(8080,ip,"hola");
//
//	prueba->server->initConnection();
//	prueba->server->acceptt();
//	cout<< "Fin 10" <<endl;

	BTree* pruebaArbolB= new BTree(3);

	pruebaArbolB->insert(1);
	pruebaArbolB->insert(3);
	pruebaArbolB->insert(7);
	pruebaArbolB->insert(10);
	pruebaArbolB->insert(11);
	pruebaArbolB->insert(18);
	pruebaArbolB->insert(20);
	pruebaArbolB->insert(4);
	pruebaArbolB->insert(2);
	pruebaArbolB->insert(15);
	pruebaArbolB->insert(100);
	pruebaArbolB->insert(31);
	pruebaArbolB->insert(9);

	cout<< "Prueba arbol";
	pruebaArbolB->traverse();
	cout<<endl;

	pruebaArbolB->remove(101);
	cout<< "Prueba arbol";
	pruebaArbolB->traverse();
	cout<<endl;

	BNode* t=pruebaArbolB->searchNode(100);

}
