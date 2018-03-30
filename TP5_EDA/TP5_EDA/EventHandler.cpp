#include <ctype.h>
#include <vector>
#include "EventHandler.h"


using namespace std;
Evnt trasformAllegroEvents(int key);


void dispatchEvent(Evnt ev, vector<Worm> worms)
{
	switch (ev)
	{
	case LEFT1: worms[0].move(LEFT); break;			// yo lo habia pensado de la siguiente forma, move solo setea la direccion y cambia el
	case LEFT2: worms[1].move(LEFT); break;			// estado a moviendose (Jump actua de forma similar pero toma la direccion actual).
	case RIGHT1:worms[0].move(RIGHT); break;		// Despues, en la funcion update se deberia llamar a una funcion doJump()/doMove() que 
	case RIGHT2:worms[1].move(RIGHT); break;		// efectue el movimiento.
	case JUMP1:worms[0].jump(); break;				// draw va a dibujar la parte correcta de la animacion dependiendo del tick en el que		
	case JUMP2:worms[1].jump(); break;				// este el worm
	case TIMER:
		for (Worm& worm : worms)
		{
			worm.update();
			worm.draw();
		}
	}
}

// Esta funcion basicamente transforma los eventos de allegro de teclado a los nuestros, definidos en el enum de arriba
Evnt trasformAllegroEvents(int key) 
{
	Evnt ev = NOEVENT;

	switch (key)
	{
	case ALLEGRO_KEY_A:
		ev = LEFT2;
		break;
	case ALLEGRO_KEY_D:
		ev = RIGHT2;
		break;
	case ALLEGRO_KEY_W:
		ev = JUMP2;
		break;
	case ALLEGRO_KEY_LEFT:
		ev = LEFT1;
		break;
	case ALLEGRO_KEY_RIGHT:
		ev = RIGHT1;
		break;
	case ALLEGRO_KEY_UP:
		ev = JUMP1;
		break;
	}
	return ev;
}

Evnt getEvent(ALLEGRO_EVENT_QUEUE * eq)
{
	ALLEGRO_EVENT ev;
	Evnt retEv = NOEVENT;
	int key = NOEVENT;

	Timer * time = new Timer();

	al_get_next_event(eq, &ev);

	switch (ev.type)
	{
	case ALLEGRO_EVENT_KEY_DOWN:
		time->start();
		key = ev.keyboard.keycode;
		break;
	case ALLEGRO_EVENT_KEY_UP:
		time->stop();
		if (time->getTime() >= 100)
			retEv = trasformAllegroEvents(key);
		break;
	case ALLEGRO_EVENT_TIMER:
		retEv = TIMER;
		break;
	}

	delete time;
	return retEv;

}