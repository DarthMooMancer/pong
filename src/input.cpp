#include "input.hpp"
#include <ncurses.h>

void Input::get_input(bool &running) {
	while(running) {
		initscr();
		cbreak();
		noecho();

		m_getch = getch();
		endwin();
		// if(m_current_key != 1 && (m_getch == 'a' || m_getch == 'D')) {
		// 	direction = m_current_key = -1;
		// } else if(m_current_key != - 1 && (m_getch == 'd' || m_getch == 'C')) {
		// 	direction = m_current_key = 1;
		// } else if(m_current_key != -2 && (m_getch == 's' || m_getch == 'B')) {
		// 	direction = m_current_key = 2;
		// } else if(m_current_key != 2 && (m_getch == 'w' || m_getch == 'A')) {
		// 	direction = m_current_key = -2;
		if(m_getch == 'q') {
			running = false;
		}
	}
	
}
