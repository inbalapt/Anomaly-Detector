#include <iostream>
#include <vector>
#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"

// default constructor
SimpleAnomalyDetector::SimpleAnomalyDetector() {
    // TODO Auto-generated constructor stub

}

// default destructor
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
        // Initialize the most correlative column
        float highestCor = 0;
        int col = -1;
        for (int j = i + 1; j < columns; j++) {
            float pears = pearson(&table[i].second[0], &table[j].second[0], rows);
            // Change for absolute value.
            if (pears < 0) {
                pears = -pears;
            }
            //the condition for being a correlative feature.
            if (pears > highestCor && pears > 0.9) {
                highestCor = pears;
                col = j;
            }
        }
        // Associate f(i) and f(j) as correlated features. add it to cf
        if (col != -1) {
            Line line = linear_reg(&table[i].second[0], &table[col].second[0], rows);
            float threshold = 0;
            // Find the biggest threshold, loop over all the dots.
            for (int k = 0; k < rows; k++) {
                float x = table[i].second[k];
                float y = table[col].second[k];
                Point p(x,y);
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
            // Add to the list of cf
            this->cf.push_back(core);
        }
    }

}


/*
 * This function gets time series and find anomalies, if there are, according to the correlative features
 * that we found in the learning level (learnNormal function), set them in a vector, and returns it.
 */
vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    vector<AnomalyReport> report;
    // Running over the correlated features that we found in learnNormal
    for(correlatedFeatures corF: this->getNormalModel()) {
        string fea1 = corF.feature1;
        string fea2 = corF.feature2;
        // gets the current values of the features
        const vector<float> values1 = ts.get_feature_by_string(fea1);
        const vector<float> values2 = ts.get_feature_by_string(fea2);
        int size = values1.size();
        // Running over the values of the features
        for(int i = 0; i < size; i++) {
            float x = values1[i];
            float y = values2[i];
            Point p(x, y);
            // Check if the deviation of this point is bigger than the threshold
            if (dev(p, corF.lin_reg) > corF.threshold) {
                // Save the description of the features that have a deviation
                string description = fea1 + "-" + fea2;
                int time = i + 1;
                // Add the anomaly to the report vector.
                report.emplace_back(description, time);
                return report;
            }
        }
    }
}
