#include "main.h"

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#define NONE 0
#define LEFT 1
#define RIGHT 2
#define BOTH 3

#define OFF 0
#define RED 1
#define GREEN 2

#define CW 1
#define CCW 2

#define NUM_STATES 3

#define NUM_LEDS 7

#define LED0(state) HAL_GPIO_WritePin(LED12_GPIO_Port, LED12_Pin, state&1); HAL_GPIO_WritePin(LED11_GPIO_Port, LED11_Pin, state&2);
#define LED1(state) HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, state&1); HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, state&2);
#define LED2(state) HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, state&1); HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, state&2);
#define LED3(state) HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, state&1); HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, state&2);
#define LED4(state) HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, state&1); HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, state&2);
#define LED5(state) HAL_GPIO_WritePin(LED10_GPIO_Port, LED10_Pin, state&1); HAL_GPIO_WritePin(LED9_GPIO_Port, LED9_Pin, state&2);
#define LED6(state) HAL_GPIO_WritePin(LED14_GPIO_Port, LED14_Pin, state&1); HAL_GPIO_WritePin(LED13_GPIO_Port, LED13_Pin, state&2);


#define BUT_LEFT HAL_GPIO_ReadPin(SWITCH_L_GPIO_Port,SWITCH_L_Pin)
#define BUT_RIGHT HAL_GPIO_ReadPin(SWITCH_R_GPIO_Port,SWITCH_R_Pin)

void set_LEDs(int state[], int del);

void set_LED(int number, int state);

void rot_R(int state[]);

void rot_L(int state[]);

void set_all(int colour);

void flash(int colour, int num, int del);

void blink(int LED, int colour, int num, int del);

void blink_til_button_press(int LED, int colour, int num, int del);

void wait_for_button_press(void);

void wait_for_button_release(int timeout);

int get_button_state_debounce(int del);


#endif /* INC_TREE_GAMES_H_ */
