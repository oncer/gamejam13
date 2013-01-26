#pragma once
#include "sdk.h"
#include "Sprite.h"
#include "Note.h"

class Stave :
	public Sprite
{
public:
	enum {
		HIT_NONE = 0,
		HIT_BAD = 1,
		HIT_GOOD = 2,
		HIT_PERFECT = 3
	};

	Stave(void);
	~Stave(void);
	
	void update(void);
	void draw(void);

	void startPulse(void);

	bool isReady(void) { return !pulse; }

	// returns hit score, 0=nothing, 1=bad, 2=good, 3=perfect
	int hitNote(const Note& note);

protected:
	bool pulse;
	s32 selectedPitch;
};

