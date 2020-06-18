#include <arpa/inet.h>

#ifndef BEP_TCPSERVER_H
#define BEP_TCPSERVER_H


class TCPServer {
public:
    TCPServer(__int16_t destPort);
    void listenAccept();
    int sendTCP(void *msg, int size);
    int readTCP(void *buffer, int size);
private:
    int sock;
    int listen_sock;
    int addrlen;
    struct sockaddr_in server_address;
};


#endif //BEP_TCPSERVER_H
