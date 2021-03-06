#include "Demon.h"
#include "KBD.h"
#include "Globals.h"

Demon::Demon(void) {
	
	add_sprite_rect("demon",0,0,96,112);
	add_sprite_rect("demon",96,0,96,112);
	add_sprite_rect("demon",192,0,96,112);
	add_sprite_rect("demon",288,0,96,112);

	setPosition(320 * PX, 96 * PX);

	velocity.x = 0;

	setState(NORMAL);
	happy(64);
}

Demon::~Demon(void) {
}

void Demon::update(void){
	Sprite::update();

	if (anim_frame_counter++ >= anim_frame_duration) {
		anim_frame_counter = 0;
		if (state == NORMAL) {
			cur_frame = ( cur_frame + 1 ) % 2; //alternate 0, 1
		} else if (state == HAPPY) {
			setState(NORMAL);
		} else if (state == HURT) {
			setState(NORMAL);
		}
	}

	/*
	if(KBD::IsKeyPressed(KBD::KEY_DOWN)) {
		happy();
	}
	if(KBD::IsKeyPressed(KBD::KEY_UP)) {
		hurt();
	}
	*/

	
	int pxpos = pos.x>>FPSH;

	//SET TREBLE LOOP VOLUME
	//map from [50,320] to [1, 0]
	float gain = ((float)(320-pxpos)/270);
	gain *= gain*gain; //^3
	gain = std::min(gain, 0.7f);
	SND::setLoopedTrepleGain(gain);
	

	//SET FILTERS
	if (pxpos < 100) {
		//map from [50, 100] to [1, 0] to [255, 0]
		int opacity;
		if (pxpos <= 50) {
			opacity = 255;
			g_game->setGamestate(Game::GAMEOVER);
			SND::stopLoopedTreble();
			SND::dead();
		} else opacity = (int) (255 * ((double)(100-pxpos))/50);

		FilterDark& filter = g_game->getFilterDark();

		filter.setOpacity(opacity);
	}
}

void Demon::draw(void){
	Sprite::draw();
}

void Demon::hurt(int strength){
	setState(HURT);
	velocity.x += strength;
	if(velocity.x > min_velocity) {
		velocity.x = min_velocity;
	}
}

void Demon::happy(int strength){
	setState(HAPPY);
	velocity.x -= strength;
	if(velocity.x < max_velocity) {
		velocity.x = max_velocity;
	}
	drag.x = 1;
}

void Demon::setState(State _state){
	state = _state;
	if(state == NORMAL) {
		anim_frame_duration=10;
		anim_frame_counter = 0;
		cur_frame = 0;
	} else if (state == HURT) {
		anim_frame_duration=20;
		anim_frame_counter = 0;
		cur_frame = 2;
	} else if (state == HAPPY) {
		anim_frame_duration=20;
		anim_frame_counter = 0;
		cur_frame = 3;
	}
}
