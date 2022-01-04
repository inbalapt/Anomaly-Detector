/*
 * Server.cpp
 *
 * Author: Noa Leshem - 314665415
 * Inbal Apt - 207031006
 * on 04/01/22.
 */
#include "Server.h"


Server::Server(int port)throw (const char*) {

}

void Server::start(ClientHandler& ch)throw(const char*){	
}

void Server::stop(){
	t->join(); // do not delete this!
}

Server::~Server() {
}

