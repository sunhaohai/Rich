#include "rich.h"
#include "function.h"
#include "assist.h"

PLAYER USERS[4]; //玩家信息
int USERS_NUMBER; //玩家个数
MAP MAPS[MAX_POSITION]; //地图信息
int NOW_ID;
int game_over;
ROOT_STATE root = ROOT_ON;
ROUND_STATE round_state = ROUND_NULL;
int dice_num;
char TMP_DEBUG[50] = {'\0'};

int main()
{

    //if(freopen("./out.txt","w",stdout)==NULL)
        //fprintf(stderr,"error\n");


    game_over = 0;
    srand((unsigned)time(NULL));
    while (1) //main loop of the game
    {
        int init_user[] = {1,2,3,4};
        USERS_NUMBER = MAX_USER;
        _init_maps();
        _init_players(init_user,10000);
        
        printf("Enter a space to continue!\n");
        char start_tmp[50];
        int j = 0;
        while(1){
            fflush(stdin);
            my_getline(start_tmp,50);
            printf("%s",start_tmp);
            if(preset_cmd(start_tmp)){
                j++;
                root = ROOT_ON;
                continue;
            }
            if(j==0){
                init_game();
            }
            break;
        }
        //printf("j=%d\n",j );
        //init_game();
        display(MAPS);
        while (!game_over) //
        {
            for(int i=0;i<USERS_NUMBER;i++)
            {
                player_round(USERS+i);   
                NOW_ID = i;
                if(game_over) break;
            }
        }
        if(game_over) break;
    }

        //fclose(stdout);   

    return 0;
}

