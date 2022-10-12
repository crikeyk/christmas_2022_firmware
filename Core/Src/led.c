#include "led.h"

void set_LEDs(int state[], int del){

	  LED1(state[0]);
	  HAL_Delay(del);
	  LED2(state[1]);
	  HAL_Delay(del);
	  LED3(state[2]);
	  HAL_Delay(del);
	  LED4(state[3]);
	  HAL_Delay(del);
	  LED5(state[4]);
	  HAL_Delay(del);
	  LED6(state[5]);
	  HAL_Delay(del);
	  LED7(state[6]);
	  HAL_Delay(del);
}

void rot_R(int state[]){
	int state_last = state[NUM_LEDS-1];
	for(int i=NUM_LEDS-1;i>0;i--){
		state[i] = state[i-1];
	}
	state[0] = state_last;
}

void rot_L(int state[]){
	int state_first = state[0];
	for(int i=0;i<NUM_LEDS-1;i++){
		state[i] = state[i+1];
	}
	state[NUM_LEDS-1] = state_first;
}

void set_all(int colour){
	int tmp_state[] = {colour, colour, colour, colour, colour, colour, colour};
	set_LEDs(tmp_state, 0);
}

void flash(int colour, int del){
	set_all(OFF);
	HAL_Delay(del);
	set_all(colour);
	HAL_Delay(del);
	set_all(OFF);

}
