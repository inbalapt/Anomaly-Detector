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

using namespace std;

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
