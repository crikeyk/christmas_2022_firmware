#include "gpio.h"
#include "stm32f0xx_hal.h"

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

void blink(int LED, int colour, int num, int del){
	for(int i=0;i<num;i++){
		set_LED(LED, colour);
		HAL_Delay(del);
		set_LED(LED, OFF);
		HAL_Delay(del);
	}
}

void blink_til_button_press(int LED, int colour, int num, int del){
	while(get_button_state_debounce(30) == NONE){
		for(int i=0;i<num;i++){
			set_LED(LED, colour);
			HAL_Delay(del);
			set_LED(LED, OFF);
			HAL_Delay(del);
		}
	}
}

void wait_for_button_press(void){
	while(get_button_state_debounce(30) == NONE){
	}
}

void wait_for_button_press_timeout(int timeout){
	if (timeout <= 0){timeout = 999999;}
	int timeout_tick = HAL_GetTick() + timeout;
	while(HAL_GetTick() < timeout_tick && get_button_state_debounce(0) == NONE){
	}
}

void wait_for_button_release(int timeout){

	if (timeout <= 0){timeout = 999999;}

	int timeout_tick = HAL_GetTick() + timeout;
	while(HAL_GetTick() < timeout_tick && get_button_state_debounce(0) != NONE){
	}

}

int get_button_state_debounce(int delay)
{
	int button_state = NONE;
	if(BUT_LEFT || BUT_RIGHT){
		HAL_Delay(delay);
		if(BUT_LEFT){
			if(BUT_RIGHT){
				button_state = BOTH;
			} else {
				button_state = LEFT;
			}
		} else if (BUT_RIGHT){
			button_state = RIGHT;
		}
	}
	return button_state;
}
