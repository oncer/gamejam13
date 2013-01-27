# pragma once

#include "sdk.h"
#include "Sprite.h"

class AfterNote :
	public Sprite
{
	public:
		AfterNote(void);
		~AfterNote(void);
		void draw(void);
		void update(void);
		void respawn(int type, int x, int y);
		bool isAlive(void);

	protected:
		bool alive;

		int type;

};
