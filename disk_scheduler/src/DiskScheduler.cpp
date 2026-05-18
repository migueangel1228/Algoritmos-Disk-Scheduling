/**
 * @file    DiskScheduler.cpp
 * @brief   Implementation of the DiskScheduler class.
 *
 * @course  Operating Systems — 300CIG011
 * @date    2025
 */

#include "DiskScheduler.h"
#include <numeric>
#include <algorithm>
#include <cmath>

using namespace std;

DiskScheduler::DiskScheduler(int cylinders, int headPos, const vector<int>& reqs)
    : totalCylinders(cylinders), initialHeadPosition(headPos), requests(reqs) {}

int DiskScheduler::computeTotalMovement(const vector<int>& serviceOrder, int startPos) const {
    int totalMovement = 0;
    int currentPos = startPos;
    for (const int& req : serviceOrder) {
        totalMovement += abs(req - currentPos);
        currentPos = req;
    }
    return totalMovement;
}

AlgorithmResult DiskScheduler::runFCFS() const {
    return AlgorithmResult("FCFS", computeTotalMovement(requests, initialHeadPosition), requests);
}

AlgorithmResult DiskScheduler::runSCAN() const {
    vector<int> serviceOrder;
    vector<int> lower, upper;
    
    for (const int& req : requests) {
        if (req < initialHeadPosition) {
            lower.push_back(req);
        } else {
            upper.push_back(req);
        }
    }

    sort(upper.begin(), upper.end());
    sort(lower.begin(), lower.end(), greater<int>());

    serviceOrder.insert(serviceOrder.end(), upper.begin(), upper.end());
    serviceOrder.insert(serviceOrder.end(), lower.begin(), lower.end());

    int totalMovement = 0;
    if (!requests.empty()) {
        totalMovement = (totalCylinders - 1 - initialHeadPosition) + (totalCylinders - 1 - lower.front());
    }
    
    return AlgorithmResult("SCAN", totalMovement, serviceOrder);
}

AlgorithmResult DiskScheduler::runCSCAN() const {
    vector<int> serviceOrder;
    vector<int> lower, upper;

    for (const int& req : requests) {
        if (req < initialHeadPosition) {
            lower.push_back(req);
        } else {
            upper.push_back(req);
        }
    }

    sort(upper.begin(), upper.end());
    sort(lower.begin(), lower.end());

    serviceOrder.insert(serviceOrder.end(), upper.begin(), upper.end());
    serviceOrder.insert(serviceOrder.end(), lower.begin(), lower.end());
    
    int totalMovement = 0;
    if (!requests.empty()) {
        totalMovement = (totalCylinders - 1 - initialHeadPosition) + (totalCylinders - 1) + lower.back();
    }

    return AlgorithmResult("CSCAN", totalMovement, serviceOrder);
}
