#include <iostream>
#include <thread>
#include "input.hpp"
#include "timer.hpp"
#include "window.hpp"
#include "elements.hpp"

int main() {
	bool running = true;
	Input input;
	Timer timer;
	Window window;
	Paddle left(1);
	Paddle right(19);
	Ball ball;
	int time = 90;
	bool timer_active = true;
	std::thread timer_thread(&Timer::decrement_time, &timer, std::ref(time), std::ref(running), std::ref(timer_active));
	std::thread input_thread(&Input::get_input, &input, std::ref(running), std::ref(left), std::ref(right));
	while (running) {
		window.update_display(left, right, ball, time);
		left.get_new_pos(1);
		right.get_new_pos(19);
		ball.get_new_pos();
		ball.check_collision();
		left.check_collision(ball);
		right.check_collision(ball);
		if (ball.m_goal && ball.m_origin.m_col < (ROW / 2)) {
			ball.m_goal = false;
			right.m_score++;
			ball.m_origin.assign(5, 10);
		} else if(ball.m_goal && ball.m_origin.m_col > (ROW / 2)) {
			ball.m_goal = false;
			left.m_score++;
			ball.m_origin.assign(5, 10);
		}
		if(!timer_active) {
			std::cout << "\033[H" << std::flush; // Clear screen
			if(left.m_score > right.m_score) {
				std::cout << "Player 1 wins!" << std::endl; 
			} if(left.m_score < right.m_score) {
				std::cout << "Player 2 wins!" << std::endl; 
			} if(left.m_score == right.m_score) {
				std::cout << "It's a tie!" << std::endl; 
			}
			running = false;
		}
	}

	timer_thread.join();
	input_thread.join();
	return 0;
}
