/*
 * HybridAnomalyDetector.cpp
 *
 * Author: Noa Leshem - 314665415
 * Inbal Apt - 207031006
 * on 10/20/21.
 */

#include "HybridAnomalyDetector.h"
#include "minCircle.h"
// default constructor
HybridAnomalyDetector::HybridAnomalyDetector() {
    // TODO Auto-generated constructor stub

}

// default destructor
HybridAnomalyDetector::~HybridAnomalyDetector() {
    // TODO Auto-generated destructor stub
}

void HybridAnomalyDetector::associateCorrelatedFeatures(int i, int j, float cor,
                                                        vector<std::pair<std::string, std::vector<float>>> table,
                                                        int rows) {
    SimpleAnomalyDetector::associateCorrelatedFeatures(i, j, cor, table, rows);
    if (cor > 0.5 && cor < 0.9) {
        Line line = linear_reg(&table[i].second[0], &table[j].second[0], rows);

        Point *points[rows];
        for(int k = 0; k < rows; k++) {
            float x = table[i].second[k];
            float y = table[j].second[k];
            points[k] = new Point(x, y);
        }

        Circle circle = findMinCircle(points,rows);
        float threshold = circle.radius;
        threshold = 1.1 * threshold;
        correlatedFeatures core = {
                table[i].first,
                table[j].first,
                cor,
                line,
                threshold,
                circle
        };
        // Add to the list of cf
        this->cf.push_back(core);
    }
}

double distance(const Point& a, const Point& b)
{
    int powX = pow(a.x - b.x, 2);
    int powY = pow(a.y - b.y, 2);
    return sqrt(powX + powY);
}

void HybridAnomalyDetector::addReport(const TimeSeries &ts, const correlatedFeatures &corF,
                                      vector<AnomalyReport> &report) {
    SimpleAnomalyDetector::addReport(ts,corF,report);
    if (corF.corrlation > 0.5 && corF.corrlation < 0.9) {
        string fea1 = corF.feature1;
        string fea2 = corF.feature2;
        // The x and vectors.
        const vector<float> values1 = ts.get_feature_by_string(fea1);
        const vector<float> values2 = ts.get_feature_by_string(fea2);
        int size = (int) values1.size();
        // Running over the values of the features
        for (int i = 0; i < size; i++) {
            float x = values1[i];
            float y = values2[i];

            if (!(distance(corF.circle.center, Point(x,y)) <= corF.threshold)) {
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
}
