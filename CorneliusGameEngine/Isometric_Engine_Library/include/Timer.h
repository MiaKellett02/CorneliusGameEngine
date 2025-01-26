#pragma once

//Library includes.
#include <chrono>
#include <string>

//Project includes.
#include "Logging.h"

//Declarations.
struct Timer {
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float, std::milli> duration;
	std::string timerName;

	Timer(std::string a_timerName) {
		start = std::chrono::high_resolution_clock::now();
		timerName = a_timerName;
	}

	~Timer() {
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;

		float ms = duration.count();
		std::cout << timerName << " took " << ms << "ms" << std::endl;
	}
};