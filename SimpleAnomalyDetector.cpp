#include <iostream>
#include <vector>
#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
    // TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    // TODO Auto-generated destructor stub
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
        //initialize the most correlative column
        float highestCor = 0;
        int col = -1;
        for (int j = i + 1; j < columns; j++) {
            float pears = pearson(&table[i].second[0], &table[j].second[0], rows);
            //change for absolute value.
            if (pears < 0) {
                pears = -pears;
            }
            //the condition for being a correlative feature.
            if (pears > highestCor && pears > 0.9) {
                highestCor = pears;
                col = j;
            }
        }
        // associate f(i) and f(j) as correlated features. add it to cf
        if (col != -1) {
            Line line = linear_reg(&table[i].second[0], &table[col].second[0], rows);
            float threshold = 0;
            // find the biggest threshold, loop over all the dots.
            for (int k = 0; k < rows; k++) {
                float x = table[i].second[k];
                float y = table[col].second[k];
                Point p(x, y);
                float distance = dev(p, line);
                // The highest threshold.
                if (distance > threshold) {
                    threshold = distance;
                }
            }
            threshold = 1.1 * threshold;
            correlatedFeatures core = {
                    table[i].first,
                    table[col].first,
                    highestCor,
                    line,
                    threshold
            };
            // add to the list of cf
            this->cf.push_back(core);
        }
    }
    // TODO Auto-generated destructor stub
}


vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<AnomalyReport> report;
    for (correlatedFeatures corF: this->getNormalModel()) {
        string fea1 = corF.feature1;
        string fea2 = corF.feature2;
        const vector<float> values1 = ts.get_feature_by_string(fea1);
        const vector<float> values2 = ts.get_feature_by_string(fea2);
        int size = values1.size();
        for (int i = 0; i < size; i++) {
            float x = values1[i];
            float y = values2[i];
            Point p(x, y);
            if (dev(p, corF.lin_reg) > corF.threshold) {
                string description = fea1 + "-" + fea2;
                int time = i + 1;
                report.emplace_back(description, time);
                return report;
            }
        }
    }
}
