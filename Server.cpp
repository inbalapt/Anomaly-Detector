/*
 * Server.cpp
 *
 * Author: Noa Leshem - 314665415
 * Inbal Apt - 207031006
 * on 04/01/22.
 */
#include "Server.h"


Server::Server(int port) throw(const char *) {
    file_des = socket(AF_INET, SOCK_STREAM, 0);
    if (file_des < 0) {
        throw std::runtime_error("socket failed");
    }
}

void Server::start(ClientHandler &ch) throw(const char *) {
}

void Server::stop() {
    t->join(); // do not delete this!
}

Server::~Server() {
}
