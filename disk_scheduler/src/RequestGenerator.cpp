/**
 * @file    RequestGenerator.cpp
 * @brief   Implementation of the RequestGenerator class.
 *
 * @course  Operating Systems — 300CIG011
 * @date    2025
 */

#include "RequestGenerator.h"
#include <algorithm>

using namespace std;

RequestGenerator::RequestGenerator(int cylinders, int requests, unsigned int seedValue)
    : totalCylinders(cylinders), numberOfRequests(requests), seed(seedValue) {}

vector<int> RequestGenerator::generate() const {
    mt19937 rng(seed);
    uniform_int_distribution<int> dist(0, totalCylinders - 1);
    vector<int> reqs(numberOfRequests);
    generate(reqs.begin(), reqs.end(), [&]() { return dist(rng); });
    return reqs;
}

unsigned int RequestGenerator::getSeed() const {
    return seed;
}
