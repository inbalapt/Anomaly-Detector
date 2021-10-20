#include <iostream>
#include "anomaly_detection_util.cpp"
int main() {
    float X[] = {0,1,2,3,4,5,6,7,8};
    float variable =var(X, (int)8);
    std::cout << variable << std::endl;
    return 0;

}
