#include "input.hpp"
#include <iostream>
#include <ncurses.h>

void Input::get_input(enum Direction &left, enum Direction &right, bool &running) {
	while(running) {
		initscr();
		cbreak();
		noecho();

		m_getch = getch();
		endwin();

		if(m_getch == 119) left = UP;
		else if(m_getch == 115) left = DOWN;

		if(m_getch == 65) right = UP;
		else if(m_getch == 66) right = DOWN;

		if(m_getch == 113) running = false;

		m_getch = 0;
	}
}
