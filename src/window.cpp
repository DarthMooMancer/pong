#include "window.hpp"
#include <iostream>
#include <chrono>
#include <thread>

void Window::update_display(Paddle &left, Paddle &right, Ball &ball, int &time) {
	for(std::array<char, COL> &row : m_board) { row.fill('.'); }
	for(int i = 0; i < left._size; i++) {
		m_board[left.m_nodes[i].m_row][left.m_nodes[i].m_col] = '|';
		m_board[right.m_nodes[i].m_row][right.m_nodes[i].m_col] = '|';
	}
	m_board[ball.m_origin.m_row][ball.m_origin.m_col] = '*';
	std::cout << "\033[H" << std::flush; // Clear screen
	for(std::array<char, COL> &row : m_board) {
		for(char &col : row) {
			std::cout << col << " ";
		}
		std::cout << "\r\n";
	}
	std::cout << "Time left: " << time << ", Score ( " << left.m_score << " : " << right.m_score << " )" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(130)); // 1000 / fps; 200ms = 5fps
}
