#include <iostream>
#include "elements.hpp"

Point::Point() {
	m_col = 0;
	m_row = 0;
}

void Point::clear(std::array<std::array<char, COL>, ROW> &m_board) {
	m_board[m_row][m_col] = '.';
}

void Point::to_string() {
	std::cout << "(" << m_row << ", " << m_col << ")";
}

void Point::to_string(int index) {
	std::cout << "Index " << index << ": (" << m_row << ", " << m_col << ")";
}

Paddle::Paddle(int col) {
	for(int i = 0; i < 4; i++) {
		m_nodes[i].m_col = col;
		m_nodes[i].m_row = i + 3;
	}
}

void Paddle::get_new_pos(int col) {
	for(int i = 1; i < 4; i++) {
		m_nodes[i].m_row = m_nodes[0].m_row + i;
		m_nodes[i].m_col = col; // Should fix the weird bug that happens when spamming keys
	}
}
