#include <iostream>
#include <thread>
#include "input.hpp"
#include "window.hpp"

bool running = true;
Input input;
Window window;
std::thread input_thread(&Input::get_input, &input, std::ref(running));

int main() {
	while (running) {
		window.update_display();
	}

	input_thread.join();
	return 0;
}
