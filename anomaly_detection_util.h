//
// Created by Noa Leshem - 314665415, and Inbal Apt - 207031006 on 10/20/21.
//

#ifndef AS1_ANOMALY_DETECTION_UTIL_H
#define AS1_ANOMALY_DETECTION_UTIL_H

/**
 * this function returns the variance of X and Y.
 * @param x
 * @param size
 * @return float
 */
float var(float* x, int size);

/**
 * returns the covariance of X and Y.
 * @param x
 * @param y
 * @param size
 * @return float
 */
float cov(float* x, float* y, int size);

/**
 * returns the Pearson correlation coefficient of X and Y.
 * @param x
 * @param y
 * @param size
 * @return float
 */
float pearson(float* x, float* y, int size);
class Line{
public:
    float a,b;
    Line():a(0),b(0){}
    Line(float a, float b):a(a),b(b){}
    float f(float x){
        return a*x+b;
    }
};
class Point{
public:
    float x,y;
    Point(float x, float y):x(x),y(x){}
};

/**
 * performs a linear regression and return s the line equation.
 * @param points
 * @param size
 * @return Line
 */
Line linear_reg(Point** points, int size);
Line linear_reg(float *x, float *y, int size);
/**
 * returns the deviation between point p and the line equation of the points.
 * @param p
 * @param points
 * @param size
 * @return float
 */
float dev(Point p,Point** points, int size);

/**
 * returns the deviation between point p and the line.
 * @param p
 * @param l
 * @return float
 */
float dev(Point p,Line l);

#endif //AS1_ANOMALY_DETECTION_UTIL_H
