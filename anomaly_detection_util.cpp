/*
 * anomaly_detection_util.cpp
 *
 * Author: Noa Leshem - 314665415
 * Inbal Apt - 207031006
 * on 10/20/21.
 */
#include "anomaly_detection_util.h"
#include <cmath>

/*
 * this function gets an array of floats and its size, and calculate its average.
 */
float E(float *x, int size) {
    float variable = 0;
    for (int i = 0; i < size; i++) {
        variable += x[i];
    }
    return (variable / size);
}

/*
 * this function gets an arrays of x floats and y floats and those sizes, and calculate the average of their multiply.
*/
float E(float *x, float *y, int size) {
    float variable = 0;
    for (int i = 0; i < size; i++) {
        variable += x[i] * y[i];
    }
    return (variable / size);
}


/*
 * returns the variance of X and Y
 */
float var(float *x, int size) {
    float variable = E(x, size);
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += (float) ((pow(x[i] - variable, 2)) / size);
    }
    return sum;
}

/*
 * returns the covariance of X and Y
 */
float cov(float *x, float *y, int size) {
    return E(x, y, size) - E(x, size) * E(y, size);
}

/*
 * returns the Pearson correlation coefficient of X and Y.
 */
float pearson(float *x, float *y, int size) {
    float xVarSqrt = sqrt(var(x, size));
    float yVarSqrt = sqrt(var(y, size));
    return cov(x, y, size) / (xVarSqrt * yVarSqrt);
}

Line linear_reg(Point **points, int size) {
    float pointsX[size];
    float pointsY[size];

    // make array of the X and Y of the points.
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

/*
 * performs a linear regression and return s the line equation.
 */
Line linear_reg(float *x, float *y, int size) {
    float a = cov(x, y, size) / var(x, size);
    float aveX = E(x, size);
    float aveY = E(y, size);
    float b = aveY - aveX * a;
    Line line;
    line.a = a;
    line.b = b;
    return line;

}

/*
 * returns the deviation between point p and the line equation of the points
 */
float dev(Point p, Point **points, int size) {
    Line line = linear_reg(points, size);
    return dev(p, line);
}

/*
 * returns the deviation between point p and the line
 */
float dev(Point p, Line l) {
    //the f(x) value of the point.
    float fx = l.f(p.x);
    float diff = fx - p.y;
    //change for absolute value.
    if (diff < 0) {
        diff = -diff;
    }
    return diff;
}