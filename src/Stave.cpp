#include "Stave.h"
#include "GFX.h"
#include "Globals.h"

Stave::Stave(void)
{
	display_offset.x = 0;
	display_offset.y = -8;
	pos.w = (32<<FPSH);
	pos.h = (48<<FPSH);
	add_sprite_rect("cursor", 0,0,32,64);
	add_sprite_rect("cursor",32,0,32,64);
	add_sprite_rect("cursor",64,0,32,64);
	anim_frames = 3;
	anim_frame_duration = 5;
	anim = true;
	
	state = STATE_IDLE;
}


Stave::~Stave(void)
{
}

const int minPitch = -1;
const int maxPitch = 4;

void Stave::update(void){
	Sprite::update();
	if (KBD::JustPressed(KBD::KEY_UP)) {
		selectedPitch--;
		if (selectedPitch < minPitch) selectedPitch = maxPitch;
	}
	if (KBD::JustPressed(KBD::KEY_DOWN)) {
		selectedPitch++;
		if (selectedPitch > maxPitch) selectedPitch = minPitch;
	}
	if (KBD::JustPressed(KBD::KEY_ACTION)) {
		// swap notes
		s32 tmp = note0.getValue();
		note0.setValue(note1.getValue());
		note1.setValue(tmp);
	}

	pos.x = 16*PX;
	pos.y = (selectedPitch + 1)*PX*16;
	point note0Center = {getCenter().x, pos.y + (16<<FPSH)};
	note0.setCenter(note0Center);
	point note1Center = {getCenter().x, pos.y + (32<<FPSH)};
	note1.setCenter(note1Center);

	note0.update();
	note1.update();
}

void Stave::draw(void)
{
	// draw lines
	rect rcLines[] = {
		{0, 0, 400, 16},
		{0,16, 400, 16}
	};
	rect& rcLine = rcLines[(g_game->getCurrentFrameID()/8)%2];
	for (int i=1; i<7; i++) {
		GFX::blit_alpha("lines", rcLine, 0, 16*i, 128);
	}
	Sprite::draw();
	note0.draw();
	note1.draw();
}

bool Stave::hitNote(const Note& note)
{
	point center = getCenter();
	s32 hitX = center.x;
	s32 noteX = note.getCenter().x;
	s32 noteVelX = note.getVelocity().x;
	if (note.getPitch() == (selectedPitch) || note.getPitch() == (selectedPitch + 1)) {
		if (noteX <= hitX && (noteX - noteVelX) > hitX) {
			if (note.getPitch() == selectedPitch) {
				note0.collide(note);
			} else {
				note1.collide(note);
			}
			return true;
		}
	}
	return false;
}


StaveNote::StaveNote()
{
	anim_frame_counter = 0;
	display_offset.x = -8;
	display_offset.y = -10;
	pos.w = (14<<FPSH);
	pos.h = (12<<FPSH);
	// white
	add_sprite_rect("cursor", 0, 64, 32, 32);
	add_sprite_rect("cursor",32, 64, 32, 32);
	add_sprite_rect("cursor",64, 64, 32, 32);
	// black
	add_sprite_rect("cursor", 0, 96, 32, 32);
	add_sprite_rect("cursor",32, 96, 32, 32);
	add_sprite_rect("cursor",64, 96, 32, 32);

	value = -1;
}

StaveNote::~StaveNote()
{
}

void StaveNote::update()
{
	Sprite::update();
	anim_frame_counter++;
	if (anim_frame_counter > 4) {
		anim_frame_counter = 0;
		cur_frame++;
		if (value == 0 && (cur_frame < 0 || cur_frame > 2)) cur_frame = 0;
		if (value == 1 && (cur_frame < 3 || cur_frame > 5)) cur_frame = 3;
	}
}

void StaveNote::setValue(s32 v)
{
	value = v;
	cur_frame = (v == 0) ? 0 : 3;
}

void StaveNote::draw()
{
	if (value >= 0) {
		Sprite::draw();
	}
}

void StaveNote::collide(const Note& note)
{
	if (value == -1) {
		value = (s32)note.getType();
	} else if (value == (s32)note.getType()) {
		value = -1;
		SND::hitnote(note.getPitch());
		EffectType effectType;
		switch (note.getPitch()) {
			case 0: effectType = EFFECT_NOTE1; break;
			case 1: effectType = EFFECT_NOTE2; break;
			case 2: effectType = EFFECT_NOTE3; break;
			case 3: effectType = EFFECT_NOTE4; break;
			case 4: effectType = EFFECT_NOTE5; break;
		}

		g_game->getParticles().addEffect(effectType, getCenter());
	} else {
		Particle::ParticleType particleType;
		switch (value) {
			case 0: particleType = Particle::NOTEHEAD1; break;
			case 1: particleType = Particle::NOTEHEAD2; break;
		}
		Particle* p = g_game->getParticles().addParticle(particleType);
		p->setCenter(getCenter());
		p->setAcceleration(0, PX/8); // gravity
		value = (s32)note.getType();
	}
}

