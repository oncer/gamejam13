#pragma once
#include "Sprite.h"
class FilterFilm :
	public Sprite
{
public:
	FilterFilm(void);
	~FilterFilm(void);
	
	void draw(void);
	void update(void);
};

