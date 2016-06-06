#include "tcpacceptor.h"


LinkedList<string>* TCPAcceptor::_Mensajes = new LinkedList<string>();

TCPAcceptor::TCPAcceptor(int port, char* address)
    : pSocket(0), portNumber(port), addresDirection(address), serverListening(false) {
	this->_Clientes = new LinkedList<TCPStream>();
	this->_Working = true;
}

TCPAcceptor::~TCPAcceptor()
{
    if (pSocket > 0) {
        close(pSocket);
    }
}

int TCPAcceptor::start()
{
    if (serverListening == true) {
        return 0;
    }

    pSocket = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;

    memset(&address, 0, sizeof(address));
    address.sin_family = PF_INET;
    address.sin_port = htons(portNumber);
    if (addresDirection.size() > 0) {
        inet_pton(PF_INET, addresDirection.c_str(), &(address.sin_addr));
    }
    else {
        address.sin_addr.s_addr = INADDR_ANY;
    }

    int optval = 1;
    setsockopt(pSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

    int result = bind(pSocket, (struct sockaddr*)&address, sizeof(address));
    if (result != 0) {
        perror("bind() failed");
        return result;
    }

    result = listen(pSocket, 5);
    if (result != 0) {
        perror("listen() failed");
        return result;
    }
    serverListening = true;
    return result;
}

TCPStream* TCPAcceptor::acceptt()
{
    if (serverListening == false) {
        return NULL;
    }

    struct sockaddr_in address;
    socklen_t len = sizeof(address);
    memset(&address, 0, sizeof(address));
    int sd = accept(pSocket, (struct sockaddr*)&address, &len);
    if (sd < 0) {
        perror("accept() failed");
        return NULL;
    }
    return new TCPStream(sd, &address);
}

void TCPAcceptor::initConnection(){
    if (start() == 0) {
    	this->_Working = true;
    	pthread_t hilo1;
    	pthread_create(&hilo1,0,TCPAcceptor::MultiClient,(void*)this);
    }
}

void* TCPAcceptor::MultiClient(void* pObject){
	TCPAcceptor* acceptor = (TCPAcceptor*) pObject;
	infoSocket data;
	while(1){
	    data._Conection = acceptor->acceptt();
	    if (data._Conection != NULL) {
	    	acceptor->_Clientes->insertData(data._Conection);
	    	pthread_t hilo;
	    	pthread_create(&hilo,0,TCPAcceptor::controlador,(void*)&data);
	    }
   	}
}

void* TCPAcceptor::controlador(void *pObjeto){
	infoSocket *data = (infoSocket*)pObjeto;
	string mensaje;
	while(true){
		char buffer[256];
		ssize_t bytes;
		bytes = data->_Conection->receive(buffer,sizeof(buffer));
		//mensaje.append(buffer, bytes);
		if (bytes > 0)
			buffer[bytes] = 0;
			ComunicationProtocol* protocolo = new ComunicationProtocol(3);
			data->_Conection->send(buffer, bytes);
			break;
		}
		//cout << mensaje << endl;
		//_Mensajes->insertData(mensaje);

		pthread_exit(NULL);

}

bool TCPAcceptor::getWorking(){
	return this->_Working;
}


