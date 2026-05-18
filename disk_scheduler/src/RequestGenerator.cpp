/**
 * @file    RequestGenerator.cpp
 * @brief   Implementation of the RequestGenerator class.
 *
 * @course  Operating Systems — 300CIG011
 * @date    2025
 */

#include "RequestGenerator.h"
#include <algorithm>

RequestGenerator::RequestGenerator(int cylinders, int requests, unsigned int seedValue)
    : totalCylinders(cylinders), numberOfRequests(requests), seed(seedValue) {}

std::vector<int> RequestGenerator::generate() const {
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(0, totalCylinders - 1);
    std::vector<int> reqs(numberOfRequests);
    std::generate(reqs.begin(), reqs.end(), [&]() { return dist(rng); });
    return reqs;
}

unsigned int RequestGenerator::getSeed() const {
    return seed;
}
