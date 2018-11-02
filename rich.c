#include "rich.h"
#include "function.h"
#include "assist.h"

PLAYER USERS[4]; //玩家信息
int USERS_NUMBER; //玩家个数
MAP MAPS[MAX_POSITION]; //地图信息
int game_over;

int main()
{
    game_over = 0;
    srand((unsigned)time(NULL));
    //while (1) //main loop of the game
    //{
        init_game();
        display(MAPS);
        save_cmd();
        
    //    while (!game_over) //
    //    {
    //        for(int i=0;i<USERS_NUMBER;i++) player_round(USERS+i);
    //    }
    //    game_over = 0;
    //}
    return 0;
}

