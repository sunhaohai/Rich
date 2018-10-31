#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rich.h"
#include "init.h"
#include "display.h"
#include "run.h"

PLAYER USERS[4];
int USERS_NUMBER;
MAP MAPS[MAX_POSITION];
int game_over;
int dice_num;

char dot[8][30] = {
    "s0000000000000H0000000000000T\n",
    "$                           0\n",
    "$                           0\n",
    "$                           0\n",
    "$                           0\n",
    "$                           0\n",
    "$                           0\n",
    "M0000000000000P0000000000000G"};

int main()
{
    game_over = 0;

    while (1) //main loop of the game
    {
        init_game();
        display(MAPS);
        while (!game_over) //
        {
            for(int i=0;i<USERS_NUMBER;i++) player_round(USERS+i);
        }
    }
    return 0;
}

