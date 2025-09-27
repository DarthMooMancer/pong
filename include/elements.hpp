#ifndef ELEMENTS_HPP
#define ELEMENTS_HPP

#include "globals.hpp"

enum Direction {
	NONE = 0,
	UP = -1,
	DOWN = 1
};

struct Point {
	Point() : m_row(0), m_col(0) {};
	Point(int r, int c, char s) : m_row(r), m_col(c), m_symbol(s) {};
	int m_row;
	int m_col;
	char m_symbol;
};


struct Ball {
	Ball() : m_vx(1), m_vy(-1) {};
	Point* m_origin;
	int m_vx;
	int m_vy;
	bool determine_next_valid_position(Point* (*board)[COL]);
};

struct Paddle {
	Paddle() : m_score(0) {};
	int m_score;
	int m_size;
	Point** m_nodes;
	enum Direction m_dir;
	void determine_new_position(Point* (*board)[COL]);
};

void on_collision_with_ball(Point** segments, Ball &ball, int t_size);
Ball create_ball(Point** segments, int row, int col, char symbol, int t_size);
Paddle create_paddle(Point** segments, int starting_index, int ending_index, int column, char symbol);

#endif
