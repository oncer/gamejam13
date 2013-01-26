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

protected:
	bool pulse;
	s32 pulseCount;


};

