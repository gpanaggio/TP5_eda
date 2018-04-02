#include "userData.h"
#include "Position.h"

#define JUMPSTART 4		//porque el salto comienza en el 4to frame
#define JUMPEND (4+32)	//y segun los calculos termina 32 fames despues
#define VI (4.5)		//velocidad inicial
#define THETA (60/(180/3.14))	//angulo del salto

enum { FRIO, CALIENTE };
typedef enum { WALKLEFT, WALKRIGHT, SALTANDO, ESPERANDO } WORM_STATE;
typedef enum { LEFT, RIGHT } DIRECTION;

class Worm
{
private:
	Position pos;
	WORM_STATE estado;
	DIRECTION worm_direction;
	userData * userDta;
	unsigned int CountWalk;		//ayuda como parametro para saber que hacer cada ves que se llama a alguna funcion
	unsigned int CountJump;		//y para saber en que instancia estamos de cada accion
	bool warm_up;	//lo usamos para saber si el gusano esta calentando o moviendose
public:
	Worm(userData*);
	void update();
	void move(DIRECTION);
	void draw();
	void jump(void);
	~Worm();
};

float tiro_oblicuo(void);

