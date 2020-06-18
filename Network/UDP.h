#include <arpa/inet.h>

#ifndef BEP_UDP_H
#define BEP_UDP_H


class UDP {
public:
    UDP(__int16_t port);
    int sendUDP(const void *msg, int size, struct sockaddr_in receiver_address);
    int readUDP(void *buffer, int size);
    int readUDP(void *buffer, int size, struct sockaddr_in *source_address);
    struct sockaddr_in create_receiver(char *ip, __int16_t port);
private:
    struct sockaddr_in address;
    int sock;
};


#endif //BEP_UDP_H
