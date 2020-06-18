#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdexcept>
#include "TCPClient.h"

TCPClient::TCPClient(char *destIp, __int16_t serverPort) {
    server_address.sin_family = AF_INET; //Set address family for the internet
    server_address.sin_port = htons(serverPort); //Convert port to right data type

    sock = socket(server_address.sin_family, SOCK_STREAM, 0); //Protocol 0 for IP packets

    if (sock < 0) {
        throw std::runtime_error("TCP socket could not be created.");
    }

    //Convert *char ip to in_address type and store it
    if (inet_pton(server_address.sin_family, destIp, &server_address.sin_addr) <= 0) {
        throw std::invalid_argument("Invalid IP address.");
    }
}

int TCPClient::tryconnect() {
    return connect(sock, (struct sockaddr *) &server_address, sizeof(server_address));
}

int TCPClient::sendTCP(void *msg, int size) {
    return send(sock, msg, size, 0);
}

int TCPClient::readTCP(void *buffer, int size) {
    return read(sock, buffer, size);
}