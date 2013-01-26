#include "Game.h"
#include "Define.h"
#include "GFX.h"
#include "KBD.h"
#include "SND.h"

Game::Game(void) :
    timer(NULL),
    paused(false),
	playtime(0),
	gameover(false),
	//song("e78d78e78c7d7e78a7h7a788c7a78d7e78h78a7c78e78c7a78h7a7a78c788d7")
	song("e34d34e34c3d3e34a3h3a344c3a34d3e12h12a1c12e12c1a12h1a1a12c122d1")
	//song("aechdchaechadcheadcheadchea")
{
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
			if (!gameover) {

				frame_counter++;
				if(frame_counter>= FPS) {
					frame_counter = 0;
					playtime++;
				}

				if (frameID%120 == 0) {
					backgroundNote = (backgroundNote + randint(1,3)) % 3;
					SND::background(backgroundNote);
				}

				KBD::Update();
				frameID++;

				song.update();
				song.updateNotes();
				player.update();
				stave.update();
				particles.update();
				demon.update();
				filterFilm.update();
				ambient.update();
			}
			// END OF GAME LOGIC
        }

        if (redraw && al_is_event_queue_empty(refresh_queue)) {
            frames_drawn++;
            al_clear_to_color(al_map_rgb(0, 0, 0));

			// DRAW SPRITES
            background.draw();
			player.draw();
			demon.draw();
			stave.draw();
			song.drawNotes();
			particles.draw();
			
			//filters
			filterDark.draw();
			filterFilm.draw();


			//END OF DRAW SPRITES

			//draw fps
            //char c_fps[20];
            //snprintf(c_fps, 20, "@%d@", fps);
            //GFX::text(FONT_DEFAULT, 360, 220, c_fps);
            char c_fps[20];
            snprintf(c_fps, 20, "@%d@", playtime);
			 GFX::text(FONT_DEFAULT, 360, 220, c_fps);


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

void Game::setGameover(bool gameover) {
	this->gameover = gameover;
}

