#ifndef INPUT_HPP
#define INPUT_HPP
#include "elements.hpp"

struct Input {
	int m_getch = 0;
	void get_input(enum Direction &left, enum Direction &right, bool &running);
};

#endif // INPUT_HPP
