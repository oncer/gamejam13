#pragma once
#include "sprite.h"
class Background :
	public Sprite
{
public:
	Background(void);
	~Background(void);
	
	void Background::draw(void);
	void Background::update(void);
};

