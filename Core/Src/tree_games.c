#include "tree_games.h"

/*
 * tree_games.c
 *
 *  Created on: 12 Oct 2022
 *      Author: Harry
 */
void start_game(int state[]){

	int flash_delay = 50;

//	  flash(GREEN, 10, flash_delay);

	  if (state[0] != OFF){
		  blink(0, RED, 5, flash_delay);

	  } else if (state[1] != OFF){
		  blink(1, RED, 5, flash_delay);

	  } else if (state[2] != OFF){
		  pong();

	  } else if (state[3] != OFF){
		  random_set();

	  } else if (state[4] != OFF){
		  memory_game();

	  } else if (state[5] != OFF){
		  blink(5, RED, 5, flash_delay);

	  } else if (state[6] != OFF){
		  blink(6, RED, 5, flash_delay);

	  } else {
		  blink_til_button_press(RED, 10, 100, flash_delay);
	  }

	  HAL_Delay(100);
}


void memory_game(void){

	int game_state = NONE;
	int round = 1;
	int rand_num;
	int tmp_num;
	int button_state;
	int i;

    srand(time(NULL));

	wait_for_button_press();

	while(game_state != FINISH){

		rand_num = rand();
		tmp_num = rand_num;

		for(i=0;i<round;i++){
			if(tmp_num & 1 == 1){
				blink(1, RED, 1, 500);
			} else {
				blink(5, RED, 1, 500);
			}

			tmp_num = tmp_num >> 1;
		}

		tmp_num = rand_num;

		for(i=0;i<round;i++){
			wait_for_button_press();
			button_state = get_button_state_debounce(30);


//			FIX ME
			if(tmp_num & 1 == 1){
				blink(1, RED, 1, 500);
			} else {
				blink(5, RED, 1, 500);
			}

			tmp_num = tmp_num >> 1;
		}


		flash(GREEN, 5, 50);

		wait_for_button_press();
		if (get_button_state_debounce(30) == BOTH){
			game_state = FINISH;
		} else {
			wait_for_button_release(0);
		}

		round++;
	}

}

void random_set(void){
	while(get_button_state_debounce(0) == NONE){

		set_LED(rand() % NUM_LEDS, rand() % NUM_STATES);
		HAL_Delay(100);
	}
}

void pong(void){
	int ball_pos[7] = {0,0,0,0,0,0,0};
	int time_step;
	int bounces;
	int game_state = NONE;
	int left_press = 0;
	int right_press = 0;
	int last_move = HAL_GetTick();

	while(game_state != FINISH){

		if (game_state == NONE){
			for (int i=0;i<NUM_LEDS;i++){
				ball_pos[i] = OFF;
			}
			ball_pos[0] = GREEN;
			set_LEDs(ball_pos, 0);

			time_step = 300;
			game_state = CW;
			bounces = 0;

			wait_for_button_press();
			if (get_button_state_debounce(30) == BOTH){
				game_state = FINISH;
			} else {
				wait_for_button_release(0);
			}
		}

		if(BUT_LEFT && game_state == CCW){
			if (ball_pos[0] != 0){
				bounces += 1;
				game_state = CW;
			} else {
				game_state = GAMEOVER_LEFT;
			}
		}

		if(BUT_RIGHT && game_state == CW){
			if (ball_pos[6] != 0){
				bounces += 1;
				game_state = CCW;
			} else {
				game_state = GAMEOVER_RIGHT;
			}
		}

		if (HAL_GetTick() - last_move >= time_step){
			if(ball_pos[0] != 0 && game_state == CCW){
				game_state = GAMEOVER_LEFT;
			} else if (ball_pos[6] != 0 && game_state == CW){
				game_state = GAMEOVER_RIGHT;
			}


			switch (game_state) {
			case CW:
				rot_R(ball_pos);
				break;
			case CCW:
				rot_L(ball_pos);
				break;
			case GAMEOVER_LEFT:
				blink(0, RED, 5, 50);
				game_state = NONE;
				break;
			case GAMEOVER_RIGHT:
				blink(6, RED, 5, 50);
				game_state = NONE;
				break;
			}

			last_move = HAL_GetTick();
			set_LEDs(ball_pos, 0);

			if ((ball_pos[0] != 0 || ball_pos[0] != 0) && bounces % 5 == 0){
				time_step = time_step * 0.9;
			}

		}






	}

}


