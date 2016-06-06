/*
 * ComunicationProtocol.h
 *
 *  Created on: 13 de abr. de 2016
 *      Author: jose
 */


#ifndef COMUNICATIONPROTOCOL_H_
#define COMUNICATIONPROTOCOL_H_

class ComunicationProtocol {
public:
	ComunicationProtocol(int pServerType);
	~ComunicationProtocol();

private:
	int _ServerType; // 0: Manager; 1: Monitor; 2: Client; 3 Server; 4: MonitorClient
};

#endif /* COMUNICATIONPROTOCOL_H_ */
