#pragma once
class Position
{
private:
	float coord_x;
	float coord_y;
public:
	Position();
	~Position();
	float get_x(void);
	float get_y(void);
	void set_x(float);
	void set_y(float);
};

