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

using namespace std;

const int TOTAL_CYLINDERS = 5000;
const int NUM_REQUESTS = 1000;

void printUsage(const char* progName) {
    cerr << "Usage: " << progName << " <initial_head_position>" << endl;
    cerr << "  <initial_head_position> must be an integer between 0 and " << TOTAL_CYLINDERS - 1 << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printUsage(argv[0]);
        return 1;
    }

    int initialHeadPosition = 0;
    try {
        initialHeadPosition = stoi(argv[1]);
        if (initialHeadPosition < 0 || initialHeadPosition >= TOTAL_CYLINDERS) {
            throw out_of_range("Initial head position out of valid range.");
        }
    } catch (const invalid_argument& e) {
        cerr << "[ERROR] Invalid argument: Not an integer." << endl;
        printUsage(argv[0]);
        return 1;
    } catch (const out_of_range& e) {
        cerr << "[ERROR] " << e.what() << endl;
        printUsage(argv[0]);
        return 1;
    }

    RequestGenerator generator(TOTAL_CYLINDERS, NUM_REQUESTS);
    vector<int> requests = generator.generate();
    unsigned int seed = generator.getSeed();

    DiskScheduler scheduler(TOTAL_CYLINDERS, initialHeadPosition, requests);

    AlgorithmResult fcfsResult = scheduler.runFCFS();
    AlgorithmResult scanResult = scheduler.runSCAN();
    AlgorithmResult cscanResult = scheduler.runCSCAN();

    cout << "Initial Head Position : " << initialHeadPosition << endl;
    cout << "Total Cylinders       : " << TOTAL_CYLINDERS << endl;
    cout << "Total Requests        : " << NUM_REQUESTS << endl;
    
    fcfsResult.print();
    scanResult.print();
    cscanResult.print();

    ReportExporter exporter("data/");
    vector<AlgorithmResult> allResults = {fcfsResult, scanResult, cscanResult};
    
    exporter.exportResults(allResults, initialHeadPosition, TOTAL_CYLINDERS, NUM_REQUESTS, seed);
    exporter.exportGeneratedRequests(requests, seed, initialHeadPosition, TOTAL_CYLINDERS);
    exporter.exportServiceOrder(fcfsResult);
    exporter.exportServiceOrder(scanResult);
    exporter.exportServiceOrder(cscanResult);

    return 0;
}
