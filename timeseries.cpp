#include "timeseries.h"

std::vector<std::pair<std::string, std::vector<float>>> TimeSeries::getVector() const {
    return this->tableVec;
}

int TimeSeries::getNumOfCol() const {
    return this->tableVec.size();
}

int TimeSeries::getNumOfRows() const {
    return this->tableVec.at(0).second.size();
}

std::vector<float> TimeSeries::get_feature_by_string(string str) const {
    int numOfCol = this->getNumOfCol();
    for (int i = 0 ; i < numOfCol; i++) {
        if(this->getVector().at(i).first == str) return this->getVector().at(i).second;
    }

}