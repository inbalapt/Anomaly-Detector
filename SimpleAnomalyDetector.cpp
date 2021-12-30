/*
 * SimpleAnomalyDetector.cpp
 *
 * Author: Noa Leshem - 314665415
 * Inbal Apt - 207031006
 * on 10/20/21.
 */

#include <iostream>
#include <vector>
#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"

// default constructor
SimpleAnomalyDetector::SimpleAnomalyDetector() {
}

// default destructor
SimpleAnomalyDetector::~SimpleAnomalyDetector() {
}

/*
 * This function gets a time series table, find the correlative features, and
 * set them in the cf vector with all the relevant details.
 */
void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    // get a details from the time series.
    int columns = ts.getNumOfCol();
    int rows = ts.getNumOfRows();
    vector<std::pair<std::string, std::vector<float>>> table = ts.getVector();
    // find  the correlative features.
    for (int i = 0; i < columns; i++) {
        // Initialize the most correlative column
        float highestCor = 0;
        int col = -1;
        for (int j = i + 1; j < columns; j++) {
            float pears = pearson(&table[i].second[0], &table[j].second[0], rows);
            // Change for absolute value.
            if (pears < 0) {
                pears = -pears;
            }
            // find the most correlated features.
            if (pears > highestCor) {
                highestCor = pears;
                col = j;
            }
        }
        // Associate f(i) and f(j) as correlated features. add it to cf
        if (col != -1) {
            associateCorrelatedFeatures(i, col, highestCor, table, rows);
        }
    }
}

/*
 * This function gets time series and find anomalies, if there are, according to the correlative features
 * that we found in the learning level (learnNormal function), set them in a vector, and returns it.
 */
vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<AnomalyReport> report;

    // Running over the correlated features that we found in learnNormal
    for (const correlatedFeatures &corF: this->getNormalModel()) {
        addReport(ts, corF, report);
    }
    return report;

}





//Associate f(i) and f(j) as correlated features. add it to cf

void SimpleAnomalyDetector::associateCorrelatedFeatures(int i, int j, float cor,
                                                        vector<std::pair<std::string, std::vector<float>>> table,
                                                        int rows) {
    if (cor > this->threshold) {
        Line line = linear_reg(&table[i].second[0], &table[j].second[0], rows);
        float threshold = 0;
        // Find the biggest threshold, loop over all the dots.
        for (int k = 0; k < rows; k++) {
            float x = table[i].second[k];
            float y = table[j].second[k];
            float distance = dev(Point(x, y), line);
            // The highest threshold.
            if (distance > threshold) {
                threshold = distance;
            }
        }
        threshold = 1.1 * threshold;
        correlatedFeatures core = {
                table[i].first,
                table[j].first,
                cor,
                line,
                threshold,
                //add undefined circle.
                Circle(Point(0, 0), 0)
        };
        // Add to the list of cf
        this->cf.push_back(core);
    }

}

//set the threshold for correlated feature.
void SimpleAnomalyDetector::setThreshold(float threshold) {
    this->threshold = threshold;
}

void
SimpleAnomalyDetector::addReport(const TimeSeries &ts, const correlatedFeatures &corF, vector<AnomalyReport> &report) {
    string fea1 = corF.feature1;
    string fea2 = corF.feature2;
    //if the corrlation is bigger than the threshold.
    if (corF.corrlation > this->threshold) {
        // The x and vectors.
        const vector<float> values1 = ts.get_feature_by_string(fea1);
        const vector<float> values2 = ts.get_feature_by_string(fea2);
        int size = (int) values1.size();
        // Running over the values of the features
        for (int i = 0; i < size; i++) {
            float x = values1[i];
            float y = values2[i];
            // Check if the deviation of this point is bigger than the threshold
            if (dev(Point(x, y), corF.lin_reg) >= corF.threshold) {
                // Save the description of the features that have a deviation
                string description = fea1 + "-";
                description += fea2;
                int time = i + 1;
                AnomalyReport anomalyReport = AnomalyReport(description, time);
                // Add the anomaly to the report vector.
                report.push_back(anomalyReport);
            }
        }
    }
    // gets the current values of the features

}
