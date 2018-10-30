#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include<stdio.h>
#include<string.h>
#include "rich.h"
typedef enum
{
    RED0_Q = 96, 
    RED1_Q,
    RED2_Q, 
    RED3_Q,
    GREEN0_A, 
    GREEN1_A,
    GREEN2_A,
    GREEN3_A,
    BLUE0_S, 
    BLUE1_S, 
    BLUE2_S,
    BLUE3_S,
    YELLOW0_J,
    YELLOW1_J,
    YELLOW2_J,
    YELLOW3_J
}COLOR;
/* change the value of position with short_name */
void oneD2twoD(char position, char short_name);
/* print map ,param [in] = map */
void printMap(char line[], char position, char short_name);
void display(char position, char short_name);

void print_red(char *chars);
void print_green(char *chars);
void print_blue(char *chars);
void print_yellow(char *chars);

void print_player(char *chars, USER_NAME name);

#endif //_DISPLAY_H_
