/*
 * minCircle.cpp
 *
 * Author: Noa Leshem - 314665415
 * Inbal Apt - 207031006
 * on 10/20/21.
 */
#include "minCircle.h"

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

// Defining infinity
const double INF = 1e18;

/*
 * return the euclidean distance between two points.
 */
double dist(const Point& a, const Point& b)
{
    int powX = pow(a.x - b.x, 2);
    int powY = pow(a.y - b.y, 2);
    return sqrt(powX + powY);
}

/*
 * check whether a point lies inside or on the boundaries of the circle.
 */
bool is_inside(const Circle& c, const Point& p)
{
    return dist(c.center, p) <= c.radius;
}

// The following two functions are used
// To find the equation of the circle when
// three points are given.

/*
 * Helper method to get a circle defined by 3 points.
 */
Point get_circle_center(double bx, double by,
                        double cx, double cy)
{
    double B = bx * bx + by * by;
    double C = cx * cx + cy * cy;
    double D = bx * cy - by * cx;
    return { float((cy * B - by * C) / (2 * D)),
             float((bx * C - cx * B) / (2 * D)) };
}


/*
 * return a unique circle that intersects three points.
 */
Circle circle_from(const Point& A, const Point& B, const Point& C)
{
    Point center = get_circle_center(B.x - A.x, B.y - A.y,
                                C.x - A.x, C.y - A.y);

    center.x += A.x;
    center.y += A.y;
    return { center, float(dist(center, A)) };
}

/*
 * return the smallest circle that intersects 2 points.
 */
Circle circle_from(const Point& A, const Point& B)
{
    // Set the center to be the midpoint of A and B
    Point C = { float((A.x + B.x) / 2.0), float((A.y + B.y) / 2.0) };

    // Set the radius to be half the distance AB
    return { C, float(dist(A, B) / 2.0) };
}

/*
 * check whether a circle encloses the given points.
 */
bool is_valid_circle(const Circle& c,
                     const vector<Point>& P)
{
    // Iterating through all the points to check whether the points lie inside the circle or not
    for (const Point& p : P)
        if (!is_inside(c, p))
            return false;
    return true;
}

/*
 * return the minimum enclosing circle for N <= 3
 */
Circle min_circle_trivial(vector<Point>& P)
{
    assert(P.size() <= 3);
    if (P.empty()) {
        return { { 0, 0 }, 0 };
    }
    else if (P.size() == 1) {
        return { P[0], 0 };
    }
    else if (P.size() == 2) {
        return circle_from(P[0], P[1]);
    }

    // To check if MEC can be determined by 2 points only
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {

            Circle c = circle_from(P[i], P[j]);
            if (is_valid_circle(c, P))
                return c;
        }
    }
    return circle_from(P[0], P[1], P[2]);
}

/*
 * Returns the MEC using Welzl's algorithm Takes a set of input points P and a set R points on the circle boundary.
 * n represents the number of points in P that are not yet processed.
 */
Circle welzl_helper(Point** points,
                    vector<Point> R, int n)
{
    // Base case when all points processed or |R| = 3
    if (n == 0 || R.size() == 3) {
        return min_circle_trivial(R);
    }

    Point p = *points[0];

    // Put the picked point at the end of since it's more efficient the deleting from the middle of the vector
    swap(*points[0], *points[n - 1]);

    // Get the MEC circle d from the set of points P - {p}
    Circle d = welzl_helper(points, R, n - 1);

    // If d contains p, return d
    if (is_inside(d, p)) {
        return d;
    }

    // Otherwise, must be on the boundary of the MEC
    R.push_back(p);

    // Return the MEC for P - {p} and R U {p}
    return welzl_helper(points, R, n - 1);
}

/*
 * returns the minimum circle.
 */
Circle findMinCircle(Point** points, size_t size) {
    return welzl_helper(points, {}, size);
}
