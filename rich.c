#include "rich.h"
#include "init.h"
#include "display.h"
#include "run.h"

PLAYER USERS[4]; //玩家信息
int USERS_NUMBER; //玩家个数
MAP MAPS[MAX_POSITION]; //地图信息

int main()
{
    int game_over = 0;
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

