#include <allegro5\allegro.h>
#include <vector>
#include "Timer.h"
#include "Worm.h"

using namespace std;



typedef enum Evnt {
	NOEVENT, LEFT1, LEFT2, RIGHT1, RIGHT2, JUMP1, JUMP2, TIMER, QUIT
};


void dispatchEvent(Evnt ev, vector<Worm> worms);
Evnt getEvent(ALLEGRO_EVENT_QUEUE *  eq);