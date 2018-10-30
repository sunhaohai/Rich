#ifndef _RUN_H_
#define _RUN_H_
#include "init.h"
#include "rich.h"

void dice_cmd(PLAYER *player, BOOL *end_round);
void robot_cmd(PLAYER *player, BOOL *end_round);
void query_cmd(PLAYER *player, BOOL *end_round);
void help_cmd();
void quit_cmd(PLAYER *player, BOOL *end_round);
void sell_cmd(PLAYER *plary, int position, BOOL *end_round);
void bolck_cmd(PLAYER *plary, int position, BOOL *end_round);
void bomb_cmd(PLAYER *plary, int position, BOOL *end_round);
void step_cmd(PLAYER *plary, int position, BOOL *end_round);
int _args_num_parse(char *arg);
void _args_parse_one(char *arg, PLAYER *player, BOOL *end_round);
void _args_parse_two(char *arg, PLAYER *player, int position, BOOL *end_round);
BOOL args_parse(char *arg, PLAYER *player);
void player_round(PLAYER *player);
void tool_house(PLAYER* player);
void gift_house(PLAYER* player);
void prison(PLAYER* player);
void magic_house(PLAYER* player);
void on_mine(char mine,PLAYER* player);
void pay_rent(int owner,int symbol,PLAYER* player);

#endif //_RUN_H_
