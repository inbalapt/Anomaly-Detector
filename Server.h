/*
 * Server.h
 *
 * Author: Noa Leshem - 314665415
 * Inbal Apt - 207031006
 * on 04/01/22.
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <pthread.h>
#include <netinet/in.h>
#include <ostream>
#include <sys/socket.h>
#include <thread>
#include "commands.h"
#include "CLI.h"
#include <cstdlib>
#include <stdexcept>
#include <unistd.h>

using namespace std;

class SocketIO : public DefaultIO {
    int clientSocket;

public:
    explicit SocketIO(int clientSocket) : clientSocket(clientSocket) {}

    virtual string read() {
        string str = "";
        char c = 0;
        while (true) {
            recv(clientSocket, &c, sizeof(c), 0);
            if (c == '\n') break;
            str += c;
        }
        return str;
    };

    virtual void write(string text) {
        send(clientSocket, text.data(), text.size(), 0);
    }

    virtual void write(float f) {
        std::ostringstream stringStream;
        stringStream << f;
        std::string str(stringStream.str());
        send(clientSocket, str.data(), str.size(), 0);
    }

    // to get the choice of client
    virtual void read(float *f) {
        char array[2];

        // first char for choice, second to '\n'.
        recv(clientSocket, &array, sizeof(array), 0);
        std::istringstream ss(array);
        ss >> *f;
    }

    ~SocketIO() = default;
};

// edit your ClientHandler interface here:
class ClientHandler{
    public:
    virtual void handle(int clientID)=0;
};


// you can add helper classes here and implement on the cpp file


// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler{
	public:
    virtual void handle(int clientID){
        SocketIO socketIo = SocketIO(clientID);
        CLI clientCli = CLI(&socketIo);
        clientCli.start();
    }
};


// implement on Server.cpp
class Server {
    int file_des;
	thread* t; // the thread to run the start() method in
    bool should_stop;
    // make soccadd_in struct with data for bind
    sockaddr_in server;
    sockaddr_in client;
	// you may add data members

public:
	Server(int port)throw(const char*);
	virtual ~Server();
	void start(ClientHandler& ch)throw(const char*);
	void stop();
};
#endif /* SERVER_H_ */

