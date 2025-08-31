#include <thread>
#include <chrono>
#include "timer.hpp"

void Timer::decrement_time(int &time, bool &running, bool &timer_active) {
	while (running) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		time--;
		if(time <= 0) {
			timer_active = false;
		}
	}

}
