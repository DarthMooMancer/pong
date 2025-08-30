#ifndef INPUT_HPP
#define INPUT_HPP

struct Input {
	int m_current_key = 0;
	char m_getch = ' ';
	void get_input(bool &r);
};

#endif // INPUT_HPP
