#ifndef ELEMENTS_HPP
#define ELEMENTS_HPP
#include "globals.hpp"
#include <array>

struct Point {
	int m_row;
	int m_col;
	Point();
	Point(int row, int col) : m_row(row), m_col(col) {};
	void to_string();
	void clear(std::array<std::array<char, COL>, ROW> &m_board);
	void assign(int row, int col);
};

struct Ball {
	Ball();
	Point m_origin;
	int m_vx = 1;
	int m_vy = -1;
	bool m_goal;
	void get_new_pos();
	void check_collision();
	void change_direction(char d);
};

struct Paddle {
	Paddle(int col);
	int _size;
	int m_score;
	Point m_nodes[4];
	void get_new_pos(int col);
	void check_collision(Ball &ball);
};

#endif
