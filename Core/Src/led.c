#include "led.h"

void set_LEDs(int state[], int del){

	for(int i=0;i<NUM_LEDS;i++){
		set_LED(i, state[i]);
	}
}

void set_LED(int number, int state){
	switch(number){
	case 0:
		LED0(state);
		break;
	case 1:
		LED1(state);
		break;
	case 2:
		LED2(state);
		break;
	case 3:
		LED3(state);
		break;
	case 4:
		LED4(state);
		break;
	case 5:
		LED5(state);
		break;
	case 6:
		LED6(state);
		break;
	}
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

void flash(int colour, int num, int del){
	for(int i=0;i<num;i++){
		set_all(colour);
		HAL_Delay(del);
		set_all(OFF);
		HAL_Delay(del);
	}
}
