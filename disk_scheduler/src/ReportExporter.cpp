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

ReportExporter::ReportExporter(const std::string& path) : outputPath(path) {}

void ReportExporter::exportResults(const std::vector<AlgorithmResult>& results, int initialHead, int totalCylinders, int totalRequests, unsigned int seed) const {
    std::string filePath = outputPath + "results.csv";
    std::ofstream outFile(filePath);

    if (outFile.is_open()) {
        outFile << "Algorithm,TotalMovement,InitialHead,Cylinders,TotalRequests,Seed\n";
        for (const auto& result : results) {
            outFile << result.toCsvRow(initialHead, totalCylinders, totalRequests, seed) << "\n";
        }
        outFile.close();
        std::cout << "[OK] " << filePath << std::endl;
    } else {
        std::cerr << "[ERROR] Could not open file: " << filePath << std::endl;
    }
}

void ReportExporter::exportServiceOrder(const AlgorithmResult& result) const {
    std::string filePath = outputPath + "service_order_" + result.algorithmName + ".csv";
    std::ofstream outFile(filePath);

    if (outFile.is_open()) {
        outFile << "ServiceStep,CylinderNumber\n";
        int step = 0;
        for (const auto& cylinder : result.serviceOrder) {
            outFile << step++ << "," << cylinder << "\n";
        }
        outFile.close();
        std::cout << "[OK] " << filePath << std::endl;
    } else {
        std::cerr << "[ERROR] Could not open file: " << filePath << std::endl;
    }
}

void ReportExporter::exportGeneratedRequests(const std::vector<int>& requests, unsigned int seed, int initialHead, int totalCylinders) const {
    std::string filePath = outputPath + "input_requests.csv";
    std::ofstream outFile(filePath);

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
        std::cout << "[OK] " << filePath << std::endl;
    } else {
        std::cerr << "[ERROR] Could not open file: " << filePath << std::endl;
    }
}
