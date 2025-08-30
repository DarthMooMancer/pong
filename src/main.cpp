#include <iostream>
#include <thread>
#include "input.hpp"
#include "window.hpp"
#include "elements.hpp"

int main() {
	bool running = true;
	Input input;
	Window window;
	Paddle left(1);
	Paddle right(18);
	std::thread input_thread(&Input::get_input, &input, std::ref(running), std::ref(left), std::ref(right));
	while (running) {
		window.update_display(left, right);
		left.get_new_pos(1);
		right.get_new_pos(18);
	}

	input_thread.join();
	return 0;
}
