#include <stdlib>
#include <string.h>

#include "run.h"
#include "init.h"
#include "rich.h"
#include "display.h"

extern PLAYER USERS[MAX_USER];
extern int USERS_NUMBER;
extern MAP MAPS[MAX_POSITION];
extern int game_over;
extern int dice_num;
extern char dot[8][30];

void _del_symbol(MAP* map,SYMBOL dels){
    //this is for player leave this position
    if(map->symbol==dels) {
        map->symbol = (map->pre_symbol)[MAX_USER-1];
        return;
    }
    for(int i=0;i<MAX_USER-1;i++){
        (map->pre_symbol)[i] = (map->pre_symbol)[i+1];
    }
}

BOOL _isuser_symbol(SYMBOL sym){
    if( (sym==SYMBOL_J)||(sym==SYMBOL_S)||(sym==SYMBOL_A)||(sym==SYMBOL_Q) )
    return TRUE;
    return FALSE;
}

void _add_symbol(MAP* map,SYMBOL adds){
    //for player arrive this position
    for(int i=0;i<MAX_USER-1;i++){
        if(!_isuser_symbol((map->pre_symbol)[i])){
            (map->pre_symbol)[i] = map->symbol;
            break;
        }
    }
    map->symbol=adds;
}

SYMBOL _get_symbol(PLAYER player){
    if(player.name==QIAN) return SYMBOL_Q;
    else if(player.name==JING) return SYMBOL_J;
    else if(player.name==SUN) return SYMBOL_S;
    else if(player.name==ATUBO) return  SYMBOL_A;
    else return SYMBOL_0;
}

void dice_cmd(PLAYER* player,BOOL* end_round){
    //dice random
    int steps = _get_rand(1,6);
    _del_symbol(&MAPS[(*player).position],_get_symbol(*player));
    (*player).position = ((*player).position + steps) % MAX_POSITION;
    _add_symbol(&MAPS[(*player).position],_get_symbol(*player));
    display((*player).position, (*player).short_name);
    *end_round = TRUE;
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

void sell_cmd(PLAYER* player, int position,BOOL* end_round){
    printf("Function is developing\n");
}

void bolck_cmd(PLAYER *player, int position,BOOL* end_round){
    //printf("Function is developing\n");
    int pos = position;
    int pos_tool;

    if((pos > 10) || (pos < -10))
    {
        printf("To use this tool, please input a number between -10 and 10\r\n");
    }
    else 
    {            
        pos_tool = (*player.position + pos) % MAX_POSITION;
        if((*player.tool[TOOL_L].num > 0) && (*player.tool[TOOL_L].num < 11))
        {
            *player.tool[TOOL_L].num--;
            MAPS[pos_tool].tool = TOOL_L;
            MAPS[pos_tool].symbol = SYMBOL_L;
            printf("Block is used successfully !\r\n");
         }
        else
        {
            *player.tool[TOOL_L].num = 0;
            printf("Sorry, you don't have available tool(Block) now !\r\n");
        }
    }
    *end_round = FALSE;
}

void bomb_cmd(PLAYER *player, int position,BOOL* end_round){
    //printf("Function is developing\n");
    int pos = position;
    int pos_tool;

    if((pos > 10) || (pos < -10))
    {
        printf("To use this tool, please input a number between -10 and 10\r\n");
    }
    else 
    {            
        pos_tool = (*player.position + pos) % MAX_POSITION;
        if((*player.tool[TOOL_B].num > 0) && (*player.tool[TOOL_B].num < 11))
        {
            *player.tool[TOOL_B].num--;
            MAPS[pos_tool].tool = TOOL_B;
            MAPS[pos_tool].symbol = SYMBOL_B;
            printf("Bomb is used successfully !\r\n");
         }
        else
        {
            *player.tool[TOOL_B].num = 0;
            printf("Sorry, you don't have available tool(Bomb) now !\r\n");
        }
    }
    *end_round = FALSE;
}

void robot_cmd(PLAYER* player,BOOL* end_round){
    //end_round :end this round or not
    //printf("Function is developing\n");
    char pos = *player.position;
    char pos_scan = pos;
    
    if((*player.tool[TOOL_R].num > 0) && (*player.tool[[TOOL_R]].num < 11))
    {
        *player.tool[TOOL_R].num--;
        while((++pos_scan % MAX_POSITION)  <= ((pos + 10) % MAX_POSITION))        
        {
            pos_scan %= MAX_POSITION;
            if((MAPS[pos_scan].tool > TOOL_NULL) && (MAPS[pos_scan].tool < TOOL_R))
            {
                if(TOOL_L == MAPS[pos_scan].tool)
                {
                    printf("Your robot found a Block !\r\n");
                }
                else
                {
                    printf("Your robot found a Bomb !\r\n");
                }
                MAPS[pos_scan].tool = TOOL_NULL;  //TO DO: symbol proc 

                break;
            }
            else
            {
                MAPS[pos_scan].tool = TOOL_NULL;
                if(pos_scan == ((pos + 10) % MAX_POSITION))
                {
                    printf("Your robot found nothing !\r\n");
                }
            }

        }
        
     }
    else
    {
        *player.tool[TOOL_R].num = 0;
        printf("Sorry, you don't have available tool(Robot) now !\r\n");
    }
    *end_round = FALSE;
}

void step_cmd(PLAYER *player, int position,BOOL* end_round){
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
