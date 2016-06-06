/**
 * @file ServerConstants.h
 * @date 15/2/16
 * @author Jose Eduardo Jimenez A 2014072577
 * @title ServerConstants
 * @brief Server del Juego
 */

#ifndef SERVERCONSTANTS_H_
#define SERVERCONSTANTS_H_
#include <string>
#include <string.h>

using namespace  std;

class ServerConstants{
public:
	const bool DEBUG = true;
	int PORT = 8080;
	const string EROOR_SOCKET = "Error al crear el socket";
	const string ERROR_CONECTAR = "Error al connectar";
	const string WAITING = "Esperando el cliente";
	const string CONNECT = "Conecto";
	const string SENDINFO_MSJ = "Bytes enviados; ";
	const string NO_HAY_MSJ = "NOHAYMENSAJES";
};



#endif /* SERVERCONSTANTS_H_ */
