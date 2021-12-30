/*
 * CLI.h
 *
 * Author: Noa Leshem - 314665415
 * Inbal Apt - 207031006
 * on 30/12/21.
 */
#ifndef CLI_H_
#define CLI_H_

#include <string.h>
#include "commands.h"

using namespace std;

class CLI {
    vector<Command*> commands;
    DefaultIO* dio;

    // you can add cliData members
public:
    void printMenu();
    CLI(DefaultIO* dio);
    void start();
    virtual ~CLI();
};

#endif /* CLI_H_ */

