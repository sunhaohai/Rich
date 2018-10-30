#include "run.h"
#include "display.h"
#include <string.h>
#include "init.h"

void players_run(PLAYER* player){
    int steps = _get_rand(1,6);
    (*player).position = ((*player).position + steps) % MAX_POSITION;
    display((*player).position, (*player).short_name);
}

void args_parse(char* arg, PLAYER* player){
    //for args parse
    char roll[] = "Roll";
    if(strcmp(roll, arg)==0){
        //printf("%d\n", (*player).position);
        players_run(player);
    }
    else return ;
}

void player_round(PLAYER* player){
    //players doing such as:Roll sell buy
    if((*player).skip_num>0){
        (*player).skip_num--;
        return;
    }
    printf("\n");
    print_prompt(player);
    char _args[10];
    scanf("%s",_args);
    args_parse(_args,player);
}
