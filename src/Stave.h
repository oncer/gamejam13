#pragma once
#include "sdk.h"
#include "Sprite.h"
#include "Note.h"

class Stave :
	public Sprite
{
public:
	enum {
		STATE_IDLE,
	};

	Stave(void);
	~Stave(void);
	
	void update(void);
	void draw(void);

	bool hitNote(const Note& note);

protected:
	s32 state;
	s32 selectedPitch; // (-1)..(4)
	s32 note0, note1;
	s32 combo;
};

