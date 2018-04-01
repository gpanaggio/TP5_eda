#include <iostream>
#include "Worm.h"


Worm::Worm()
{
	bitmapWalk[0] = al_load_bitmap("wwalk-F1.png");
	bitmapWalk[1] = al_load_bitmap("wwalk-F2.png");
	bitmapWalk[2] = al_load_bitmap("wwalk-F3.png");
	bitmapWalk[3] = al_load_bitmap("wwalk-F4.png");
	bitmapWalk[4] = al_load_bitmap("wwalk-F5.png");
	bitmapWalk[5] = al_load_bitmap("wwalk-F6.png");
	bitmapWalk[6] = al_load_bitmap("wwalk-F7.png");
	bitmapWalk[7] = al_load_bitmap("wwalk-F8.png");
	bitmapWalk[8] = al_load_bitmap("wwalk-F9.png");
	bitmapWalk[9] = al_load_bitmap("wwalk-F10.png");
	bitmapWalk[10] = al_load_bitmap("wwalk-F11.png");
	bitmapWalk[11] = al_load_bitmap("wwalk-F12.png");
	bitmapWalk[12] = al_load_bitmap("wwalk-F13.png");
	bitmapWalk[13] = al_load_bitmap("wwalk-F14.png");
	bitmapWalk[14] = al_load_bitmap("wwalk-F15.png");

	bitmapJump[0] = al_load_bitmap("wjump-F1.png");
	bitmapJump[1] = al_load_bitmap("wjump-F2.png");
	bitmapJump[2] = al_load_bitmap("wjump-F3.png");
	bitmapJump[3] = al_load_bitmap("wjump-F4.png");
	bitmapJump[4] = al_load_bitmap("wjump-F5.png");
	bitmapJump[5] = al_load_bitmap("wjump-F6.png");
	bitmapJump[6] = al_load_bitmap("wjump-F7.png");
	bitmapJump[7] = al_load_bitmap("wjump-F8.png");
	bitmapJump[8] = al_load_bitmap("wjump-F9.png");
	bitmapJump[9] = al_load_bitmap("wjump-F10.png");

	CountWalk = 0;
	CountJump = 0;
	warm_up = FRIO;	//el gusano esta en frio

	estado = ESPERANDO;
}

void Worm::update()
{
	static unsigned int ciclos = 0;		//usamos esto mas que nada para el tema de que en un desplazamiento se corre 3 veces la secuencia de caminata

	if (estado == WALKLEFT || estado == WALKRIGHT)
	{
		CountWalk++;

		if (warm_up == FRIO)
		{
			if (CountWalk == 3)
			{
				warm_up = CALIENTE;  //el gusano ya calento
				CountWalk = 0;
			}
		}
		else if (estado == WALKLEFT && CountWalk == 15)		//luego tengo que fijarme el tema para que no se salga del escenario
		{
			CountWalk = 0;	//la logica de esto es que si entramos por 15 ves al update estando el Worm en caminando ya mostramos en pantalla
			pos.set_x(pos.get_x() - 9);			//las 15 imagenes del Worm Walk que la ultima esta desplazada 9 pixeles respecto de la primera
			if (++ciclos == 3)
			{
				ciclos = 0;
				warm_up = FRIO;
				estado = ESPERANDO;
			}
		}
		else if (estado == WALKRIGHT && CountWalk == 15)
		{
			CountWalk = 0;
			pos.set_x(pos.get_x() + 9);
			if (++ciclos == 3)					//el ciclo de caminar lo hace 3 veces luego de eso tiene que volver a calentar
			{
				ciclos = 0;
				warm_up = FRIO;
				estado = ESPERANDO;
			}
		}
	}
	else if (estado == SALTANDO)
	{
		if (warm_up == FRIO && CountJump == JUMPSTART)		//el gusano calentando
		{
			warm_up = CALIENTE;
			CountJump = 0;
		}
		else if (CountJump > JUMPSTART && CountJump < JUMPEND)	//el gusano volando
		{
			if (worm_direction == LEFT)		//el gusano salta hacia la izquierda
			{
				pos.set_x(pos.get_x() - VI * cos(THETA));

			}
			else
				pos.set_x(pos.get_x() + VI * cos(THETA));
		}
		else if (CountJump == 42)		// aqui finaliza toda la sequencia de salto
		{
			CountJump = 0;
			warm_up = FRIO;
		}
	}
	else if (estado == ESPERANDO)
	{
		CountWalk = 0;
		CountJump = 0;
		warm_up = FRIO;
	}
}

void Worm::move(DIRECTION dir)
{
	if (dir == LEFT)
		estado = WALKLEFT;
	else if (dir == RIGHT)
		estado = WALKRIGHT;
	worm_direction = dir;
}

void Worm::draw(void)
{
	if (estado == WALKRIGHT)
	{
		al_draw_bitmap(bitmapWalk[CountWalk], pos.get_x(), pos.get_y(), ALLEGRO_FLIP_HORIZONTAL);
	}
	else if (estado == WALKLEFT)
	{
		al_draw_bitmap(bitmapWalk[CountWalk], pos.get_x(), pos.get_y(), 0);
	}
	else if (estado = SALTANDO)
	{
		if (worm_direction = LEFT)
		{
			if (CountJump <= JUMPSTART)
			{
				al_draw_bitmap(bitmapJump[CountJump], pos.get_x(), pos.get_y(), 0);
			}
			else if (CountJump < JUMPEND)
			{
				al_draw_bitmap(bitmapJump[5], pos.get_x(), pos.get_y() + tiro_oblicuo(), 0);	//dibujamos la imagen 5 (mirando a la izquierda)
			}
			else
			{
				al_draw_bitmap(bitmapJump[CountJump - (JUMPEND - JUMPSTART)], pos.get_x(), pos.get_y(), 0);
			}
		}
		else     //el worm mira para la derecha -> se espejan las imagenes
		{
			if (CountJump <= JUMPSTART)
			{
				al_draw_bitmap(bitmapJump[CountJump], pos.get_x(), pos.get_y(), ALLEGRO_FLIP_HORIZONTAL);
			}
			else if (CountJump < JUMPEND)
			{
				al_draw_bitmap(bitmapJump[5], pos.get_x(), pos.get_y() - tiro_oblicuo(), ALLEGRO_FLIP_HORIZONTAL);	//dibujamos la imagen 5 (mirando a la izquierda)
			}
			else
			{
				al_draw_bitmap(bitmapJump[CountJump - (JUMPEND - JUMPSTART)], pos.get_x(), pos.get_y(), ALLEGRO_FLIP_HORIZONTAL);
			}
		}
		CountJump++;
	}
	else if (estado == ESPERANDO)
	{
		if (worm_direction == LEFT) 
		al_draw_bitmap(bitmapWalk[1], pos.get_x(), pos.get_y(), 0);
		else
		al_draw_bitmap(bitmapWalk[1], pos.get_x(), pos.get_y(), ALLEGRO_FLIP_HORIZONTAL);
	}
}

void Worm::jump(void)
{
	estado = SALTANDO;
}

Worm::~Worm()
{
}

float tiro_oblicuo(void)	//esta funcion lo que hace es devolver la posicion en Y en un tiempo dado
{
	static int frame = 0;
	float rta = VI * sin(THETA)*frame - (0.24 / 2)*(frame*frame);	//formula del tiro oblicuo
	if (++frame == 33)
		frame = 0;     //al frame 33 el gusanito ya volvio al piso
	return rta;
}
