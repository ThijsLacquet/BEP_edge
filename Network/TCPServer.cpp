#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdexcept>
#include "TCPServer.h"



TCPServer::TCPServer(__int16_t serverPort) {
    addrlen = sizeof(server_address);
    server_address.sin_family = AF_INET; //Set address family for the internet
    server_address.sin_addr.s_addr = INADDR_ANY; //Set client ip to all possible ip's
    server_address.sin_port = htons(serverPort); //Convert port to right data type

    listen_sock = socket(server_address.sin_family, SOCK_STREAM, 0); //Protocol 0 for IP packets

    if (listen_sock < 0) {
        throw std::runtime_error("TCP socket could not be created.");
    }

    //Bind socket to server address and port
    if (bind(listen_sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        throw std::runtime_error("TCP socket could not be bound to port.");
    }
}

void TCPServer::listenAccept() {
    if (listen(listen_sock, 3) < 0) {
        throw std::runtime_error("Error while listening for client.");
    }
    sock = accept(listen_sock, (struct sockaddr *) &server_address, (socklen_t*) &addrlen);
    if (sock < 0) {
        throw std::runtime_error("Error while accepting client.");
    }
}

int TCPServer::sendTCP(void *msg, int size) {
    return send(sock, msg, size, 0);
}

int TCPServer::readTCP(void *buffer, int size) {
    int bytesRead = read(sock, buffer, size);
    return bytesRead;
}


