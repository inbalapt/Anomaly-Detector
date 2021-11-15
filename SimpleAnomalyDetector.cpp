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


void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    int columns = ts.getNumOfCol();
    int rows = ts.getNumOfRows();

    vector<std::pair<std::string, std::vector<float>>> table = ts.getVector();
    for (int i = 0; i < columns; i++) {
        //initialize the most correlative column
        float highestCor = 0;
        int col = -1;
        for (int j = i + 1; j < columns; j++) {
            //person correlative
            float pears = pearson(&table[j].second[0], &table[i].second[0], rows);
            if (pears > highestCor) {
                //setting the most correlative column.
                highestCor = pears;
                col = j;
            }
            // associate f(i) and f(j) as correlated features. add it to cf
            if (col != -1) {
                Line line = linear_reg(&table[i].second[0], &table[j].second[0], rows);
                float threshold = 0;
                // find the biggest threshold, loop over all the dots.
                for (int k = 0; k < rows; k++) {
                    float x = table[col].second[k];
                    float y = table[j].second[k];
                    float distance = dev(Point(x, y), line);
                    // the highest threshold
                    if (distance > threshold) {
                        threshold = distance;
                    }
                }
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

    }
    // TODO Auto-generated destructor stub
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    // TODO Auto-generated destructor stub
}
