#include <thread>
#include <chrono>
#include "timer.hpp"

void Timer::decrement_time(int &time, bool &running) {
	while (running) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		time--;
	}
}
