/**
 * @file    main.cpp
 * @brief   Main entry point for the Disk Scheduling Simulator.
 * @details Parses command-line arguments, orchestrates the simulation, and reports results.
 *
 * @course  Operating Systems — 300CIG011
 * @date    2025
 */

#include <iostream>
#include <string>
#include <vector>
#include "RequestGenerator.h"
#include "DiskScheduler.h"
#include "ReportExporter.h"

const int TOTAL_CYLINDERS = 5000;
const int NUM_REQUESTS = 1000;

void printUsage(const char* progName) {
    std::cerr << "Usage: " << progName << " <initial_head_position>" << std::endl;
    std::cerr << "  <initial_head_position> must be an integer between 0 and " << TOTAL_CYLINDERS - 1 << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printUsage(argv[0]);
        return 1;
    }

    int initialHeadPosition = 0;
    try {
        initialHeadPosition = std::stoi(argv[1]);
        if (initialHeadPosition < 0 || initialHeadPosition >= TOTAL_CYLINDERS) {
            throw std::out_of_range("Initial head position out of valid range.");
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "[ERROR] Invalid argument: Not an integer." << std::endl;
        printUsage(argv[0]);
        return 1;
    } catch (const std::out_of_range& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
        printUsage(argv[0]);
        return 1;
    }

    RequestGenerator generator(TOTAL_CYLINDERS, NUM_REQUESTS);
    std::vector<int> requests = generator.generate();
    unsigned int seed = generator.getSeed();

    DiskScheduler scheduler(TOTAL_CYLINDERS, initialHeadPosition, requests);

    AlgorithmResult fcfsResult = scheduler.runFCFS();
    AlgorithmResult scanResult = scheduler.runSCAN();
    AlgorithmResult cscanResult = scheduler.runCSCAN();

    std::cout << "Initial Head Position : " << initialHeadPosition << std::endl;
    std::cout << "Total Cylinders       : " << TOTAL_CYLINDERS << std::endl;
    std::cout << "Total Requests        : " << NUM_REQUESTS << std::endl;
    
    fcfsResult.print();
    scanResult.print();
    cscanResult.print();

    ReportExporter exporter("data/");
    std::vector<AlgorithmResult> allResults = {fcfsResult, scanResult, cscanResult};
    
    exporter.exportResults(allResults, initialHeadPosition, TOTAL_CYLINDERS, NUM_REQUESTS, seed);
    exporter.exportGeneratedRequests(requests, seed, initialHeadPosition, TOTAL_CYLINDERS);
    exporter.exportServiceOrder(fcfsResult);
    exporter.exportServiceOrder(scanResult);
    exporter.exportServiceOrder(cscanResult);

    return 0;
}
