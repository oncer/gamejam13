# pragma once

#include "sdk.h"
#include "Sprite.h"

class Note :
	public Sprite
{
	public:
		Note(void);
		~Note(void);
		void draw(void);
		void update(void);
		void respawn(int _pitch);
		bool isAlive(void);

	protected:
		static const int pos_max_x = 380;
		static const int pos_min_x = 20;
		static const int hitpos_max_x = 60;
		static const int hitpos_min_x = 40;

		bool alive;

		int pitch;

};
