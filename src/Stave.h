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
		STATE_BOUNCE
	};

	Stave(void);
	~Stave(void);
	
	void update(void);
	void draw(void);

	void startPulse(void);
	bool isReady(void) { return state == STATE_IDLE; }

	bool hitNote(const Note& note);

protected:
	s32 state;
	s32 selectedPitch;
};

