#include "allegroClass.h"
#include "EventHandler.h"
#include "userData.h"  // Header de la estructura info


typedef class Stage;
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
	EventHandler eventHandler;
	vector<Worm> worms;

	Stage stage;

	userData userData;


	Evnt ev;

	userData.loadBitmap(NULL, 3, NULL, 3);
	worms.push_back(Worm(&userData));
	worms.push_back(Worm(&userData));

	while (eventHandler.getEvent(allegro.getEventQueue()))
		if (eventHandler.isThereEvent())
			eventHandler.handleEventDispatcher(stage);


	data.unload(3, 3);
	return 0;
}