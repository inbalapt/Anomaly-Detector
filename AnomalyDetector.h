//
// Created by inbal on 11/14/21.
//

#ifndef AS1_ANOMALYDETECTOR_H
#define AS1_ANOMALYDETECTOR_H

class TimeSeries{ /*...*/};
class AnomalyReport{
public:
    const string description;
    const long timeStep;
    AnomalyReport(string description, long timeStep) :
            description(description),timeStep(timeStep){}
};
class TimeSeriesAnomalyDetector {
public:
    virtual void learnNormal(const TimeSeries& ts)=0;
    virtual vector<AnomalyReport> detect(const TimeSeries& ts)=0;
    virtual ~TimeSeriesAnomalyDetector(){}
};


#endif //AS1_ANOMALYDETECTOR_H
