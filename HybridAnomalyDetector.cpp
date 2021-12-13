
#include "HybridAnomalyDetector.h"

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
        float threshold = 0;
        Point *points[rows];
        for(int k = 0; k < rows; k++) {
            float x = table[i].second[k];
            float y = table[j].second[k];
            points[k] = new Point(x, y);
        }

        Circle circle = findMinCircle(points,rows);
        threshold = 1.1 * threshold;
        correlatedFeatures core = {
                table[i].first,
                table[j].first,
                cor,
                line,
                threshold
                circle
        };
        // Add to the list of cf
        this->cf.push_back(core);
    }
}
