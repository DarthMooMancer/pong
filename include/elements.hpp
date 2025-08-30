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
	void to_string(int index);
	void clear(std::array<std::array<char, COL>, ROW> &m_board);
	// void set_new_point(int row, int col);
};

struct Paddle {
	Paddle(int col);
	Point m_nodes[4];
	void get_new_pos(int col);
};

struct Ball {

};

#endif
