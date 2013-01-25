#include "Stave.h"


Stave::Stave(void)
{
	add_sprite_rect("stave",0,0,368,32);
	setPosition(16*PX,32*PX);
}


Stave::~Stave(void)
{
}

void Stave::draw(void){
	Sprite::draw();
}

void Stave::update(void){
	Sprite::update();
}