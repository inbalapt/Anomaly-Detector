//
// Created by inbal on 11/14/21.
//

#ifndef AS1_SIMPLEANOMALYDETECTOR_H
#define AS1_SIMPLEANOMALYDETECTOR_H

struct correlatedFeatures{
    string feature1,feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
};
class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
public:
    SimpleAnomalyDetector();
    virtual ~SimpleAnomalyDetector();
    virtual void learnNormal(const TimeSeries& ts);
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    vector<correlatedFeatures> getNormalModel();
};

#endif //AS1_SIMPLEANOMALYDETECTOR_H
