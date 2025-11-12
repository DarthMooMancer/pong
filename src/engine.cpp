#include <engine.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <ranges>

void Window::clear_display() {
	for(auto &row : view) {
		row.fill('.');
	}
}

void Window::draw_display() {
	std::cout << "\033[H" << std::flush; // Clear screen
	for(const auto &row : view) {
		for(const auto val : row) {
			if(val == '.') std::cout << ". ";
			else std::cout << val << " ";
		}
		std::cout << "\r\n";
	}
}

void Window::update_display(const vec2 &ball, const Paddle &p1, const Paddle &p2) {
	view[ball.b][ball.a] = '*';
	for(auto &i : p1.nodes) {
		view[i.b][i.a] = p1.symbol;
	}
	for(auto &i : p2.nodes) {
		view[i.b][i.a] = p2.symbol;
	}
}

Paddle::Paddle(const vec2 init_pos) {
	for(int i : std::ranges::views::iota(0, (int)nodes.size())) {
		nodes[i].set(init_pos.a, init_pos.b + i);
	}
}

void Paddle::move() {
	if(dir == Direction::UP && nodes.front().b > 0) {
		for(auto &i : nodes) { i.b--; }
	} else if(dir == Direction::DOWN && nodes.back().b < ROW - 1) {
		for(auto &i : nodes) { i.b++; }
	}
	dir = Direction::NONE;
}

Engine::Engine() {
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	nodelay(stdscr, true);
	last_clock_update = std::chrono::steady_clock::now();
}

void Engine::on_collision_with_ball() {
	for(const auto &i : p1.nodes) {
		if(i == ball) {
			if (ball_direction.a == 1) ball_direction.a = -1;
			else ball_direction.a = 1;
		}
	}
	for(const auto &i : p2.nodes) {
		if(i == ball) {
			if (ball_direction.a == 1) ball_direction.a = -1;
			else ball_direction.a = 1;
		}
	}
}

void Engine::run() {
	while(process_input() && exit_process()) {
		if(!move_ball()) {
			if(ball.a < 1) { score.b++; }
			else if(ball.a > COL - 2) { score.a++; }
			ball.set(COL / 2, ROW / 2);
		}
		p1.move();
		p2.move();
		on_collision_with_ball();
		win.clear_display();
		win.update_display(ball, p1, p2);
		win.draw_display();
		auto current_time = std::chrono::steady_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - last_clock_update).count();
		if(elapsed_time >= 1) {
			clock -= elapsed_time;
			last_clock_update = current_time;
		}
		std::cout << "Time left: " << clock << ", Score ( " << score.a << " : " << score.b << " )\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(150)); // 1000 / fps; 200ms = 5fps
	}
}

bool Engine::process_input() {
	int ch;
	while((ch = getch()) != ERR) {
		if(ch == 'q') { return false; }
		if(ch == 'w') { p1.dir = Direction::UP; }
		else if(ch == 's') { p1.dir = Direction::DOWN; }

		if(ch == 65) { p2.dir = Direction::UP; }
		else if(ch == 66) { p2.dir = Direction::DOWN; }
	}
	return true;
}


bool Engine::exit_process() {
	if(time_seconds <= 0) {
		std::cout << ((score.a > score.b ) ? "Player 1 wins\n" : (score.a == score.b) ? "It's a tie\n" : "Player 2 wins\n");
		std::this_thread::sleep_for(std::chrono::seconds(1));
		return false;
	}
	return true;
}

bool Engine::move_ball() {
	if(ball.b <= 0 || ball.b >= ROW - 1) {
		if (ball_direction.b == 1) ball_direction.b = -1;
		else ball_direction.b = 1;
	}
	if(ball.a <= 0 || ball.a >= COL - 1) return false;
	if(ball_direction.a == 1) { ball.a++; }
	else if(ball_direction.a == -1) { ball.a--; }

	if(ball_direction.b == 1) { ball.b++; }
	else if(ball_direction.b == -1) { ball.b--; }
	return true;
}
