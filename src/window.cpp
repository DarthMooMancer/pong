#include "window.hpp"
#include <iostream>
#include <chrono>
#include <thread>

Window::Window() {
	for(std::array<char, COL> &row : m_board) { row.fill('.'); }
}

void Window::update_display() {
// 	// Update symbols of positions
// 	m_board[head.m_head.m_row][head.m_head.m_col] = '*';
// 	m_board[fruit.m_point.m_row][fruit.m_point.m_col] = 'X';
// 	for(int i = 0; i < body.m_body.size(); i++) {
// 		m_board[body.m_body.at(i).m_tail_pos.m_row][body.m_body.at(i).m_tail_pos.m_col] = '0';
// 	}
//
	std::cout << "\033[H" << std::flush; // Clear screen
	// Draw Screen
	for(std::array<char, COL> &row : m_board) {
		for(char &col : row) {
			std::cout << col << " ";
		}
		std::cout << "\r\n";
	}
	std::this_thread::sleep_for(std::chrono::milliseconds((int) (200))); // 1000 / fps; 200ms = 5fps
// 	// Clear old spaces
// 	for(int i = 0; i < body.m_body.size(); i++) {
// 		body.m_body.at(i).m_tail_pos.clear(m_board);
// 	}
// 	head.m_head.clear(m_board);
// 	fruit.m_point.clear(m_board);
}
