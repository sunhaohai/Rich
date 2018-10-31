#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rich.h"
#include "init.h"
#include "display.h"
#include "run.h"
#include "test.h"

PLAYER USERS[4];
int USERS_NUMBER;
MAP MAPS[MAX_POSITION];
int game_over;
int dice_num;

int main()
{
    game_over = 0;
    srand((unsigned)time(NULL));
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

