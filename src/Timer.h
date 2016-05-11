#pragma once

#include <chrono>

class Timer {
	public:
		static Timer* getInstance() {
			static Timer instance;
			return &instance;
		}

		void init();
		void update();
		// return ms
		int getTime();
		int getDiff();
	private:
		Timer() {}
		std::chrono::system_clock::time_point start;
		std::chrono::system_clock::time_point now;
		int prevtime;
		int time;
};
