#ifndef _RUN_H_
#define _RUN_H_
#include "init.h"
#include "rich.h"

void players_run(PLAYER *player);
void args_parse(char *arg, PLAYER *player);
void player_round(PLAYER *player);

#endif //_RUN_H_
