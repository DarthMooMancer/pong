#ifndef ELEMENTS_HPP
#define ELEMENTS_HPP

#include "globals.hpp"

enum Direction {
	NONE, UP, DOWN
};

struct vec2 {
	vec2() : y(0), x(0) {};
	vec2(int r, int c, char s) : y(r), x(c), m_symbol(s) {}
	int x, y;
	char m_symbol;
};

struct Ball {
	Ball() : m_vx(1), m_vy(-1) {};
	vec2* m_origin;
	int m_vx;
	int m_vy;
	bool determine_next_valid_position();
};

struct Paddle {
	Paddle() : m_score(0) {};
	int m_score;
	int m_size;
	vec2** m_nodes;
	enum Direction m_dir;
	void determine_new_position(vec2* (*board)[COL]);
};

class Engine {
public:
	Engine();
	~Engine();
	void run();

private:


};

void on_collision_with_ball(vec2** segments, Ball &ball, int t_size);
Ball create_ball(vec2** segments, int row, int col, char symbol, int t_size);
Paddle create_paddle(vec2** segments, int starting_index, int ending_index, int column, char symbol);

#endif
