#include "window.hpp"
#include <iostream>
#include <chrono>
#include <thread>

void Window::clear_display() {
	for(int i = 0; i < ROW; i++) {
		for(int j = 0; j < COL; j++) {
			m_board[i][j] = nullptr;
		}
	}
}

void Window::draw_display(int milliseconds) {
	std::cout << "\033[H" << std::flush; // Clear screen
	for(int i = 0; i < ROW; i++) {
		for(int j = 0; j < COL; j++) {
			if(m_board[i][j] == nullptr) std::cout << ". ";
			else std::cout << m_board[i][j]->m_symbol << " ";
		}
		std::cout << "\r\n";
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds)); // 1000 / fps; 200ms = 5fps
}

void Window::update_display(vec2** segments) {
	for(int i = 10; i >= 0; i--) {
		if(segments[i] == nullptr) continue;
		m_board[segments[i]->y][segments[i]->x] = segments[i];
	}
}
