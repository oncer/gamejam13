#pragma once
#include "Sprite.h"

class Demon :
	public Sprite
{
public:
	Demon(void);
	~Demon(void);
	
	void Demon::update(void);
	void Demon::draw(void);
	void Demon::hurt(void);
	void Demon::happy(void);

protected:
	enum State {
		NORMAL,
		HURT,
		HAPPY
	};

	State state;

	void Demon::setState(State _state);

	static const int max_velocity = -160;
	static const int min_velocity = -4;
};