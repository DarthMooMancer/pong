#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <array>
#include <chrono>
#include <ncurses.h>

constexpr int ROW = 15;
constexpr int COL = 31;
constexpr int SIZE { 5 };

enum class Direction {
	NONE, UP, DOWN
};

struct vec2 {
	int a, b;
	vec2() : b(0), a(0) {};
	vec2(int x, int y) : a(x), b(y) {};
	void set(int a1, int b1) { a = a1; b = b1; };
	auto operator <=> (const vec2&) const = default;
};

struct Paddle {
	Paddle(const vec2 init_pos);
	std::array<vec2, SIZE> nodes;
	const char symbol { '|' };
	enum Direction dir = Direction::NONE;
	void move();
};

struct Window {
	std::array<std::array<char, COL>, ROW> view = {};
	void clear_display();
	void draw_display();
	void update_display(const vec2 &ball, const Paddle &p1, const Paddle &p2);
};

class Engine {
public:
	Engine();
	~Engine() { endwin(); };
	void run();

private:
	Window win;
	int clock { 30 };
	vec2 score { 0, 0 };
	vec2 ball { (COL / 2), (ROW / 2) };
	vec2 ball_direction { 1, 1 };
	Paddle p1 { { 1, (ROW / 2) - (SIZE / 2) } };
	Paddle p2 { { COL - 2, (ROW / 2) - (SIZE / 2) } };
	std::chrono::steady_clock::time_point last_clock_update;

	bool exit_process();
	bool process_input();
	bool move_ball();
	void on_collision_with_ball();
};

#endif
