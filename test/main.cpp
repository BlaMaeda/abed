#include <iostream>
#include <vector>
#include "../include/dataset.hpp"
#include "../include/mlp.hpp"
#include "../include/tester.hpp"
#include "../include/perceptron.hpp"
#include "../include/bagging.hpp"
using namespace std;
using namespace abed;

int main () {
    Bagging bagging(3);
    StaticDataSet sds("iris.ssv");

    Tester tester(&bagging, &sds);

    tester.resubstitution();
    cout << tester.get_percentage() << endl;

    return 0;
}

