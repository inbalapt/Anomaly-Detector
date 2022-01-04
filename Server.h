/*
 * Server.h
 *
 * Author: Noa Leshem - 314665415
 * Inbal Apt - 207031006
 * on 04/01/22.
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <ostream>
#include <sys/socket.h>
#include <thread>
#include "commands.h"

using namespace std;

class SocketIO : public DefaultIO {
    int clientSocket;

public:
    explicit SocketIO(int clientSocket) : clientSocket(clientSocket) {}

    string read() override {
        string str = "";
        char c = 0;
        while (true) {
            recv(clientSocket, &c, sizeof(c), 0);
            if (c == '\n') break;
            str += c;
        }
        return str;
    };

    virtual void write(string text) override {
        send(clientSocket, text.data(), text.size(), 0);
    }

    virtual void write(float f) override {
        std::ostringstream stringStream;
        stringStream << f;
        std::string str(stringStream.str());
        send(clientSocket, str.data(), str.size(), 0);
    }

    // to get the choice of client
    virtual void read(float *f) override {
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

    }
};


// implement on Server.cpp
class Server {
	thread* t; // the thread to run the start() method in

	// you may add data members

public:
	Server(int port) throw (const char*);
	virtual ~Server();
	void start(ClientHandler& ch)throw(const char*);
	void stop();
};
#endif /* SERVER_H_ */

