//
// Created by Noa Leshem and Inbal Apt on 10/20/21.
//
#include <iostream>
#include "anomaly_detection_util.h"
#include <cmath>

float E(float* x, int size) {
    float variable = 0;
    for (int i = 0; i < size; i++) {
        variable += (x[i] / size);
    }
    return variable;
}

// returns the variance of X and Y
float var(float* x, int size) {
    float variable = E(x, size);
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += (float)((pow(x[i] - variable, 2)) / size);
    }
    return sum;
}
// returns the covariance of X and Y
float cov(float* x, float* y, int size) {
    return 0;
}
// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size) {
    return 0;
}
// performs a linear regression and return s the line equation
Line linear_reg(Point** points, int size) {

}
// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size) {
return 0;
}
// returns the deviation between point p and the line
float dev(Point p,Line l) {
return 0;
}


