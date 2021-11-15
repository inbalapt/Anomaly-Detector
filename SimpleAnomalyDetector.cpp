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


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){

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
