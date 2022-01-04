/*
 * Server.cpp
 *
 * Author: Noa Leshem - 314665415
 * Inbal Apt - 207031006
 * on 04/01/22.
 */
#include <netinet/in.h>
#include "Server.h"

/*
 * constructor of Server class.
 */
Server::Server(int port)throw(const char *) {
    file_des = socket(AF_INET, SOCK_STREAM, 0);
    // if socket is failed
    if (file_des < 0) {
        throw std::runtime_error("socket failed");
    }

    // update soccadd_in data for bind
    this->server.sin_addr.s_addr = INADDR_ANY;
    this->server.sin_port = htons(port);
    this->server.sin_family = AF_INET;

    int b = bind(file_des, (struct sockaddr*)&server, sizeof(server));

    // if bind is failed
    if(b < 0) {
        throw std::runtime_error("bind failure");
    }
    int l = listen(file_des, 1);
    // if listen is failed
    if (l == 1){
        throw std::runtime_error("listen failure");
    }
}

/*
 * The server connects to the clients.
 */
void Server::start(ClientHandler &ch)throw(const char *) {
    // creating new thread
    this->t = new thread([&ch,this]{
        socklen_t client_size = sizeof (this->client);
        while (!this->should_stop){
            //try to connect to the client
            int client_des = accept(this->file_des,(struct sockaddr *) &this->client, &client_size);
            // if the connection failed.
            if (client_des <= 0) {
                throw std::runtime_error("connection failed");
            }
            ch.handle(client_des);
            close(client_des);
        }
        close(this->file_des);
    });
}

/*
 * Stop the server.
 */
void Server::stop() {
    should_stop = true;
    t->join(); // do not delete this!
}

/*
 * Stop the server. server destructor.
 */
Server::~Server() {
    // if the program hadn't stopped, stop it.
    if(!should_stop) stop();
}
