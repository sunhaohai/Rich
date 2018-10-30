#include "run.h"
#include "display.h"
#include <string.h>
#include "init.h"

extern PLAYER USERS[4];
extern int USERS_NUMBER;
extern MAP MAPS[MAX_POSITION];
extern int game_over;
extern int dice_num;

void dice_cmd(PLAYER* player,BOOL* end_round){
    //dice random
    int steps = _get_rand(1,6);
    int pos_temp = 0;
    for(int i = 1; i <= steps; i++){
        pos_temp = (player->position + i) % MAX_POSITION;
        switch(MAPS[pos_temp].symbol)
        {
            case SYMBOL_L:
                player->position = pos_temp;
                display((*player).position, (*player).short_name);
                *end_round = TRUE;
                return;
            case SYMBOL_B:
                player->position = 14;
                player->skip_num = 3;
                display((*player).position, (*player).short_name);
                *end_round = TRUE;
                return;
        }
    }
    (*player).position = ((*player).position + steps) % MAX_POSITION;
    //判断user最后停留地
    int pos_temp = (*player).position;
    if(MAPS[pos_temp].owner){
        pay_rent(MAPS[pos_temp].owner, MAPS[pos_temp].symbol,player);
    }else if(MAPS[pos_temp].symbol == 0){
        buy_house(player);  
    }else{
        switch(MAPS[pos_temp].symbol){
            case SYMBOL_T:
                int tool_num = player->tool[0].num + player->tool[1].num + player->tool[2].num;
                if( player->point < 30){
                    printf("You are too pool to buy tools");
                }else if(tool_num >= 10){
                    printf("You already have a maximum limit number of tools");
                }else{
                    tool_house(player);
                }
                break;
            case SYMBOL_G:
                gift_house(player);
                break;
            case SYMBOL_M: 
                magic_house(player);
                break;
            case SYMBOL_P:
                prison(player);
                break;
            case SYMBOL_$:       
                on_mine(MAPS[pos_temp].mine,player);
                break;
            default:
                return;
        }
    }
    *end_round = TRUE;
    display((*player).position, (*player).short_name);
}

void robot_cmd(PLAYER* player,BOOL* end_round){
    //end_round :end this round or not
    printf("Function is developing\n");
}

void query_cmd(PLAYER *player,BOOL* end_round){
    printf("Function is developing\n");
}

void help_cmd(){
    printf("Function is developing\n");
}

void quit_cmd(PLAYER *player,BOOL* end_round){
    printf("Function is developing\n");
}

void sell_cmd(PLAYER* plary, int position,BOOL* end_round){
    printf("Function is developing\n");
}

void bolck_cmd(PLAYER *plary, int position,BOOL* end_round){
    printf("Function is developing\n");
}

void bomb_cmd(PLAYER *plary, int position,BOOL* end_round){
    printf("Function is developing\n");
}

void step_cmd(PLAYER *plary, int position,BOOL* end_round){
    printf("Function is developing\n");
}

int _args_num_parse(char* arg){
    //judge arg field number
    int args_n=1;
    int args_size = sizeof(arg)/sizeof(char);
    for(int i=0;i<args_size;i++){
        if(arg[i]==' ') args_n += 1;
    }
    return args_n;
}

void _args_parse_one(char* arg, PLAYER* player,BOOL* end_round){
    //deal cmd without param
    if(strcmp(ROLL,arg)==0) dice_cmd(player,end_round);
    else if(strcmp(ROBOT,arg)==0) robot_cmd(player,end_round);
    else if(strcmp(QUERY,arg)==0) query_cmd(player,end_round);
    else if(strcmp(QUIT,arg)==0) quit_cmd(player,end_round);
    else help_cmd();
}

void _args_parse_two(char *arg, PLAYER *player, int position,BOOL* end_round){
    //deal cmd with param
    if(strcmp(SELL,arg)==0) sell_cmd(player,position,end_round);
    else if(strcmp(BLOCK,arg)==0) bolck_cmd(player,position,end_round);
    else if(strcmp(BOMB,arg)==0) bomb_cmd(player,position,end_round);
    else if(strcmp(STEP,arg)==0) step_cmd(player,position,end_round);
    else help_cmd();
}

BOOL args_parse(char* arg, PLAYER* player){
    //for args parse
    BOOL end_round=FALSE; //end this round or not
    int args_field_n = _args_num_parse(arg);
    if(args_field_n==1) _args_parse_one(arg,player,&end_round);
    else if(args_field_n==2){
        char* t=strtok(arg," ");
        char* f1=t;
        t=strtok(NULL," ");
        char* f2=t;
        _args_parse_two(f1,player,atoi(f2),&end_round);
    }
    else help_cmd();
    return end_round;
}

void player_round(PLAYER* player){
    //players doing such as:Roll sell buy
    if((*player).skip_num>0){
        (*player).skip_num--;
        return;
    }
    while(1){
        printf("\n");
        print_prompt(player);
        char _args[10];
        rewind(stdin);
        scanf("%s", _args);
        if(args_parse(_args, player)) break;
    }
}

void tool_house(PLAYER* player){
    printf("Welcome to tool house, please choose a tool:\n");
    char tool;
    while(1){
        if(player->point <= 50){
        printf("you only can buy 2:robot baby \n");
        printf("if you want to leave,please enter F \n");
        scanf("%c",tool);
        }else{
            printf("1:road barrier 2:robot baby 3:bomb\n");
            printf("if you want to leave,please enter F \n");
            scanf("%c",tool);
        }
        switch(tool){
            case '1':
                player->tool[1].num++;
                return;
            case '2':
                player->tool[2].num++;
                return;
            case '3':
                player->tool[3].num++;
                return;
            case 'F':
                return;
            default:
                printf("please choose again ~~~");
                break;
        }
    }
}

void gift_house(PLAYER* player){
    int gift;
    printf("Welcome to gift house, please choose a gift：\n");
    printf("1:money 2:point card 3: lucky god\n");
    while(1){
        scanf("%d",&gift);
        switch(gift){
            case 1:
                (*player).money += 2000;
                return;
            case 2:
                (*player).point += 200;
                return;
            case 3:
                (*player).lucky_god += 5;
                return;
            default:
                printf("please choose again ~~~");
                break;
        }
    }
}

void prison(PLAYER* player){
    player->skip_num += 2;
    return;
}

void on_mine(char mine,PLAYER* player){
    player->money += mine;
    return;
}

void pay_rent(int owner,int symbol,PLAYER* player){
    
    switch(symbol){
        case SYMBOL_0:

    }
}