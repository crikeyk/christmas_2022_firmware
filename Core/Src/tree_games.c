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
		  blink(2, RED, 5, flash_delay);

	  } else if (state[3] != OFF){
		  random_set();

	  } else if (state[4] != OFF){
		  blink(4, RED, 5, flash_delay);

	  } else if (state[5] != OFF){
		  blink(5, RED, 5, flash_delay);

	  } else if (state[6] != OFF){
		  blink(6, RED, 5, flash_delay);

	  } else {
		  blink_til_button_press(RED, 10, 100, flash_delay);
	  }

	  HAL_Delay(100);
}

void random_set(void){
	while(get_button_state_debounce(0) == NONE){
		set_LED(rand() % NUM_LEDS, rand() % NUM_STATES);
		HAL_Delay(100);
	}
}


