#include "rich.h"
#include "function.h"
#include "assist.h"

PLAYER USERS[4]; //玩家信息
int USERS_NUMBER; //玩家个数
MAP MAPS[MAX_POSITION]; //地图信息
int game_over;
ROOT_STATE root = ROOT_OFF;

int main()
{
    game_over = 0;
    srand((unsigned)time(NULL));
    while (1) //main loop of the game
    {
        int init_user[] = {1,2,3,4};
        USERS_NUMBER = MAX_USER;
        _init_maps();
        _init_players(init_user,10000);
        

        /*
        printf("Enter a space to continue!");
        char start_tmp[20];
        int j = 0;
        while(1){
            my_getline(start_tmp,20);
            int input_len = sizeof(start_tmp)/sizeof(char);
            start_tmp[input_len-1]='\0'; 
            if(preset_cmd(start_tmp)) j++;
            if(j==0){
                init_game();
                break;
            }
        }
        */
        init_game();
        display(MAPS);
        while (!game_over) //
        {
            for(int i=0;i<USERS_NUMBER;i++) player_round(USERS+i);
        }
        game_over = 0;
    }
    return 0;
}

