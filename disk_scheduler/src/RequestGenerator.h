/**
 * @file    RequestGenerator.h
 * @brief   Generates a reproducible list of random disk cylinder requests.
 * @details Uses a Mersenne Twister engine to create a uniform distribution of requests.
 *
 * @course  Operating Systems — 300CIG011
 * @date    2025
 */

#ifndef REQUEST_GENERATOR_H
#define REQUEST_GENERATOR_H

#include <vector>
#include <random>

using namespace std;

class RequestGenerator {
private:
    int totalCylinders;
    int numberOfRequests;
    unsigned int seed;

public:
    /**
     * @brief   Constructs a RequestGenerator.
     * @param   cylinders   The total number of cylinders (e.g., 5000).
     * @param   requests    The number of requests to generate (e.g., 1000).
     * @param   seedValue   The seed for the random number generator for reproducibility.
     */
    explicit RequestGenerator(int cylinders, int requests, unsigned int seedValue = 42);

    /**
     * @brief   Generates the random requests.
     * @return  A vector of integers representing cylinder requests.
     */
    vector<int> generate() const;

    /**
     * @brief   Gets the seed used for generation.
     * @return  The seed value.
     */
    unsigned int getSeed() const;
};

#endif // REQUEST_GENERATOR_H
