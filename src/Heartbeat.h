#pragma once
#include "sdk.h"
#include "Sprite.h"
#include "Note.h"

class Heartbeat :
	public Sprite
{
public:
	enum {
		STATE_IDLE,
		STATE_Q,
		STATE_R,
		STATE_S,
		STATE_T,
		STATE_U
	};

	Heartbeat(void);
	~Heartbeat(void);
	
	void update(void);
	void draw(void);

	void startPulse(void);
	bool isReady(void) { return state == STATE_IDLE; }

	static const int yOff = 0;

protected:
	s32 state;
};

