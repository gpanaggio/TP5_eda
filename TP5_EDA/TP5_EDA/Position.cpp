#include "Position.h"
#include "time.h"
#include <stdlib.h>



Position::Position()
{
	coord_y = 616;	//el gusano se inicial en el piso (se estaria al 616)
	coord_x = (rand() % (1212 - 701) + 701);	//posicion el x aleatoria dentro de los parametros
}


Position::~Position()
{
}

float Position::get_x(void)
{
	return coord_x;
}

float Position::get_y(void)
{
	return coord_y;
}

void Position::set_x(float x_)
{
	coord_x = x_;
}

void Position::set_y(float y_)
{
	coord_y = y_;
}
