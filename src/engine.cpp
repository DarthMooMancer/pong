#include <engine.hpp>
#include <iostream>
#include <ranges>
#include <algorithm>
#include <thread>

void Window::clear_display() {
	for(auto &row : view) {
		row.fill('.');
	}
}

void Window::draw_display() const {
	std::cout << "\033[H" << std::flush; // Clear screen
	std::string output;
	for(const auto &row : view) {
		for(const auto val : row) {
			output += std::isprint(val) ? val : '.';
			output += ' ';
		}
		output.append("\r\n");
	}
	std::cout << output;
}

void Window::update_display(const vec2 &ball, const Paddle &p1, const Paddle &p2) {
	view[ball.y][ball.x] = '*';
	for(auto &i : p1.nodes) {
		view[i.y][i.x] = p1.symbol;
	}
	for(auto &i : p2.nodes) {
		view[i.y][i.x] = p2.symbol;
	}
}

Paddle::Paddle(const vec2 init_pos) {
	for(int i : std::ranges::views::iota(0, (int)nodes.size())) {
		nodes[i].set(init_pos.x, init_pos.y + i);
	}
}

void Paddle::move() {
	if(dir == Dir::UP && nodes.front().y > 0) {
		for(auto &i : nodes) { i.y--; }
	}
	else if(dir == Dir::DOWN && nodes.back().y < ROW - 1) {
		for(auto &i : nodes) { i.y++; }
	}
	dir = Dir::NONE;
}

Engine::Engine() {
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	nodelay(stdscr, true);
	keypad(stdscr, true);
	last_clock_update = std::chrono::steady_clock::now();
}

void Engine::run() {
	while(process_input() && exit_process()) {
		if(!move_ball()) {
			if(ball.x < 1) { score.y++; }
			else if(ball.x > COL - 2) { score.x++; }
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
		std::cout << std::format("Time left: {}, Score ({}, {})\n", clock, score.x, score.y);
		std::this_thread::sleep_for(std::chrono::milliseconds(150)); // 1000 / fps; 200ms = 5fps
	}
}

bool Engine::process_input() {
	int key;
	while((key = getch()) != ERR) {
		if(key == 'q') { return false; }
		if(key == 'w') { p1.dir = Paddle::Dir::UP; }
		else if(key == 's') { p1.dir = Paddle::Dir::DOWN; }

		if(key == KEY_UP) { p2.dir = Paddle::Dir::UP; }
		else if(key == KEY_DOWN) { p2.dir = Paddle::Dir::DOWN; }
	}
	return true;
}


bool Engine::exit_process() {
	if(clock <= 0) {
		std::cout << ((score.x > score.y ) ? "Player 1 wins\n" : (score.x == score.y) ? "It's a tie\n" : "Player 2 wins\n");
		std::this_thread::sleep_for(std::chrono::seconds(1));
		return false;
	}
	return true;
}

bool Engine::move_ball() {
	if(ball.y <= 0 || ball.y >= ROW - 1) { ball_direction.y *= -1; }
	else if(ball.x <= 0 || ball.x >= COL - 1) return false;
	ball.x += ball_direction.x;
	ball.y += ball_direction.y;
	return true;
}

void Engine::on_collision_with_ball() {
	if(std::ranges::any_of(p1.nodes, [&](const auto& node) { return node == ball; })
		|| std::ranges::any_of(p2.nodes, [&](const auto& node) { return node == ball; })) {
		ball_direction.x *= -1;
	} 
}
