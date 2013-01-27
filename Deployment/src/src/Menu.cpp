#include "Menu.h"
#include "Globals.h"


Menu::Menu(void)
{
	add_sprite_rect("menu",0,0,400,240);
}


Menu::~Menu(void)
{
}

void Menu::draw(void) {
	Sprite::draw();
}
void Menu::update(void) {
	Sprite::update();
	if( KBD::IsKeyPressed(KBD::KEY_ACTION)) { 
		//start game
		g_game->setGamestate(Game::GAME);
	}
}
