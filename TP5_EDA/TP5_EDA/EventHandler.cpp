#include <ctype.h>
#include <vector>
#include "EventHandler.h"
#include <iostream>



using namespace std;
Evnt trasformAllegroEvents(int key);


void dispatchEvent(Evnt ev, Stage& stage)
{
	switch (ev)
	{
	case LEFT1: stage.worms[0].move(LEFT); break;
	case LEFT2: stage.worms[1].move(LEFT); break;
	case RIGHT1:stage.worms[0].move(RIGHT); break;
	case RIGHT2:stage.worms[1].move(RIGHT); break;
	case JUMP1:stage.worms[0].jump(); break;
	case JUMP2:stage.worms[1].jump(); break;
	case TIMER:
		stage.draw();
		for (Worm& worm : stage.worms)
		{
			worm.update();
			worm.draw();
		}
	}

}

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
	case ALLEGRO_KEY_ESCAPE:
		ev = QUIT;
		break;
	}
	return ev;
}

Evnt getEvent(ALLEGRO_EVENT_QUEUE * eq)
{
	ALLEGRO_EVENT ev;
	Evnt retEv = NOEVENT;
	static Timer * time = NULL;		// Ya se que no deberiamos usar 'static' pero necesito que este objeto no se destruya al terminar
									// la funcion ya que es el encargado de regular el tiempo. Creo este objeto solo cuando se detecta 
									// que se toco una tecla y lo destruyo cuando dejan de apretarla.
	al_get_next_event(eq, &ev);


	switch (ev.type)
	{
	case ALLEGRO_EVENT_KEY_DOWN:
		if (time == NULL)
		{
			time = new Timer();
			time->start();
		}
		break;
	case ALLEGRO_EVENT_KEY_UP:
		if (time != NULL)
		{
			time->stop();
			if (time->getTime() >= 100)
				retEv = trasformAllegroEvents(ev.keyboard.keycode);
			delete time;
			time = NULL;
		}
		break;
	case ALLEGRO_EVENT_TIMER:
		retEv = TIMER;
		break;
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		retEv = QUIT;
		break;
	}


	return retEv;

}