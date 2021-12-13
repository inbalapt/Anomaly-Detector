
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
    if (cor > 0.5) {
        
    }
}
