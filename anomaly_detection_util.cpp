//
// Created by Noa Leshem - 314665415, and Inbal Apt - 207031006 on 10/20/21.
//
#include <iostream>
#include "anomaly_detection_util.h"
#include <cmath>

/**
 * this function gets an array of floats and its size, and calculate its average.
 * @param x
 * @param size
 * @return float
 */
float E(float* x, int size) {
    float variable = 0;
    for (int i = 0; i < size; i++) {
        variable += (x[i] / size);
    }
    return variable;
}

/**
 * this function gets an arrays of x floats and y floats and those sizes, and calculate the average of their multiply.
 * @param x
 * @param y
 * @param size
 * @return float
 */
float E(float* x, float* y, int size) {
    float variable;
    for (int i = 0; i < size; i++){
        variable += x[i] * y[i] / size;
    }
}


float var(float* x, int size) {
    float variable = E(x, size);
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += (float)((pow(x[i] - variable, 2)) / size);
    }
    return sum;
}

float cov(float* x, float* y, int size) {
    return E(x, y, size) - E(x, size) * E(y, size);
}

float pearson(float* x, float* y, int size) {
    float xVarSqrt = sqrt(var(x, size));
    float yVarSqrt = sqrt(var(y, size));
    return cov(x, y, size) / (xVarSqrt * yVarSqrt);

}

Line linear_reg(Point** points, int size) {
    float pointsX[size];
    float pointsY[size];
    for (int i = 0; i < size; i++) {
        pointsX[i] = points[i]->x;
        pointsY[i] = points[i]->y;
    }
    float a = cov(pointsX, pointsY, size) / var(pointsX, size);
    float aveX = E(pointsX, size);
    float aveY = E(pointsY, size);
    float b = aveY - aveX * a;
    Line line;
    line.a = a;
    line.b = b;
    return line;
}

float dev(Point p,Point** points, int size) {
return 0;
}

float dev(Point p,Line l) {
return 0;
}


