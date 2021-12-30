/*
 * CLI.cpp
 *
 * Author: Noa Leshem - 314665415
 * Inbal Apt - 207031006
 * on 30/12/21.
 */
#include "CLI.h"

CLI::CLI(DefaultIO *dio) {
    this->dio = dio;
    commands.push_back(new UploadCSVFile(dio));
    commands.push_back(new AlgoSettings(dio));
    commands.push_back(new DetectAnom(dio));
    commands.push_back(new DisplayResults(dio));
    commands.push_back(new UploadAnom(dio));
}

void CLI::printMenu() {
    dio->write("Welcome to the Anomaly Detection Server.\n"
               "Please choose an option:\n");
    int commands_size = commands.size();
    int i = 0;
    // print all the options of the commands.
    for (; i < commands_size; i++) {
        dio->write(float(i + 1));
        dio->write(". " + commands[i]->actDescription + "\n");
    }
    dio->write(float(i + 1));
    dio->write(". exit\n");

}

void CLI::start() {
    CLIData cliData;
    float option = -1;
    while (option != 6) {
        printMenu();
        dio->read(&option);
        // if the option is in the range.
        if (option > 0 && option < 6) {
            int i = int(option) - 1;
            commands[i]->execute(&cliData);
        }
    }
}


CLI::~CLI() {
    int commands_size = commands.size();
    for (int i = 0; i < commands_size; i++){
        delete commands[i];
    }
}
