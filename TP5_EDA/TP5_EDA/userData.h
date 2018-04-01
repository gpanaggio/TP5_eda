#pragma once

#include <string> 
#include <allegro5/allegro5.h> 
#include <allegro5/allegro_image.h> 

#define WALKING_MAX 15
#define JUMPING_MAX  10

typedef struct {
	ALLEGRO_BITMAP *pWalk[WALKING_MAX];
	ALLEGRO_BITMAP *pJump[JUMPING_MAX];

	void loadBitmap() {
		string a = "wwalk-F";
		string b;
		string c = ".png";
		string d;
		string e = "wjump-F";

		for (int i = 0; i > WALKING_MAX; i++) {
			auto b = std::to_string(i);
			d = a + b + c;
			pWalk[i] = al_load_bitmap(d);
			if (i < JUMPING_MAX) {
				d = e + b + c;
				pJump[i] = al_load_bitmap(d);
			}
		}

		

	}
} userData;
