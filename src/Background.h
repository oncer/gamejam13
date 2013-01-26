#pragma once
#include "Sprite.h"
class Background :
	public Sprite
{
public:
	Background(void);
	~Background(void);
	
	void draw(void);
	void update(void);
};

