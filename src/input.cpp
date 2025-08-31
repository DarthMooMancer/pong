#include "globals.hpp"
#include "input.hpp"
#include <ncurses.h>

void Input::get_input(bool &running, Paddle &a, Paddle &b) {
	while(running) {
		initscr();
		cbreak();
		noecho();

		m_getch = getch();

		endwin();
		if(m_getch == 'w') {
			if(a.m_nodes[0].m_row > 0) {
				a.m_nodes[0].m_row--;
				m_getch = ' ';
			}
		} else if(m_getch == 's') {
			if(a.m_nodes[a._size - 1].m_row < ROW - 1) {
				a.m_nodes[0].m_row++;
				m_getch = ' ';
			}
		} if(m_getch == 'A') {
			if(b.m_nodes[0].m_row > 0) {
				b.m_nodes[0].m_row--;
				m_getch = ' ';
			}
		} else if(m_getch == 'B') {
			if(b.m_nodes[b._size - 1].m_row < ROW - 1) {
				b.m_nodes[0].m_row++;
				m_getch = ' ';
			}
		}
		if(m_getch == 'q') {
			running = false;
		}
	}
}
