#include "Player.h"
#include "Globals.h"

Player::Player(void)
{
	add_sprite_rect("player",0,0,80,64);
	add_sprite_rect("player",80,0,80,64);
	add_sprite_rect("player",160,0,80,64);
	add_sprite_rect("player",240,0,80,64);
	
	setPosition(48 * PX, 128 * PX);
	
	setState(IDLE);
}


Player::~Player(void)
{
}

void Player::setState(States _state) {
	state = _state;
	if(state == IDLE) {
		anim_frame_duration=10;
		anim_frame_counter = 0;
		cur_frame = 0;
	} else if (state == PUMP) {
		anim_frame_duration=5;
		anim_frame_counter = 0;
		cur_frame = 2;
	}
}

void Player::draw(void) {
	Sprite::draw();
}
void Player::update(void) {
	
	Sprite::update();

	//handle keypress
	if(KBD::JustPressed(KBD::KEY_ACTION) && state != PUMP) { //just pressed key and state not yet set
		setState(PUMP);
		ParticleEmitter& particles = g_game->getParticles();
		point effectPos = {pos.x + 47*PX, pos.y + 19*PX};
		particles.addEffect(EFFECT_BLOODSQUIRT, effectPos);
		Stave& stave = g_game->getStave();
		stave.startPulse();
	}

	//update animation

	if (anim_frame_counter++ >= anim_frame_duration) {
		anim_frame_counter = 0;
		if (state == IDLE) {
			cur_frame = ( cur_frame + 1 ) % 2; //alternate 0, 1
		} else if (state == PUMP) {
			cur_frame++;
			if (cur_frame == 4) {
				setState(IDLE);
			}
		}
	}

}
