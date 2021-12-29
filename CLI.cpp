//
// Created by inbal on 12/29/21.
//

#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->dio=dio;
    commands.push_back(new UploadCSV(dio));
    commands.push_back(new AlgoSettings(dio));
    commands.push_back(new DetectAnom(dio));
    commands.push_back(new DisplayResults(dio));
    commands.push_back(new UploadAnom(dio));
    commands.push_back(new Exit(dio));
}

void CLI::start(){
}


CLI::~CLI(DefaultIO* dio) {
}
