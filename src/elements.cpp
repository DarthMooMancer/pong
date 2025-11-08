#include "elements.hpp"
#include "globals.hpp"

Ball create_ball(vec2** segments, int row, int col, char symbol, int t_size) {
	Ball ball;
	segments[t_size - 1] = new vec2 { row, col, symbol };
	ball.m_origin = segments[t_size - 1];
	return ball;
}

Paddle create_paddle(vec2** segments, int starting_index, int ending_index, int column, char symbol) {
	Paddle paddle;
	paddle.m_size = ending_index - starting_index;
	paddle.m_nodes = new vec2*[paddle.m_size];
	int starting_y_index = (ROW / 2) - (paddle.m_size / 2);
	for(int i = 0; i < paddle.m_size; i++) {
		paddle.m_nodes[i] = new vec2 { starting_y_index + i, column, symbol };
		segments[starting_index + i] = paddle.m_nodes[i];
	}
	return paddle;
}

void Paddle::determine_new_position(vec2* (*board)[COL]) {
	if(m_dir == UP) {
		if(board[(m_nodes[0]->y) - 1][m_nodes[0]->x] == nullptr) {
			for(int i = 0; i < m_size; i++) {
				m_nodes[i]->y--;
			}
		}
	} else if(m_dir == DOWN) {
		if(board[(m_nodes[m_size - 1]->y) + 1][m_nodes[m_size - 1]->x] == nullptr) {
			for(int i = 0; i < m_size; i++) {
				m_nodes[i]->y++;
			}
		}
	}
	m_dir = NONE;
}

void on_collision_with_ball(vec2** segments, Ball &ball, int t_size) {
	for(int i = 0; i < t_size - 1; i++) {
		if(segments[i]->y != ball.m_origin->y) continue; 
		if(segments[i]->x != ball.m_origin->x) continue;
		if (ball.m_vx == 1) ball.m_vx = -1;
		else ball.m_vx = 1;
	}
}

bool Ball::determine_next_valid_position() {
	if(m_origin->y <= 0 || m_origin->y >= ROW - 1) {
		if (m_vy == 1) m_vy = -1;
		else m_vy = 1;
	}
	if(m_origin->x <= 0 || m_origin->x >= COL - 1) return false;
	if(m_vx == 1) {
		m_origin->x++;
	}
	else if(m_vx == -1) {
		m_origin->x--;
	}
	if(m_vy == 1) {
		m_origin->y++;
	}
	else if(m_vy == -1) {
		m_origin->y--;
	}
	return true;
}
