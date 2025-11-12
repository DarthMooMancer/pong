#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <array>
#include <chrono>
#include <ncurses.h>

constexpr int ROW = 15;
constexpr int COL = 31;
constexpr int SIZE { 3 };

struct vec2 {
	int x, y;
	vec2() : y(0), x(0) {};
	vec2(int x, int y) : x(x), y(y) {};
	void set(int a1, int b1) { x = a1; y = b1; };
	auto operator <=> (const vec2&) const = default;
};

struct Paddle {
	Paddle(const vec2 init_pos);
	std::array<vec2, SIZE> nodes;
	const char symbol { '|' };
	enum class Dir { NONE, UP, DOWN } dir;
	void move();
};

struct Window {
	std::array<std::array<char, COL>, ROW> view = {};
	void clear_display();
	void draw_display() const;
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
	Paddle p2 { { COL - 2, (ROW / 2) - (SIZE / 2) - 1 } };
	std::chrono::steady_clock::time_point last_clock_update;

	bool exit_process();
	bool process_input();
	bool move_ball();
	void on_collision_with_ball();
};

#endif
