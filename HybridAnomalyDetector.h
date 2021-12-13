/*
 * HybridAnomalyDetector.h
 *
 * Author: Noa Leshem - 314665415
 * Inbal Apt - 207031006
 * on 10/20/21.
 */

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();

    virtual void associateCorrelatedFeatures(int i, int j, float cor, vector<pair<std::string, std::vector<float>>> table, int rows);
    virtual void addReport(const TimeSeries &ts, const correlatedFeatures &corF, vector<AnomalyReport> &report);
    Point **vectorsToArray(float *x, float *y, size_t size);
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
