#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <stdio.h>

using namespace std;
//constants and enumerations

const float FPS = 60;
const int player1_SIZE = 20;
const int player2_SIZE = 20;
int lives = 5;
int lives2 = 5;

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_ENTER
};
enum MYKEYS2 {
	KEY_W, KEY_S, KEY_A, KEY_D
};

enum states { INTRO, ALIVE, DEAD };//1 is alive and 2 is dead.

enum Direction { RIGHT, LEFT, UP, DOWN };

enum Direction2 { D, A, W, S };


int main() {

	//set up matrix
	int grid[50][50];
	/*int grid2[50][50];*/
	for (int i = 0; i< 50; i++)
		for (int j = 0; j < 50; j++) {
			//set all to 0s except edges
			grid[i][j] = 0;
			if (i == 0 || i == 49 || j == 0 || j == 49)
				grid[i][j] = 1;
		}

	//for (int k = 0; k< 50; k++)
	//	for (int l = 0; l < 50; l++) {
	//		//set all to 0s except edges
	//		grid2[k][l] = 0;
	//		if (k == 0 || k == 49 || l == 0 || l == 49)
	//			grid2[k][l] = 1;
	//	}

	//print to console for testing
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++)
			cout << grid[i][j];
		cout << endl;
	}

	/*for (int k = 0; k < 50; k++) {
	for (int l = 0; l < 50; l++)
	cout << grid2[k][l];
	cout << endl;
	}*/
	//set up variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *player1 = NULL;
	ALLEGRO_BITMAP *player2 = NULL;
	ALLEGRO_SAMPLE *sample = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance = NULL;

	cout << "flag" << endl;
	int player1_x = 300;
	int player1_y = 400;


	int player2_x = 200;
	int player2_y = 300;
	bool key[5] = { false, false, false, false,false };
	bool key2[4] = { false, false, false , false };
	bool redraw = true;
	bool doexit = false;
	//x and y velocity
	int dx1 = 0;
	int dy1 = 0;
	int dx2 = 0;
	int dy2 = 0;
	int dir = 0;
	int dir2 = 0;
	int state = INTRO;


	//set up allegro stuff
	al_init();
	al_init_primitives_addon();

	al_init_font_addon();

	al_init_ttf_addon();

	al_install_audio();

	al_init_acodec_addon();

	ALLEGRO_FONT *font = al_load_ttf_font("28DaysLater.ttf", 72, 0);
	al_install_keyboard();


	al_reserve_samples(10);

	timer = al_create_timer(1.0 / FPS);

	display = al_create_display(500, 500);

	sample = al_load_sample("Garys_song.wav");

	instance = al_create_sample_instance(sample);

	al_set_sample_instance_playmode(instance, ALLEGRO_PLAYMODE_LOOP);

	al_attach_sample_instance_to_mixer(instance, al_get_default_mixer());



	player1 = al_create_bitmap(player1_SIZE, player1_SIZE);

	al_set_target_bitmap(player1);

	al_clear_to_color(al_map_rgb(255, 0, 255));

	player2 = al_create_bitmap(player2_SIZE, player2_SIZE);

	al_set_target_bitmap(player2);

	al_clear_to_color(al_map_rgb(255, 0, 255));


	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);


	cout << "flag2" << endl;
	//game loop
	while (!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//physics section
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (state == INTRO) {
				if (key[KEY_ENTER] == true)
					state = ALIVE;

			}


			if (state == ALIVE) {
				al_play_sample_instance(instance);
				if (key[KEY_UP]) {
					//notice we just set the velocity, NOT the position... the bike will move up until another
					dy1 = -3;
					dx1 = 0;
					dir = UP;//used for collision later
				}

				if (key[KEY_DOWN]) {
					dy1 = 3;
					dx1 = 0;
					dir = DOWN;
				}

				if (key[KEY_LEFT]) {
					dx1 = -3;
					dy1 = 0;
					dir = LEFT;
				}

				if (key[KEY_RIGHT]) {
					dx1 = 3;
					dy1 = 0;
					dir = RIGHT;
				}
				if (key2[KEY_W]) {
					//notice we just set the velocity, NOT the position... the bike will move up until another
					dy2 = -3;
					dx2 = 0;
					dir2 = W;//used for collision later
				}

				if (key2[KEY_S]) {
					dy2 = 3;
					dx2 = 0;
					dir2 = S;
				}

				if (key2[KEY_A]) {
					dx2 = -3;
					dy2 = 0;
					dir2 = A;
				}

				if (key2[KEY_D]) {
					dx2 = 3;
					dy2 = 0;
					dir2 = D;
				}
				cout << "flag3" << endl;
				//move player one
				player1_x += dx1;
				player1_y += dy1;


				cout << "flag b" << endl;
				cout << "drawing player 1 at " << player1_x / 10 << " , " << player1_x / 10 << endl;


				//draw a line behind the bike
				grid[(player1_x) / 10][(player1_y) / 10] = 2;
				cout << "drawing player 2 at " << player1_y / 10 << " , " << player1_y / 10 << endl;
				player2_x += dx2;
				player2_y += dy2;



				grid[(player2_x) / 10][(player2_y) / 10] = 2;


				cout << "flag a" << endl;

				//check right collision for p1
				if (dir == RIGHT && grid[(player1_x + 10) / 10][player1_y / 10] != 0) {
					cout << "RIGHT CRASH" << endl; //you need to do something more here :/

					grid[(player1_x) / 10][(player1_y) / 10] = 0;
					if (grid[(player1_x) / 10][(player1_y) / 10] == 0) {
						for (int i = 0; i < 50; i++) {
							for (int j = 0; j < 50; j++) {
								grid[i][j] = 0;

							}
						}
					}


					player1_x = 300;
					player1_y = 400;
					lives = lives - 1;
					cout << lives << endl;
				}

				//check left collision for p1
				if (dir == LEFT && grid[(player1_x - 10) / 10][player1_y / 10] != 0) {
					cout << "LEFT CRASH" << endl;
					grid[(player1_x) / 10][(player1_y) / 10] = 0;
					if (grid[(player1_x) / 10][(player1_y) / 10] == 0) {
						for (int i = 0; i < 50; i++) {
							for (int j = 0; j < 50; j++) {
								grid[i][j] = 0;

							}
						}
					}


					player1_x = 300;
					player1_y = 400;
					lives = lives - 1;
					cout << lives << endl;
				}


				//check down collision for p1
				if (dir == DOWN && grid[player1_x / 10][(player1_y + 10) / 10] != 0) {
					cout << "DOWN CRASH" << endl;
					grid[(player1_x) / 10][(player1_y) / 10] = 0;
					if (grid[(player1_x) / 10][(player1_y) / 10] == 0) {
						for (int i = 0; i < 50; i++) {
							for (int j = 0; j < 50; j++) {
								grid[i][j] = 0;

							}
						}
					}


					player1_x = 300;
					player1_y = 400;
					lives = lives - 1;
					cout << lives << endl;
				}

				//check up collision for p1
				if (dir == UP && grid[player1_x / 10][(player1_y - 10) / 10] != 0) {
					cout << "UP CRASH" << endl;
					grid[(player1_x) / 10][(player1_y) / 10] = 0;
					if (grid[(player1_x) / 10][(player1_y) / 10] == 0) {
						for (int i = 0; i < 50; i++) {
							for (int j = 0; j < 50; j++) {
								grid[i][j] = 0;

							}
						}
					}


					player1_x = 300;
					player1_y = 400;
					lives = lives - 1;
					cout << lives << endl;
				}

				cout << "flag5" << endl;

				/////////////////	


				if (dir2 == D && grid[(player2_x + 10) / 10][player2_y / 10] != 0) {
					cout << "RIGHT CRASH" << endl; //you need to do something more here :/

					grid[(player2_x) / 10][(player2_y) / 10] = 0;
					if (grid[(player2_x) / 10][(player2_y) / 10] == 0) {
						for (int i = 0; i < 50; i++) {
							for (int j = 0; j < 50; j++) {
								grid[i][j] = 0;

							}
						}
					}


					player2_x = 200;
					player2_y = 300;
					lives2 = lives2 - 1;
					cout << lives2 << endl;
				}


				//check left collision for p1
				if (dir2 == A && grid[(player2_x - 10) / 10][player2_y / 10] != 0) {
					cout << "LEFT CRASH" << endl;
					grid[(player2_x) / 10][(player2_y) / 10] = 0;
					if (grid[(player2_x) / 10][(player2_y) / 10] == 0) {
						for (int i = 0; i < 50; i++) {
							for (int j = 0; j < 50; j++) {
								grid[i][j] = 0;

							}
						}
					}


					player2_x = 200;
					player2_y = 300;
					lives2 = lives2 - 1;
					cout << lives2 << endl;
				}

				cout << "flag4" << endl;
				//check down collision for p1
				if (dir2 == S && grid[player2_x / 10][(player2_y + 10) / 10] != 0) {
					cout << "DOWN CRASH" << endl;
					grid[(player2_x) / 10][(player2_y) / 10] = 0;
					if (grid[(player2_x) / 10][(player2_y) / 10] == 0) {
						for (int i = 0; i < 50; i++) {
							for (int j = 0; j < 50; j++) {
								grid[i][j] = 0;

							}
						}
					}


					player2_x = 200;
					player2_y = 300;
					lives2 = lives2 - 1;
					cout << lives2 << endl;
				}

				//check up collision for p1
				if (dir2 == W && grid[player2_x / 10][(player2_y - 10) / 10] != 0) {
					cout << "UP CRASH" << endl;
					grid[(player2_x) / 10][(player2_y) / 10] = 0;
					if (grid[(player2_x) / 10][(player2_y) / 10] == 0) {
						for (int i = 0; i < 50; i++) {
							for (int j = 0; j < 50; j++) {
								grid[i][j] = 0;

							}
						}
					}


					player2_x = 200;
					player2_y = 300;
					lives2 = lives2 - 1;
					cout << lives2 << endl;
				}
				///////////////////////////


				if (state == DEAD) {
					if (key[KEY_ENTER] == true)
						state = ALIVE;

				}
			}

			redraw = true;
		}
		//kill program when window x is pressed
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		//check if keys are pressed down
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;
			case ALLEGRO_KEY_ENTER:
				key[KEY_ENTER] = true;
				break;
			case ALLEGRO_KEY_W:
				key2[KEY_W] = true;
				break;
			case ALLEGRO_KEY_S:
				key2[KEY_S] = true;
				break;
			case ALLEGRO_KEY_A:
				key2[KEY_A] = true;
				break;
			case ALLEGRO_KEY_D:
				key2[KEY_D] = true;
				break;


			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}
		//check if keys released
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;
			case ALLEGRO_KEY_ENTER:
				key[KEY_ENTER] = false;
				break;
			case ALLEGRO_KEY_W:
				key2[KEY_W] = false;
				break;
			case ALLEGRO_KEY_S:
				key2[KEY_S] = false;
				break;
			case ALLEGRO_KEY_A:
				key2[KEY_A] = false;
				break;
			case ALLEGRO_KEY_D:
				key2[KEY_D] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}


		//RENDER SECTION
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			//wipe screen black
			al_clear_to_color(al_map_rgb(0, 0, 0));

			//walk throught matrix, color is white and twos blue
			if (state == INTRO) {
				al_draw_text(font, al_map_rgb(255, 255, 255), 500 / 2, (500 / 5), ALLEGRO_ALIGN_CENTRE, "WELCOME");
				al_flip_display();

			}
			if (state == ALIVE) {
				for (int i = 0; i < 50; i++) {
					for (int j = 0; j < 50; j++) {
						if (grid[i][j] == 1)
							al_draw_filled_rectangle(i * 10, j * 10, i * 10 + 10, j * 10 + 10, al_map_rgb(255, 255, 255));
						if (grid[i][j] == 2)
							al_draw_filled_rectangle(i * 10, j * 10, i * 10 + 10, j * 10 + 10, al_map_rgb(0, 25, 255));
					}
				}


				if (lives == 0) {
					state = DEAD;

				}
				if (lives2 == 0) {
					state = DEAD;
				}
				//draw player
				al_draw_bitmap(player1, player1_x - 10, player1_y - 10, 0);
				al_draw_bitmap(player2, player2_x - 10, player2_y - 10, 0);

				al_flip_display();
			}
			if (state == DEAD) {
				al_draw_text(font, al_map_rgb(255, 255, 255), 500 / 2, (500 / 5), ALLEGRO_ALIGN_CENTRE, "YOU SUCK");
				al_flip_display();
			}


		}//end render section

	}//end game loop


	 //clear up memory
	al_destroy_sample(sample);
	al_destroy_sample_instance(instance);
	al_destroy_bitmap(player1);
	al_destroy_bitmap(player2);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}