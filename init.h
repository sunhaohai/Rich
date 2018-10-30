#ifndef _INIT_H_
#define _INIT_H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rich.h"

int _get_rand(int min, int max);
void _clear();

int* _read_number();
int* _read_n_players(int min_player,int max_player,int min_n,int max_n);
int *_start_game();

void _init_players(int *users, int init_money);
void _init_maps();
void init_game();

void use_tool();
void _init_one_map(MAP *map, int posi, MAP_TYPE type, USER_NAME name, TOOL_TYPE tool,
                   char mine, PRICE price, SYMBOL symbol);
char _get_player_symbol(USER_NAME name);

#endif //_INIT_H_
