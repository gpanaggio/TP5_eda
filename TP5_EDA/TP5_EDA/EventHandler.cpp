#include <ctype.h>
#include <vector>
#include "EventHandler.h"
#include <iostream>

using namespace std;
Evnt trasformAllegroEvents(int key);


void EventHandler::dispatchEvent(Evnt ev, Stage& stage)
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

EventHandler::EventHandler()
{
	for (Ev_t& ev : events)
	{
		ev.deactivate();
		ev.time = NULL;
	}
}

using namespace std;

bool EventHandler::getEvent(ALLEGRO_EVENT_QUEUE * eq)
{
	ALLEGRO_EVENT ev;
	bool quit = false;

	al_get_next_event(eq, &ev);


	switch (ev.type)
	{
	case ALLEGRO_EVENT_KEY_DOWN:

		if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			quit = true;
		else
			for (int i = 0; i < 2; ++i)			
				if (!this->events[i].active && moveWorm(ev.keyboard.keycode, i) && !this->events[i].timerExist())
					setEvent(trasformAllegroEvents(ev.keyboard.keycode), i);
		break;
	case ALLEGRO_EVENT_KEY_UP:

		for (int i = 0; i < 2; ++i)
			if (this->events[i].timerExist() && this->events[i].Event == trasformAllegroEvents(ev.keyboard.keycode))
				if (this->events[i].timerGreaterThan(100))
					this->events[i].activate();
		break;
	case ALLEGRO_EVENT_TIMER:
		this->setEvent(TIMER, 2);
		this->events[2].activate();
		break;
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		quit = true;
		break;
	}

	if (quit)
		for (int i = 0; i < 2; i++)
			if (this->events[i].timerExist())
				this->events[i].killTimer();
	
	return !quit;

}

bool EventHandler::isThereEvent()
{
	return this->events[0].active || this->events[1].active || this->events[2].active;
}

void EventHandler::handleEventDispatcher(Stage& stage)
{
	if (this->events[2].active)
	{
		dispatchEvent(this->events[2].Event, stage);
		this->events[2].deactivate();
	}
	else 
	{
		for (int i =0 ; i <2 ; i++)
		{
			if (this->events[i].active)
			{
				dispatchEvent(this->events[i].Event, stage);
				this->events[i].deactivate();
			}
				
		}
	}
}

void EventHandler::setEvent(Evnt ev, int worm)
{
	this->events[worm].Event = ev;
	if (ev != TIMER)
		this->events[worm].newTimer();
}

bool EventHandler::moveWorm(int ev, int worm)
{
	bool retValue = false;

	switch (worm)
	{
	case 0: retValue = moveWorm1(ev);
		break;
	case 1: retValue = moveWorm2(ev);
		break;
	}
	return retValue;
}

bool EventHandler::moveWorm1(int ev)
{
	return ((ev == ALLEGRO_KEY_LEFT) || (ev == ALLEGRO_KEY_RIGHT) || (ev == ALLEGRO_KEY_UP));
}

bool EventHandler::moveWorm2(int ev)
{
	return ((ev == ALLEGRO_KEY_W) || (ev == ALLEGRO_KEY_A) || (ev == ALLEGRO_KEY_D));
}
