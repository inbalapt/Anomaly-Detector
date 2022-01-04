/*
 * Server.cpp
 *
 * Author: Noa Leshem - 314665415
 * Inbal Apt - 207031006
 * on 04/01/22.
 */
#include <netinet/in.h>
#include "Server.h"


Server::Server(int port) throw(const char *) {
    file_des = socket(AF_INET, SOCK_STREAM, 0);
    //had gone
    if (file_des < 0) {
        throw std::runtime_error("socket failed");
    }
    sockaddr_in server{};
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    server.sin_family = AF_INET;


    int b = bind(file_des, (struct sockaddr*)&server, sizeof(server));
    if(b < 0) {
        throw std::runtime_error("bind failure");
    }
    int l = listen(file_des, 1);
    if (l == 1){
        throw std::runtime_error("listen failure");
    }
}

void Server::start(ClientHandler &ch) throw(const char *) {
}

void Server::stop() {
    t->join(); // do not delete this!
}

Server::~Server() {
}
