#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include<stdio.h>
#include<string.h>
#include "rich.h"

/* change the value of position with short_name */
void oneD2twoD(char position, char short_name);
/* print map ,param [in] = map */
void printMap(char line[]);

void display(char position, char short_name);

void print_red(char *chars);
void print_green(char *chars);
void print_blue(char *chars);
void print_yellow(char *chars);
void print_player(char *chars, USER_NAME name);
void print_prompt(PLAYER *player);

#endif //_DISPLAY_H_
