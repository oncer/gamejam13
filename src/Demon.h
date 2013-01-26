#pragma once
#include "Sprite.h"

class Demon :
	public Sprite
{
public:
	Demon(void);
	~Demon(void);
	
	void update(void);
	void draw(void);
	void hurt(int strength);
	void happy(int strength);

protected:
	enum State {
		NORMAL,
		HURT,
		HAPPY
	};

	State state;

	void setState(State _state);

	static const int max_velocity = -160;
	static const int min_velocity = -4;
};
