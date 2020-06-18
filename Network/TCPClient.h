#include <arpa/inet.h>

#ifndef BEP_TCPCLIENT_H
#define BEP_TCPCLIENT_H


class TCPClient {
public:
    TCPClient(char *destIp, __int16_t serverPort);
    int tryconnect();
    int sendTCP(void *msg, int size);
    int readTCP(void *buffer, int size);
private:
    int sock;
    struct sockaddr_in server_address;
};

#endif //BEP_TCPCLIENT_H
