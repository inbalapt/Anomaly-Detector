/*
 * timeseries.cpp
 *
 * Author: Noa Leshem - 314665415
 * Inbal Apt - 207031006
 * on 10/20/21.
 */

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
        // if the string is found as one of the features name, returns its vector of values.
        if(this->getVector().at(i).first == str){
            return this->getVector().at(i).second;
        }
    }
}