/*
 * tree_games.h
 *
 *  Created on: 12 Oct 2022
 *      Author: Harry
 */

#ifndef INC_TREE_GAMES_H_
#define INC_TREE_GAMES_H_

#include "gpio.h"
#include "stdlib.h"

#define GAMEOVER_LEFT 10
#define GAMEOVER_RIGHT 11

void start_game(int state[]);

void random_set(void);

void pong(void);

void memory_game(void);

#endif /* INC_TREE_GAMES_H_ */
