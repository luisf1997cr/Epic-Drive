#ifndef __tcpacceptor_h__
#define __tcpacceptor_h__

#include <string>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include "tcpstream.h"
#include <pthread.h>

#include <unistd.h>
#include "ComunicationProtocol.h"
#include "../structures/LinkedList.h"

using namespace std;

struct infoSocket{
	TCPStream* _Conection;
};

class TCPAcceptor
{
    int    pSocket;
    int    portNumber;
    string addresDirection;
    bool   serverListening;
    LinkedList<TCPStream>* _Clientes;
    static LinkedList<string> *_Mensajes;
    
  public:
    TCPAcceptor(int port, char* address);
    ~TCPAcceptor();

    int        start();
    TCPStream* acceptt();
    void initConnection();
    static void * controlador(void *pObjeto);
    static void * MultiClient(void *pObjeto);

    bool getWorking();

  private:

    bool _Working;

};

#endif
