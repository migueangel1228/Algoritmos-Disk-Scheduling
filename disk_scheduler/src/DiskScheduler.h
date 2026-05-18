/**
 * @file    DiskScheduler.h
 * @brief   Simulates FCFS, SCAN, and C-SCAN disk scheduling algorithms.
 * @details Orchestrates the execution of algorithms on a given set of requests.
 *
 * @course  Operating Systems — 300CIG011
 * @date    2025
 */

#ifndef DISK_SCHEDULER_H
#define DISK_SCHEDULER_H

#include "AlgorithmResult.h"
#include <vector>

using namespace std;

class DiskScheduler {
private:
    const int totalCylinders;
    int initialHeadPosition;
    vector<int> requests;

    /**
     * @brief   Calculates the total head movement for a given service order.
     * @param   serviceOrder    The sequence of serviced cylinders.
     * @param   startPos        The initial position of the disk head.
     * @return  The total number of cylinders the head has moved.
     */
    int computeTotalMovement(const vector<int>& serviceOrder, int startPos) const;

public:
    /**
     * @brief   Constructs a DiskScheduler.
     * @param   cylinders   The total number of cylinders on the disk.
     * @param   headPos     The initial position of the disk head.
     * @param   reqs        The vector of cylinder requests to process.
     */
    DiskScheduler(int cylinders, int headPos, const vector<int>& reqs);

    /**
     * @brief   Runs the First-Come, First-Served (FCFS) algorithm.
     * @return  An AlgorithmResult object containing the simulation results.
     */
    AlgorithmResult runFCFS() const;

    /**
     * @brief   Runs the SCAN (Elevator) algorithm.
     * @return  An AlgorithmResult object containing the simulation results.
     */
    AlgorithmResult runSCAN() const;

    /**
     * @brief   Runs the C-SCAN (Circular SCAN) algorithm.
     * @return  An AlgorithmResult object containing the simulation results.
     */
    AlgorithmResult runCSCAN() const;
};

#endif // DISK_SCHEDULER_H
