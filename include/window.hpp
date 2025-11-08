#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "globals.hpp"
#include "elements.hpp"

struct Window {
	vec2* m_board[ROW][COL] = {};
	void clear_display();
	void draw_display(int milliseconds);
	void update_display(vec2** segments);
};
#endif
