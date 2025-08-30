#ifndef INPUT_HPP
#define INPUT_HPP
#include "elements.hpp"

struct Input {
	int m_current_key = 0;
	char m_getch = ' ';
	void get_input(bool &r, Paddle &a, Paddle &b);
};

#endif // INPUT_HPP
