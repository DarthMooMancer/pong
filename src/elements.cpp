#include "elements.hpp"
#include "globals.hpp"

Ball create_ball(Point** segments, int row, int col, char symbol, int t_size) {
	Ball ball;
	segments[t_size - 1] = new Point { row, col, symbol };
	ball.m_origin = segments[t_size - 1];
	return ball;
}

Paddle create_paddle(Point** segments, int starting_index, int ending_index, int column, char symbol) {
	Paddle paddle;
	paddle.m_size = ending_index - starting_index;
	paddle.m_nodes = new Point*[paddle.m_size];
	int starting_y_index = (ROW / 2) - (paddle.m_size / 2);
	for(int i = 0; i < paddle.m_size; i++) {
		paddle.m_nodes[i] = new Point { starting_y_index + i, column, symbol };
		segments[starting_index + i] = paddle.m_nodes[i];
	}
	return paddle;
}

void Paddle::determine_new_position(Point* (*board)[COL]) {
	if(m_dir == UP) {
		if(board[(m_nodes[0]->m_row) - 1][m_nodes[0]->m_col] == nullptr) {
			for(int i = 0; i < m_size; i++) {
				m_nodes[i]->m_row--;
			}
		}
	} else if(m_dir == DOWN) {
		if(board[(m_nodes[m_size - 1]->m_row) + 1][m_nodes[m_size - 1]->m_col] == nullptr) {
			for(int i = 0; i < m_size; i++) {
				m_nodes[i]->m_row++;
			}
		}
	}
	m_dir = NONE;
}

void on_collision_with_ball(Point** segments, Ball &ball, int t_size) {
	for(int i = 0; i < t_size - 1; i++) {
		if(segments[i]->m_row != ball.m_origin->m_row) continue; 
		if(segments[i]->m_col != ball.m_origin->m_col) continue;
		if (ball.m_vx == 1) ball.m_vx = -1;
		else ball.m_vx = 1;
	}
}

bool Ball::determine_next_valid_position(Point* (*board)[COL]) {
	if(m_origin->m_row <= 0 || m_origin->m_row >= ROW - 1) {
		if (m_vy == 1) m_vy = -1;
		else m_vy = 1;
	}
	if(m_origin->m_col <= 0 || m_origin->m_col >= COL - 1) return false;
	if(m_vx == 1) {
		m_origin->m_col++;
	}
	else if(m_vx == -1) {
		m_origin->m_col--;
	}
	if(m_vy == 1) {
		m_origin->m_row++;
	}
	else if(m_vy == -1) {
		m_origin->m_row--;
	}
	return true;
}
