#ifndef ELEMENTS_HPP
#define ELEMENTS_HPP

struct Point {
	Point();
	int m_row;
	int m_col;
	void assign(int row, int col);
};

struct Ball {
	Ball();
	Point m_origin;
	int m_vx;
	int m_vy;
	bool m_goal;
	void get_new_pos();
	void check_collision();
	void change_direction(char d);
};

struct Paddle {
	Paddle(int col);
	int _size;
	int m_score;
	Point m_nodes[3];
	void get_new_pos(int col);
	void check_collision(Ball &ball);
};

#endif
