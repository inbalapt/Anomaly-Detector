
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

        correlatedFeatures core = {
                table[i].first,
                table[j].first,
                cor,
                line,
                threshold
        };
        // Add to the list of cf
        this->cf.push_back(core);
    }
}
