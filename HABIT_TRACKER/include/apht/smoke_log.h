#pragma once
#include <chrono>
#include <string>
#include <vector>
#include "apht/cig_log.h"

class SmokingTracker {
public:
    void addLog(std::chrono::system_clock::time_point timestamp, int craving_level); // timestamp will default to the instant it is logged..keeping it as a param in case one forgets to add log at the time of smoking
    void deleteLog(const std::string& id);
    std::vector<CigaretteLog> getLogs(std::chrono::system_clock::time_point start_time, std::chrono::system_clock::time_point end_time);
private:
    std::vector<CigaretteLog> cig_logs;
};