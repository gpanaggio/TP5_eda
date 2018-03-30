#include <allegro5\allegro.h>
#include <vector>
#include "Timer.h"
#include "Worm.h"		// Header de la clase Worm

using namespace std;

typedef class Worm; //Solo para que no me putee visual


typedef enum Evnt {
	NOEVENT, LEFT1, LEFT2, RIGHT1, RIGHT2, JUMP1, JUMP2, TIMER, QUIT
};


void dispatchEvent(Evnt ev, vector<Worm> worms);
Evnt getEvent(ALLEGRO_EVENT_QUEUE * eq);