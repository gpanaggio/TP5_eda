#include "allegroClass.h"
#include "EventHandler.h"
#include "userData.h"  // Header de la estructura info



typedef struct info;
// Info seria la estructura que contiene cosas como las posiciones maximas y minimas a las que pueden acceder los worms, ademas de
// un arreglo de punteros a bitmap para cada animacion. Si hay alguna otra informacion que sea igual para ambos worms y es constante,
// debe ir aca.
// Esta estructura tiene dos funciones, load y unload. A load deberiamos pasarle un arreglo de strings con los nombres de todas las imagenes
// a cargar (dos en realidad, uno para las del salto y uno para las de caminar). Ademas deberiamos pasarle la cantidad de imagenes que son.
// A unload hay que pasarle la cantidad de fotos de mabas animaciones.
int main() {

	srand(time(NULL));

	allegro_c allegro;
	vector<Worm> worms;
	userData userData;
	Evnt ev;

	data.load(NULL, 3, NULL, 3);
	worms.push_back(&userData);
	worms.push_back(&userData);

	while ((ev = getEvent(allegro->getEventQueue())) != QUIT)
		if (ev != NOEVENT)
			dispatchEvent(ev, worms);


	data.unload(3, 3);
	return 0;
}