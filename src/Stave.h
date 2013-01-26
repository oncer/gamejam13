#pragma once
#include "sdk.h"
#include "Sprite.h"
class Stave :
	public Sprite
{
public:

	Stave(void);
	~Stave(void);
	
	void update(void);
	void draw(void);

	void startPulse(void);

	bool isReady(void) { return !pulse; }

protected:
	bool pulse;
	s32 pulseCount;
	s32 selectedPitch;


};

