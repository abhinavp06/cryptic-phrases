#include <algorithm>
#include <chrono>
#include <random>
#include <string>
#include "apht/log/cigarette_log.h"
#include "apht/tracker/smoking_tracker.h"

std::string generateID(size_t length) {
    const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, characters.size() - 1);

    std::string id;
    for (size_t i = 0; i < length; ++i) {
        id += characters[dis(gen)];
    }
    return id;
}

void SmokingTracker::addLog(std::chrono::system_clock::time_point timestamp, int craving_level) {
	CigaretteLog cig_log;
	cig_log.timestamp = timestamp == NULL ? std::chrono::system_clock::now() : timestamp;
	cig_log.craving_level = craving_level;

    std::string id = generateID(6);
    cig_log.id = id;

    cig_logs[id] = cig_log;
}

void SmokingTracker::deleteLog(const std::string& id) {
    cig_logs.erase(id);
}

std::vector<CigaretteLog> SmokingTracker::getLogs(
    std::chrono::system_clock::time_point start_time,
    std::chrono::system_clock::time_point end_time
) {
    std::vector<CigaretteLog> result;

    for (const auto& [id, log] : cig_logs) {
        if (log.timestamp >= start_time && log.timestamp <= end_time) {
            result.push_back(log);
        }
    }


    std::sort(result.begin(), result.end(),
        [](const CigaretteLog& a, const CigaretteLog& b) {
            return a.timestamp < b.timestamp;
        });

    return result;
}