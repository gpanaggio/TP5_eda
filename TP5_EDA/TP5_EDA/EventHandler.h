#include <allegro5\allegro.h>
#include <vector>
#include "Timer.h"
#include "Stage.h" //

using namespace std;



typedef enum Evnt {
	NOEVENT, LEFT1, LEFT2, RIGHT1, RIGHT2, JUMP1, JUMP2, TIMER, QUIT
};

typedef struct {
	Evnt Event;
	Timer * time;
	bool active;
	int keycode;

	void activate() {
		active = true;
	}
	void deactivate() {
		active = false;
		Event = NOEVENT;
	}
	void newTimer() {
		time = new Timer();
	}
	bool timerExist() {
		return time != NULL;
	}

	void killTimer() {
		delete time;
		time = NULL;
	}

	bool timerGreaterThan(float ms)
	{
		bool retValue = false;
		time->stop();
		if (time->getTime() >= ms)
			retValue = true;
		killTimer();

		return retValue;
	}
}Ev_t;

class EventHandler {
public:
	EventHandler();
	
	bool getEvent(ALLEGRO_EVENT_QUEUE *  eq);		// Gets the event from the event queue and/or other mediums not yet implemented
	bool isThereEvent();							// Checks if there is an active event
	void handleEventDispatcher(Stage& stage);		// Dispatches multiple events
private:

	void setEvent(Evnt ev, int worm);				// Sets the event but it does not activate it.
	void dispatchEvent(Evnt ev, Stage& stage);		// The actual dispatcher for every single event
	bool moveWorm(int ev, int worm);				// It decides if the key pressed correspond to a given worm
	bool moveWorm1(int ev);
	bool moveWorm2(int ev);

	array<Ev_t, 3>events;
};

