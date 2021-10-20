//
// Created by Noa Leshem and Inbal Apt on 10/20/21.
//
#include <iostream>
#include "anomaly_detection_util.h"

// returns the variance of X and Y
float var(float* x, int size) {
    std::cout << "Hello, World!" << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;

}
// returns the covariance of X and Y
float cov(float* x, float* y, int size) {
    std::cout << "Hello, World!" << std::endl;
}
// returns the Pearson correlation coefficient of X and Y
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
// performs a linear regression and return s the line equation
Line linear_reg(Point** points, int size);
// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size);
// returns the deviation between point p and the line
float dev(Point p,Line l);

