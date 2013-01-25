#pragma once
#include "sprite.h"
class Stave :
	public Sprite
{
public:
	Stave(void);
	~Stave(void);
	
	void Stave::draw(void);
	void Stave::update(void);
};

