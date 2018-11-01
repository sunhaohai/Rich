#ifndef _ASSIST_H_
#define _ASSIST_H_
//基本函数
#include "rich.h"

void _clear();
int *_read_number();
int *_read_n_players(int min_player, int max_player, int min_n, int max_n);

int _get_rand(int min, int max);
char _get_player_symbol(USER_NAME name);
int _get_place_price(PRICE place);
char _get_map_display(SYMBOL symbol);
SYMBOL _get_symbol(PLAYER player);


void print_red(char *chars);
void print_green(char *chars);
void print_blue(char *chars);
void print_yellow(char *chars);
void print_player(char *chars, USER_NAME name);
void print_prompt(PLAYER *player);
void _print_map_symbol(MAP *map);

BOOL args_parse(char *arg, PLAYER *player);
void _args_parse_one(char *arg, PLAYER *player, BOOL *end_round);
void _args_parse_two(char *arg, PLAYER *player, int position, BOOL *end_round);
int _args_num_parse(char *arg);
BOOL _isuser_symbol(SYMBOL sym);

void _add_symbol(MAP* map,SYMBOL adds);
void _del_symbol(MAP *map, SYMBOL dels);
void display_run_map(PLAYER *player, int fin_position);

void prison(PLAYER *player);
void magic_house(PLAYER *player);
void on_mine(char mine, PLAYER *player);
void gift_house(PLAYER *player);
void tool_house(PLAYER *player);

void pay_rent(PLAYER *player, MAP *maps);
void buy_upper_house(PLAYER *player, MAP *maps);

void players_end_run(PLAYER *player, BOOL *end_round);
void players_run_in_the_way(PLAYER *player, int steps, BOOL *end_round);

void _usercmp(PLAYER *user1, PLAYER *user2);
void rm_user(PLAYER *users, USER_NAME name, int* user_size);
#endif //_ASSIST_H_
