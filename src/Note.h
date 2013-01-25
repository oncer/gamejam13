# pragma once

#include "sdk.h"
#include "sprite.h"

class Note :
	public Sprite
{
	public:
		void Note::draw(void);
		void Note::update(void);
		

	protected:
		static const int pos_max_x = 380;
		static const int pos_min_x = 20;
		static const int hitpos_max_x = 60;
		static const int hitpos_min_x = 40;
		static const int note_velocity = 5;

		const int pitch;


};