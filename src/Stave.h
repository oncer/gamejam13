#pragma once
#include "sdk.h"
#include "Sprite.h"
#include "Note.h"

class StaveNote : public Sprite
{
	public:
		StaveNote(void);
		~StaveNote(void);

		void update();
		void draw();

		s32 getValue() const { return value; }
		void setValue(s32 v) { value = v; }
		void collide(const Note& note);
		
	protected:
		s32 value;
};

class Stave :
	public Sprite
{
public:
	enum {
		STATE_IDLE,
	};

	Stave(void);
	~Stave(void);
	
	void update(void);
	void draw(void);

	bool hitNote(const Note& note);

protected:
	s32 state;
	s32 selectedPitch; // (-1)..(4)
	StaveNote note0, note1;
	s32 combo;
};

