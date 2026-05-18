/**
 * @file    ReportExporter.h
 * @brief   Exports simulation results to CSV files.
 * @details Handles the creation of summary, input, and service order trace files.
 *
 * @course  Operating Systems — 300CIG011
 * @date    2025
 */

#ifndef REPORT_EXPORTER_H
#define REPORT_EXPORTER_H

#include "AlgorithmResult.h"
#include <string>
#include <vector>

using namespace std;

class ReportExporter {
private:
    string outputPath;

public:
    /**
     * @brief   Constructs a ReportExporter.
     * @param   path    The directory where data files will be saved (e.g., "data/").
     */
    explicit ReportExporter(const string& path);

    /**
     * @brief   Exports a summary of all algorithm results to a single CSV file.
     * @param   results         A vector of AlgorithmResult objects.
     * @param   initialHead     The starting head position.
     * @param   totalCylinders  The total number of cylinders.
     * @param   totalRequests   The total number of requests.
     * @param   seed            The seed used for request generation.
     */
    void exportResults(const vector<AlgorithmResult>& results, int initialHead, int totalCylinders, int totalRequests, unsigned int seed) const;

    /**
     * @brief   Exports the service order of a single algorithm to a dedicated CSV file.
     * @param   result  The AlgorithmResult object to export.
     */
    void exportServiceOrder(const AlgorithmResult& result) const;

    /**
     * @brief   Exports the generated requests, seed, and initial settings to a CSV file.
     * @param   requests        The vector of generated cylinder requests.
     * @param   seed            The seed used for generation.
     * @param   initialHead     The starting head position.
     * @param   totalCylinders  The total number of cylinders.
     */
    void exportGeneratedRequests(const vector<int>& requests, unsigned int seed, int initialHead, int totalCylinders) const;
};

#endif // REPORT_EXPORTER_H
