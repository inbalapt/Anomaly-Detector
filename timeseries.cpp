#include "timeseries.h"

std::vector<std::pair<std::string, std::vector<float>>> TimeSeries::getVector() {
    return this->tableVec;
}

int TimeSeries::getNumOfCol() const {
    return this->numOfCol;
}

int TimeSeries::getNumOfRows() const {
    return this->numOfRows;
}