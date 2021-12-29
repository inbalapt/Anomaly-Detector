
#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

struct ReportsRangers{
    string description;
    long begin;
    long end;
};

struct CLIData{
    float threshold;
    vector<AnomalyReport> report;
    int numOfRows;
};

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
protected:
    DefaultIO* dio;
    CLIData* cliData;

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
    virtual void execute(){
        std::string line;

        dio->write("Please upload your local train CSV file.\n");

        // get train file from client
        std::ofstream train("anomalyTrain.csv");
        line = dio->read();
        while(line != "done") {
            train << line << endl;
            line = dio->read();
            this->cliData->numOfRows += 1;
        }
        train.close();

        dio->write("Upload complete.\n");
        dio->write("Please upload your local test CSV file.\n");

        // get test file from client
        std::ofstream test("anomalyTrain.csv");
        line = dio->read();
        while(line != "done") {
            test << line << endl;
            line = dio->read();
            this->cliData->numOfRows += 1;
        }
        test.close();

        dio->write("Upload complete.\n");
    }
};

class AlgoSettings:public Command{
public:
    AlgoSettings(DefaultIO* dio):Command(dio, "algorithm settings"){}
    virtual void execute(){
        float thresh;
        dio->write("The current correlation threshold is ");
        dio->write(cliData->threshold);
        dio->write("\nType a new threshold\n");
        thresh = std::stof(dio->read());
        while (thresh < 0 || thresh > 1) {
            dio->write("please choose a value between 0 and 1.\n");
            thresh = std::stof(dio->read());
        }
        this->cliData->threshold = thresh;
    }
};

// option 3
class DetectAnom:public Command{
public:
    DetectAnom(DefaultIO* dio):Command(dio, "detect anomalies"){}
    virtual void execute(){
        //train and test of time series.
        TimeSeries train("anomalyTrain.csv");
        TimeSeries test("anomalyTest.csv");
        HybridAnomalyDetector anomalyDetector;
        anomalyDetector;
    }
};


class DisplayResults:public Command{
public:
    DisplayResults(DefaultIO* dio):Command(dio, "display results"){}
    virtual void execute() {
        for(int i = 0; i < cliData->report.size(); i++){
            dio->write(cliData->report[i].timeStep);
            dio->write("\t");
            dio->write(cliData->report[i].description + "\n");
        }
        dio->write("Done.\n");
    }
};

class UploadAnom:public Command{
public:
    UploadAnom(DefaultIO* dio):Command(dio, "upload anomalies and analyze results"){}
    virtual void execute() {
        std::string line;
        vector<ReportsRangers> reports_ranges;
        int num_of_deviations = 0; // counting deviations for N

        // get the ranges of the reports that were discovered
        for(int i = 0; i < cliData->report.size(); i++) {
            int count = 1;  // count the sequence of deviations of this current report.
            ReportsRangers current_report;
            current_report.description = cliData->report[i].description;
            current_report.begin = cliData->report[i].timeStep;
            i++;

            /*
             * check if the description of this current report is as the one that comes after,
             * and if this is a part of the sequence of deviations.
             */
            while (cliData->report[i].description == current_report.description &&
            cliData->report[i].timeStep == current_report.begin + count && i < cliData->report.size()) {
                count++;
                i++;
            }

            num_of_deviations += count;
            // update the end of the range to be the begin + count of the sequence deviations.
            current_report.end = current_report.begin + count;
            // pushing this report to the vector of reports ranges.
            reports_ranges.push_back(current_report);
        }

        float P;
        float N;




        dio->write("Please upload your local anomalies file.\n");

        // get train file from client
        std::ofstream train("anomalyTrain.csv");
        line = dio->read();
        while(line != "done") {
            train << line << endl;
            line = dio->read();
        }
        train.close();
    }
};


#endif /* COMMANDS_H_ */