#include <iostream>
#include <thread>
#include "input.hpp"
#include "timer.hpp"
#include "window.hpp"
#include "elements.hpp"
#include "globals.hpp"

int main() {
	int time_seconds = 30;
	Input input;
	Timer timer;
	Window window;
	bool running = true;
	vec2* segments[8] = {};

	Paddle left = create_paddle(segments, 0, 3, 1, '|');
	Paddle right = create_paddle(segments, 3, 6, COL - 2, '|');
	Ball ball = create_ball(segments, (ROW / 2), (COL / 2), 'o', 8);

	std::thread timer_thread([&] { timer.decrement_time(time_seconds, running); } );
	std::thread input_thread([&] { input.get_input(left.m_dir, right.m_dir, running); } );

	while (running) {
		left.determine_new_position(window.m_board);
		right.determine_new_position(window.m_board);
		if(!ball.determine_next_valid_position()) {
			if(ball.m_origin->x < 1) {
				left.m_score++;
			} else if(ball.m_origin->x > COL - 2) {
				right.m_score++;
			}
			ball.m_origin->y = ROW / 2;
			ball.m_origin->x = COL / 2;
		}
		on_collision_with_ball(segments, ball, 7);
		if(time_seconds <= 0) {
			if(left.m_score > right.m_score) {
				std::cout << "Player 1 wins!\n"; 
			} if(left.m_score < right.m_score) {
				std::cout << "Player 2 wins!\n"; 
			} if(left.m_score == right.m_score) {
				std::cout << "It's a tie!\n";
			}
			running = false;
		}
		window.clear_display();
		window.update_display(segments);
		window.draw_display(130);
		std::cout << "Time left: " << time_seconds << ", Score ( " << left.m_score << " : " << right.m_score << " )\n";
	}

	timer_thread.join();
	input_thread.join();
	for(int i = 8; i > 0; i--) {
		if(segments[i] != nullptr) {
			delete segments[i];
		}
	}
	return 0;
}
