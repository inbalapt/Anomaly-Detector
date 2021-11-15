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
            //change for absolute value.
            if (pears < 0) {
                pears = -pears;
            }
            if (pears > highestCor && pears > 0.9) {
                //setting the most correlative column.
                highestCor = pears;
                col = j;
            }
        }
        // associate f(i) and f(j) as correlated features. add it to cf
        if (col != -1) {
            Line line = linear_reg(&table[col].second[0], &table[i].second[0], rows);
            float threshold = 0;
            // find the biggest threshold, loop over all the dots.
            for (int k = 0; k < rows; k++) {
                float x = table[col].second[k];
                float y = table[i].second[k];
                float distance = dev(Point(x, y), line);
                // the highest threshold
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



vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    vector<AnomalyReport> report;
    for(correlatedFeatures corF: this->getNormalModel()) {
        string fea1 = corF.feature1;
        string fea2 = corF.feature2;
        vector<float> values1 = ts.get_feature_by_string(fea1);
        vector<float> values2 = ts.get_feature_by_string(fea2);

        for(int i = 0; i < values1.size(); i++) {
            Point p(values2.at(i), values1.at(i));
            if (dev(p, corF.lin_reg) > corF.threshold) {
                string description = fea1 + "-" + fea2;
                int time = i;
                report.emplace_back(description, time);
            }
        }
    }
}
