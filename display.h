#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include<stdio.h>
#include<string.h>
#include "rich.h"

void display(MAP* maps);

void print_red(char *chars);
void print_green(char *chars);
void print_blue(char *chars);
void print_yellow(char *chars);

void print_player(char *chars, USER_NAME name);

#endif //_DISPLAY_H_
