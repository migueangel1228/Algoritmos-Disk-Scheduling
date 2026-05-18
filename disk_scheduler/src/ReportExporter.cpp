/**
 * @file    ReportExporter.cpp
 * @brief   Implementation of the ReportExporter class.
 *
 * @course  Operating Systems — 300CIG011
 * @date    2025
 */

#include "ReportExporter.h"
#include <fstream>
#include <iostream>

using namespace std;

ReportExporter::ReportExporter(const string& path) : outputPath(path) {}

void ReportExporter::exportResults(const vector<AlgorithmResult>& results, int initialHead, int totalCylinders, int totalRequests, unsigned int seed) const {
    string filePath = outputPath + "results.csv";
    ofstream outFile(filePath);

    if (outFile.is_open()) {
        outFile << "Algorithm,TotalMovement,InitialHead,Cylinders,TotalRequests,Seed\n";
        for (const auto& result : results) {
            outFile << result.toCsvRow(initialHead, totalCylinders, totalRequests, seed) << "\n";
        }
        outFile.close();
        cout << "[OK] " << filePath << endl;
    } else {
        cerr << "[ERROR] Could not open file: " << filePath << endl;
    }
}

void ReportExporter::exportServiceOrder(const AlgorithmResult& result) const {
    string filePath = outputPath + "service_order_" + result.algorithmName + ".csv";
    ofstream outFile(filePath);

    if (outFile.is_open()) {
        outFile << "ServiceStep,CylinderNumber\n";
        int step = 0;
        for (const auto& cylinder : result.serviceOrder) {
            outFile << step++ << "," << cylinder << "\n";
        }
        outFile.close();
        cout << "[OK] " << filePath << endl;
    } else {
        cerr << "[ERROR] Could not open file: " << filePath << endl;
    }
}

void ReportExporter::exportGeneratedRequests(const vector<int>& requests, unsigned int seed, int initialHead, int totalCylinders) const {
    string filePath = outputPath + "input_requests.csv";
    ofstream outFile(filePath);

    if (outFile.is_open()) {
        outFile << "# Seed: " << seed << "\n";
        outFile << "# InitialHead: " << initialHead << "\n";
        outFile << "# TotalCylinders: " << totalCylinders << "\n";
        outFile << "# TotalRequests: " << requests.size() << "\n";
        outFile << "RequestIndex,CylinderNumber\n";
        for (size_t i = 0; i < requests.size(); ++i) {
            outFile << i << "," << requests[i] << "\n";
        }
        outFile.close();
        cout << "[OK] " << filePath << endl;
    } else {
        cerr << "[ERROR] Could not open file: " << filePath << endl;
    }
}
