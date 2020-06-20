#include <sys/socket.h>
#include <unistd.h>
#include <stdexcept>
#include <netinet/in.h>
#include "UDP.h"

UDP::UDP(__int16_t port) {
    address.sin_family = AF_INET; //Set address family for the internet
    address.sin_addr.s_addr = INADDR_ANY; //Set client ip to all possible ip's
    address.sin_port = htons(port); //Convert port to right data type


    sock = socket(address.sin_family, SOCK_DGRAM, 0); //Protocol 0 for IP packets

    if (sock < 0) {
        throw std::runtime_error("UDP socket could not be created.");
    }

    //Bind socket to server address and port
    if (bind(sock, (struct sockaddr *) &address, sizeof(address)) < 0) {
        throw std::runtime_error("UDP socket could not be bound to port.");
    }
}

int UDP::sendUDP(const void *msg, int size, struct sockaddr_in dest_address) {
    return sendto(sock, msg, size, MSG_CONFIRM, (const struct sockaddr *) &dest_address,
                  sizeof(dest_address));
}

int UDP::readUDP(void *buffer, int size, struct sockaddr_in *source_address) {
    socklen_t len = sizeof(*source_address);
    return recvfrom(sock, buffer, size, MSG_WAITALL, (struct sockaddr *) &source_address, &len);
}

int UDP::readUDP(void *buffer, int size) {
    struct sockaddr_in source_address;
    return (readUDP(buffer, size, &source_address));
}

struct sockaddr_in UDP::create_receiver(char *ip, __int16_t port) {
    sockaddr_in receiver;
    receiver.sin_family = AF_INET;
    receiver.sin_port = htons(port);

    if (inet_pton(receiver.sin_family, ip, &receiver.sin_addr) <= 0) {
        throw std::invalid_argument("Invalid IP address.");
    }

    return receiver;
}
