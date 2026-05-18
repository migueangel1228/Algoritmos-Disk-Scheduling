/**
 * @file    AlgorithmResult.h
 * @brief   Represents the result of a single disk scheduling algorithm execution.
 * @details Stores the algorithm's name, total head movement, and the sequence of serviced cylinders.
 *
 * @course  Operating Systems — 300CIG011
 * @date    2025
 */

#ifndef ALGORITHM_RESULT_H
#define ALGORITHM_RESULT_H

#include <bits/stdc++.h>

using namespace std;

class AlgorithmResult {
public:
    string algorithmName;
    int totalHeadMovement;
    vector<int> serviceOrder;

    /**
     * @brief   Constructs an AlgorithmResult object.
     * @param   name        The name of the algorithm.
     * @param   movement    The total head movement.
     * @param   order       The sequence of serviced cylinders.
     */
    AlgorithmResult(const string& name, int movement, const vector<int>& order);

    /**
     * @brief   Prints a formatted summary of the result to the console.
     */
    void print() const;

    /**
     * @brief   Serializes the result summary to a single CSV row string.
     * @param   initialHead     The starting head position.
     * @param   totalCylinders  The total number of cylinders on the disk.
     * @param   totalRequests   The total number of requests.
     * @param   seed            The seed used for request generation.
     * @return  A string formatted as a CSV row.
     */
    string toCsvRow(int initialHead, int totalCylinders, int totalRequests, unsigned int seed) const;
};

#endif // ALGORITHM_RESULT_H
