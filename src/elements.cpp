#include "elements.hpp"
#include "globals.hpp"

Point::Point() {
	m_col = m_row = 0;
}

void Point::assign(int row, int col) {
	m_row = row;
	m_col = col;
}

Paddle::Paddle(int col) {
	_size = 3;
	m_score = 0;
	for(int i = 0; i < _size; i++) { m_nodes[i].assign(i + (_size * 2), col); }
}

void Paddle::get_new_pos(int col) {
	for(int i = 1; i < _size; i++) { m_nodes[i].assign(m_nodes[0].m_row + i, col); }
}

void Paddle::check_collision(Ball &ball) {
	for(int i = 0; i < _size; i++) {
		if(ball.m_origin.m_row == m_nodes[i].m_row && ball.m_origin.m_col == m_nodes[i].m_col) {
			ball.change_direction('x');
		}
	}
}

Ball::Ball() {
	m_origin.assign((ROW / 2), (COL / 2));
	m_vx = 1;
	m_vy = -1;
	m_goal = false;
}

void Ball::change_direction(char d) {
	if(d == 'y') {
		if (m_vy == 1) m_vy = -1;
		else m_vy = 1;
	} if(d == 'x') {
		if (m_vx == 1) m_vx = -1;
		else m_vx = 1;
	}
}

void Ball::check_collision() {
	if(m_origin.m_row <= 0 || m_origin.m_row >= ROW - 1) change_direction('y');
	if(m_origin.m_col <= 0 || m_origin.m_col >= COL - 1) m_goal = true;
}

void Ball::get_new_pos() {
	if(m_vx == 1) m_origin.m_col++;
	else if(m_vx == -1) m_origin.m_col--;
	if(m_vy == 1) m_origin.m_row++;
	else if(m_vy == -1) m_origin.m_row--;
}
