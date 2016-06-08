/*
 * FileWhereHouse.h
 *
 *  Created on: 6 de jun. de 2016
 *      Author: acacia
 */

#ifndef FILEWHEREHOUSE___FILEWHEREHOUSE_H_
#define FILEWHEREHOUSE___FILEWHEREHOUSE_H_
#include "../server/tcpacceptor.h"

class FileWhereHouse {
public:
	FileWhereHouse(int pPortNumbre, char* pIpNumber, string pFileUbication);
	virtual ~FileWhereHouse();

	int portNumber;
	char* ipNumber;
	string fileUbication;
	TCPAcceptor *server;
};

#endif /* FILEWHEREHOUSE___FILEWHEREHOUSE_H_ */
