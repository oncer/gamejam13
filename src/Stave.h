#pragma once
#include "Sprite.h"
class Stave :
	public Sprite
{
public:

	Stave(void);
	~Stave(void);
	
	void draw(void);
	void update(void);
};

