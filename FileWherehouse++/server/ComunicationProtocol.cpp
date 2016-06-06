/*
 * ComunicationProtocol.cpp
 *
 *  Created on: 13 de abr. de 2016
 *      Author: jose
 */

#include "ComunicationProtocol.h"
#include "tcpacceptor.h"

ComunicationProtocol::ComunicationProtocol(int pServerType) {
	this->_ServerType = pServerType;
}

ComunicationProtocol::~ComunicationProtocol() {
	// TODO Auto-generated destructor stub
}

