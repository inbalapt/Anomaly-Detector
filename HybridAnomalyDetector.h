

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();

    virtual void associateCorrelatedFeatures(int i, int j, float cor, vector<pair<std::string, std::vector<float>>> table, int rows);
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
