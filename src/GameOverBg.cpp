#include "GameOverBg.h"


GameOverBg::GameOverBg(void)
{
	add_sprite_rect("gameover",0,0,400,240);
}


GameOverBg::~GameOverBg(void)
{
}

void GameOverBg::draw(void) {
	Sprite::draw();
}
void GameOverBg::update(void) {
	Sprite::update();
}
