#include "Game.h"
#include "Define.h"
#include "GFX.h"
#include "KBD.h"
#include "SND.h"

Game::Game(void) :
	timer(NULL),
	paused(false),
	playtime(0),
	state(MENU)
{
	score = 0;
	combo = 0;
	maxCombo = 0;
}

Game::~Game(void)
{
}

void Game::pause(bool enabled)
{
	if (paused == enabled) return;
	this->paused = enabled;
	if (enabled) {
		al_stop_timer(timer);
	} else {
		al_start_timer(timer);
	}
}

void Game::run(void)
{
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* refresh_queue = NULL;
	ALLEGRO_EVENT_QUEUE* input_queue = NULL;
	bool redraw = true;

	if (!al_init()) {
		throw std::runtime_error("failed to initialize allegro!\n");
	}
	if (!al_init_image_addon()) {
		throw std::runtime_error("failed to initialize allegro image addon!\n");
	}
	if (!al_init_primitives_addon()) {
		throw std::runtime_error("failed to initialize allegro primitives addon!\n");
	}
	al_init_font_addon();
	al_init_acodec_addon();

	if (!al_install_audio()) {
		throw std::runtime_error("failed to initialize audio!\n");
	}
	al_reserve_samples(128);

	if (!al_install_keyboard()) {
		throw std::runtime_error("failed to initialize keyboard!\n");
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		throw std::runtime_error("failed to create timer!\n");
	}

	al_set_new_display_option(ALLEGRO_VSYNC, 2, ALLEGRO_SUGGEST);
	display = al_create_display(WIDTH * 2, HEIGHT * 2);
	if (!display) {
		throw std::runtime_error("failed to initialize display!\n");
	}
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_scale_transform(&transform, 2.0, 2.0);
	al_use_transform(&transform);

	refresh_queue = al_create_event_queue();
	if (!refresh_queue) {
		throw std::runtime_error("failed to create event_queue!\n");
	}
	input_queue = al_create_event_queue();
	if (!input_queue) {
		throw std::runtime_error("failed to create input_queue!\n");
	}

	al_register_event_source(input_queue, al_get_display_event_source(display));
	al_register_event_source(input_queue, al_get_keyboard_event_source());
	al_register_event_source(refresh_queue, al_get_timer_event_source(timer));

	GFX::init();
	SND::load();
	// initialization here

	al_start_timer(timer);

	bool step_by_step = false;

	int frames_fired, frames_drawn;
	frames_fired = frames_drawn = 0;
	int fps = 0;
	bool running = true;
	frameID = 0;

	int frame_counter = 0;


	//start allegro looped ambients
	SND::startLoopedAmbient();
	SND::startLoopedTreble();

    while (running)
    {
        ALLEGRO_EVENT ev;
        bool keydown = false;
        while (!al_is_event_queue_empty(input_queue)) {
            al_wait_for_event(input_queue, &ev);
            if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
                keydown = true;
                if (ev.keyboard.keycode == ALLEGRO_KEY_P) {
                    step_by_step = !step_by_step;
                }
            } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                running = false;
            }
        }
        al_wait_for_event(refresh_queue, &ev);
        if (!paused && ((step_by_step && keydown) ||
                    (!step_by_step && ev.type == ALLEGRO_EVENT_TIMER))) {
            redraw = true;
            frames_fired++;

			// GAME LOGIC
			
			KBD::Update();

			if (KBD::JustPressed(KBD::KEY_FULLSCREEN)) {
				bool opp = !(al_get_display_flags(display) & ALLEGRO_FULLSCREEN_WINDOW);
				al_toggle_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, opp);
				al_identity_transform(&transform);
				if (opp) {
					al_scale_transform(&transform, (double)al_get_display_width(display)/(double)WIDTH, (double)al_get_display_height(display)/(double)HEIGHT);
				} else {
					al_scale_transform(&transform, 2.0, 2.0);
				}
				al_use_transform(&transform);
			}

			frame_counter++;
			if(frame_counter>= FPS) {
				frame_counter = 0;
				if (state == GAME) playtime++;
			}
			if (state == MENU) {
				menu.update();
			} else if (state == GAME) {

				frameID++;

				song.update();
				song.updateNotes();
				player.update();
				stave.update();
				particles.update();
				demon.update();
				ambient.update();
				heartbeat.update();
			} else if (state == GAMEOVER) {
				gameOverBg.update();
			}

			filterFilm.update();
			// END OF GAME LOGIC
		}

		if (redraw && al_is_event_queue_empty(refresh_queue)) {
			frames_drawn++;
			al_clear_to_color(al_map_rgb(0, 0, 0));

			
			// DRAW SPRITES
			if (state == MENU) {
				menu.draw();
			} else if (state == GAME) {
				background.draw();
				player.draw();
				demon.draw();
				song.drawNotes();
				particles.draw();
				heartbeat.draw();
				stave.draw();
				
				filterDark.draw();
			} else if(state == GAMEOVER) {
				gameOverBg.draw();
			}

			filterFilm.draw();


			//END OF DRAW SPRITES

			//draw fps
			//char c_fps[20];
			//snprintf(c_fps, 20, "@%d@", fps);
			//GFX::text(FONT_DEFAULT, 360, 220, c_fps);
			if (state == GAME) {
				char c_stats[100];
				snprintf(c_stats, 100, "SCORE: %05d     COMBO:%03d     TIME: %05d", score, combo, playtime);
				GFX::text_center(FONT_DEFAULT, 200, 220, c_stats);
			} else if (state == GAMEOVER) {
				char c_stats[100];
				snprintf(c_stats, 100, "FINAL SCORE: %d", score);
				GFX::text_center(FONT_DEFAULT, 200, 180, c_stats);
				snprintf(c_stats, 100, "MAX COMBO: %d", maxCombo);
				GFX::text_center(FONT_DEFAULT, 200, 200, c_stats);
				snprintf(c_stats, 100, "TIME SURVIVED: %d", playtime);
				GFX::text_center(FONT_DEFAULT, 200, 220, c_stats);
			}


			al_flip_display();
		}/* else if (redraw && !al_is_event_queue_empty(refresh_queue)) {
			static int frameskip = 0;
			std::cout << "frameskip " << frameskip++ << std::endl;
			}*/
		if (frames_fired >= FPS) {
			frames_fired -= FPS;
			fps = frames_drawn;
			frames_drawn = 0;
		}
	}

}

void Game::setGamestate(Gamestate state) {
	this->state = state;
}

void Game::failnote(const Sprite& s, s32 type)
{
	demon.happy(64);
	particles.addEffect(EFFECT_OBSTACLE, s.getCenter());
	Particle::ParticleType particleType;
	switch (type) {
		case 0: particleType = Particle::NOTEHEAD1; break;
		case 1: particleType = Particle::NOTEHEAD2; break;
	}
	Particle* p = particles.addParticle(particleType);
	p->setCenter(s.getCenter());
	p->setAcceleration(0, PX/8); // gravity
	SND::failnote();
	combo = 0;
}

void Game::hitnote(const Sprite& s, s32 pitch)
{
	SND::hitnote(pitch);
	EffectType effectType;
	switch (pitch) {
		case 0: effectType = EFFECT_NOTE1; break;
		case 1: effectType = EFFECT_NOTE2; break;
		case 2: effectType = EFFECT_NOTE3; break;
		case 3: effectType = EFFECT_NOTE4; break;
		case 4: effectType = EFFECT_NOTE5; break;
	}
	particles.addEffect(effectType, s.getCenter());
	player.pump();
	heartbeat.startPulse();
	combo++;
	if (combo > maxCombo) maxCombo = combo;
	score += combo;
}

