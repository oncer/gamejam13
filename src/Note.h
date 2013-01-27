# pragma once

#include "sdk.h"
#include "Sprite.h"

class Note :
	public Sprite
{
	public:
		enum Type {
			NOTE_1 = 0,
			NOTE_2 = 1
		};

		enum Pitch {
			NONE = -1,
			E = 0,
			D = 1,
			C = 2,
			H = 3,
			A = 4
		};

		Note(void);
		~Note(void);
		void draw(void);
		void update(void);
		void respawn(Pitch _pitch, Type _type);
		bool isAlive(void);

		Pitch getPitch() const { return pitch; }
		Type getType() const { return type; }

	protected:
		static const int pos_max_x = 392;
		static const int pos_min_x = 16;
		static const int hitpos_max_x = 60;
		static const int hitpos_min_x = 40;

		bool alive;

		Type type;
		Pitch pitch;

};
