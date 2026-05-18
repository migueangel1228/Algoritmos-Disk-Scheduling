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

AlgorithmResult::AlgorithmResult(const std::string& name, int movement, const std::vector<int>& order)
    : algorithmName(name), totalHeadMovement(movement), serviceOrder(order) {}

void AlgorithmResult::print() const {
    std::cout << "==========================================" << std::endl;
    std::cout << "Algorithm             : " << algorithmName << std::endl;
    std::cout << "Total Head Movement   : " << totalHeadMovement << " cylinders" << std::endl;
    std::cout << "==========================================" << std::endl;
}

std::string AlgorithmResult::toCsvRow(int initialHead, int totalCylinders, int totalRequests, unsigned int seed) const {
    std::stringstream ss;
    ss << algorithmName << ","
       << totalHeadMovement << ","
       << initialHead << ","
       << totalCylinders << ","
       << totalRequests << ","
       << seed;
    return ss.str();
}
