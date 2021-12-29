
#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
public:
    virtual string read()=0;
    virtual void write(string text)=0;
    virtual void write(float f)=0;
    virtual void read(float* f)=0;
    virtual ~DefaultIO(){}

    // you may add additional methods here
};

// you may add here helper classes


// you may edit this class
class Command{
    DefaultIO* dio;

public:
    string actDescription;

    Command(DefaultIO* dio):dio(dio){}
    Command(DefaultIO* dio, const string actDescription):dio(dio), actDescription(actDescription){};
    virtual void execute()=0;
    virtual ~Command(){}
};

// implement here your command classes

class UploadCSVFile:public Command{
public:
    UploadCSVFile(DefaultIO* dio):Command(dio, "upload a time series csv file"){}

};

class AlgoSettings:public Command{
public:
    AlgoSettings(DefaultIO* dio):Command(dio, "algorithm settings"){}
};


class DetectAnom:public Command{
public:
    DetectAnom(DefaultIO* dio):Command(dio, "detect anomalies"){}
};


class DisplayResults:public Command{
public:
    DisplayResults(DefaultIO* dio):Command(dio, "display results"){}
};

class UploadAnom:public Command{
public:
    UploadAnom(DefaultIO* dio):Command(dio, "upload anomalies and analyze results"){}
};


#endif /* COMMANDS_H_ */