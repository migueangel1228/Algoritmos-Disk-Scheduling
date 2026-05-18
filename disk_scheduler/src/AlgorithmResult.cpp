/**
 * @file    AlgorithmResult.cpp
 * @brief   Implementation of the AlgorithmResult class.
 *
 * @course  Operating Systems — 300CIG011
 * @date    2025
 */

#include "AlgorithmResult.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

AlgorithmResult::AlgorithmResult(const string& name, int movement, const vector<int>& order)
    : algorithmName(name), totalHeadMovement(movement), serviceOrder(order) {}

void AlgorithmResult::print() const {
    cout << "==========================================" << endl;
    cout << "Algorithm             : " << algorithmName << endl;
    cout << "Total Head Movement   : " << totalHeadMovement << " cylinders" << endl;
    cout << "==========================================" << endl;
}

string AlgorithmResult::toCsvRow(int initialHead, int totalCylinders, int totalRequests, unsigned int seed) const {
    stringstream ss;
    ss << algorithmName << ","
       << totalHeadMovement << ","
       << initialHead << ","
       << totalCylinders << ","
       << totalRequests << ","
       << seed;
    return ss.str();
}
