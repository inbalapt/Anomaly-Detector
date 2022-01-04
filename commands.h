/*
 * command.h
 *
 * Author: Noa Leshem - 314665415
 * Inbal Apt - 207031006
 * on 30/12/21.
 */
#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

typedef struct {
    string description;
    int begin;
    int end;
} ReportsRanges;

typedef struct {
    float threshold = 0.9;
    vector<AnomalyReport> report;
    int numOfRows;
} CLIData;

class DefaultIO {
public:
    virtual string read() = 0;

    virtual void write(string text) = 0;

    virtual void write(float f) = 0;

    virtual void read(float *f) = 0;

    virtual ~DefaultIO() {}

    // you may add additional methods here
};

// you may add here helper classes


// you may edit this class
class Command {
protected:
    DefaultIO *dio;
    CLIData *cliData;

public:
    string actDescription;

    Command(DefaultIO *dio) : dio(dio) {}

    Command(DefaultIO *dio, const string actDescription) : dio(dio), actDescription(actDescription) {};

    virtual void execute(CLIData *cliData) = 0;

    virtual ~Command() {}

};

/*
 * option 1 - upload the csv test and train files.
 */
class UploadCSVFile : public Command {
public:
    UploadCSVFile(DefaultIO *dio) : Command(dio, "upload a time series csv file") {}

    virtual void execute(CLIData *cliData) {
        std::string line;

        dio->write("Please upload your local train CSV file.\n");

        // get train file from client
        std::ofstream train("anomalyTrain.csv");
        line = dio->read();
        while (line != "done") {
            train << line << endl;
            line = dio->read();
        }
        train.close();

        dio->write("Upload complete.\n");
        dio->write("Please upload your local test CSV file.\n");

        // get test file from client
        std::ofstream test("anomalyTest.csv");
        line = dio->read();
        cliData->numOfRows = 0;
        while (line != "done\n" && line != "done") {
            test << line << endl;
            line = dio->read();
            cliData->numOfRows++;
        }
        cliData->numOfRows--;
        test.close();

        dio->write("Upload complete.\n");
    }
};

/*
 * option 2 - set the threshold for correlated features.
 */
class AlgoSettings : public Command {
public:
    AlgoSettings(DefaultIO *dio) : Command(dio, "algorithm settings") {}

    virtual void execute(CLIData *cliData) {
        float thresh;

        dio->write("The current correlation threshold is ");
        dio->write(cliData->threshold);
        dio->write("\nType a new threshold\n");
        thresh = std::stof(dio->read());
        while (thresh < 0 || thresh > 1) {
            dio->write("please choose a value between 0 and 1.\n");


            //convert from string to int.
            thresh = std::stof(dio->read());
        }
        cliData->threshold = thresh;
    }
};

/*
 * option 3 - detect the normal features.
 */
class DetectAnom : public Command {
public:
    DetectAnom(DefaultIO *dio) : Command(dio, "detect anomalies") {}

    virtual void execute(CLIData *cliData) {
        //train and test of time series.
        TimeSeries train("anomalyTrain.csv");
        TimeSeries test("anomalyTest.csv");
        HybridAnomalyDetector anomalyDetector;
        //set the threshold.
        anomalyDetector.setThreshold(cliData->threshold);
        anomalyDetector.learnNormal(train);
        //save the normal features.
        cliData->report = anomalyDetector.detect(test);
        dio->write("anomaly detection complete.\n");
    }
};



/*
 * option 4 - printing the reports od the exceptions.
 */
class DisplayResults:public Command{
public:
    DisplayResults(DefaultIO *dio) : Command(dio, "display results") {}

    virtual void execute(CLIData *cliData) {
        for (int i = 0; i < cliData->report.size(); i++) {
            dio->write((float)cliData->report[i].timeStep);
            dio->write("   ");
            dio->write(cliData->report[i].description + "\n");
        }
        dio->write("Done.\n");
    }
};

/*
 * option 5 - we get file of ranges exceptions from client and compare those with the ranges that we found.
 */
class UploadAnom:public Command{
public:
    UploadAnom(DefaultIO *dio) : Command(dio, "upload anomalies and analyze results") {}

    virtual void execute(CLIData *cliData) {
        std::string line;
        vector<ReportsRanges> reports_ranges;
        vector<ReportsRanges> user_ranges;

        float P = 0;
        int N = 0;
        int sum = 0; // counting deviations for N

        dio->write("Please upload your local anomalies file.\n");
        line = dio->read();
        while (line != "done") {
            std::stringstream string_stream(line);
            int start = 0;
            int end = 0;
            string_stream >> start;
            if (string_stream.peek() == ',') string_stream.ignore();
            string_stream >> end;
            P++;
            sum += end - start + 1;
            ReportsRanges user_range = {"", start, end};
            user_ranges.push_back(user_range);
            line = dio->read();
        }

        N = cliData->numOfRows - sum;
        // get the ranges of the reports that were discovered
        for (int i = 0; i < cliData->report.size(); i++) {
            int count = 1;  // count the sequence of deviations of this current report.
            ReportsRanges current_report;
            current_report.description = cliData->report[i].description;
            current_report.begin = (int) cliData->report[i].timeStep;
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

            // update the end of the range to be the begin + count of the sequence deviations.
            current_report.end = current_report.begin + count - 1;
            i--;

            // pushing this report to the vector of reports ranges.
            reports_ranges.push_back(current_report);
        }

        float TP = 0, FP = 0;

        /*
         * check if the ranges reports that we found have overlaps with user ranges.
         */
        for(ReportsRanges &real_report : reports_ranges) {
            bool true_positive = false;
            for(ReportsRanges &user_range : user_ranges) {
                if(user_range.begin <= real_report.end && user_range.end >= real_report.begin) {
                    // we found true positive range
                    TP++;
                    true_positive = true;
                }
            }
        }
        FP = reports_ranges.size() - TP;
        float true_positive_rate = (floor((TP / float(P)) * 1000)) / 1000;
        float false_alarm_rate = ((int)(1000.0 * FP / float(N))) / 1000.0f;
        //float false_alarm_rate = (floor((FP / float(N)) * 1000)) / 1000;
        dio->write("Upload complete.\n");
        dio->write("True Positive Rate: ");
        dio->write(true_positive_rate);
        dio->write("\nFalse Positive Rate: ");
        dio->write(false_alarm_rate);
        dio->write("\n");


    }
};


#endif /* COMMANDS_H_ */
