#pragma once
#include <string>
#include <chrono>

struct CigaretteLog {
	std::string id;
	std::chrono::system_clock::time_point timestamp;
	int craving_level; // 1 - 5
};