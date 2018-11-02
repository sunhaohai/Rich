#include <stdlib>
#include <string.h>

#include "run.h"
#include "rich.h"
#include "display.h"

extern PLAYER USERS[MAX_USER];
extern int USERS_NUMBER;
extern MAP MAPS[MAX_POSITION];
extern int game_over;
extern int dice_num;

void display_run_map(PLAYER* player, int fin_position){
    //
    _del_symbol(&MAPS[(*player).position], _get_symbol(*player));
    (*player).position = fin_position;
    _add_symbol(&MAPS[(*player).position], _get_symbol(*player));
    display(MAPS);
}

void buy_house(PLAYER* player){
    printf("waiting to do!\n");
}

int players_run_in_the_way(PLAYER *player, BOOL *end_round)
{
    int steps = _get_rand(1, 6);
    int pos_temp = 0;
    for (int i = 1; i < steps; i++)
    {
        pos_temp = (player->position + 1) % MAX_POSITION;
        switch (MAPS[pos_temp].symbol)
        {
        case SYMBOL_L:
            //player->position = pos_temp;
            display_run_map(player, pos_temp);
            *end_round = TRUE;
            return;
        case SYMBOL_B:
            //player->position = 14;
            player->skip_num += 2;
            display_run_map(player, 14);
            *end_round = TRUE;
            return;
        default:
            display_run_map(player, pos_temp);
            break;
        }
    }
    return steps;
}

void players_end_run(PLAYER *player, BOOL *end_round)
{
    int pos_temp = (*player).position;
    if (MAPS[pos_temp].owner)
    {
        pay_rent(MAPS[pos_temp].owner, MAPS[pos_temp].symbol, player);
    }
    else if (MAPS[pos_temp].symbol == 0)
    {
        buy_house(player);
    }
    else
    {
        int tool_num = player->tool[0].num + player->tool[1].num + player->tool[2].num;
        switch (MAPS[pos_temp].symbol)
        {
        case SYMBOL_T:
            if (player->point < 30)
            {
                printf("You are too pool to buy tools");
            }
            else if (tool_num >= 10)
            {
                printf("You already have a maximum limit number of tools");
            }
            else
            {
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
            on_mine(MAPS[pos_temp].mine, player);
            break;
        default:
            return;
        }
    }
    *end_round = TRUE;
}

void tool_house(PLAYER *player)
{
    printf("Welcome to tool house, please choose a tool:\n");
    char tool;
    while (1)
    {
        if (player->point <= 50)
        {
            printf("you only can buy 2:robot baby \n");
            printf("if you want to leave,please enter F \n");
            scanf("%c", &tool);
        }
        else
        {
            printf("1:road barrier 2:robot baby 3:bomb\n");
            printf("if you want to leave,please enter F \n");
            scanf("%c", &tool);
        }
        switch (tool)
        {
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

void gift_house(PLAYER *player)
{
    int gift;
    printf("Welcome to gift house, please choose a gift：\n");
    printf("1:money 2:point card 3: lucky god\n");
    while (1)
    {
        scanf("%d", &gift);
        switch (gift)
        {
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

void prison(PLAYER *player)
{
    player->skip_num += 2;
    return;
}

void magic_house(PLAYER *player)
{
    printf("Waiting to do\n");
}

void on_mine(char mine, PLAYER *player)
{
    player->money += mine;
    return;
}

void pay_rent(int owner, int symbol, PLAYER *player)
{

    /*switch(symbol){
        case SYMBOL_0:

    }*/
    printf("Waiting to do\n");
}

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
    if( (sym<=SYMBOL_J)&&(sym>=SYMBOL_Q) )
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

int dice_cmd(PLAYER* player,BOOL* end_round){
    //dice random
    int steps = players_run_in_the_way(player, end_round);
    if (*end_round)
        return;
    display_run_map(player,player->position+1);
    //判断user最后停留地
    players_end_run(player, end_round);
    *end_round = TRUE;
    return steps;
}

void query_cmd(PLAYER *player, BOOL *end_round) //查看自家资产(钱、点数、房产、道具)
{
    printf("your total money:%ld\n", player->money);
    printf("your total point:%ld\n", player->point);

    printf("your total house:");                                      //显示房产（等级和位置）
    HOUSE* tmp = player->house;
    if(!tmp) printf("you have no house!\n");
    while(tmp){
       printf("your house position:%c and its level:%c\n",player->house->position,player->house->level); //显示房产位置
       tmp = tmp+1;
    }

    printf("\nyour total tool>>\n");                            //显示道具（种类和数量）
    printf("Block's number:%d\n", player->tool[TOOL_L].num); //路障数量
    printf("Bomb's number:%d\n", player->tool[TOOL_B].num);  //炸弹数量
    printf("Robot's number:%d\n", player->tool[TOOL_R].num); //路障数量
}

void help_cmd() //查看命令帮助
{
    printf("Roll : Roll the dice 1~6 \n");
    printf("Sell n : When it's the buyer's turn to play, sell a property with an absolute n on his map at twice the total cost of investment. \n");
    printf("Block n :  You can place the roadblock anywhere in the front and back 10 steps of the current position. Any player passing the roadblock will be intercepted. The props are effective once. \n");
    printf("Bomb n : You can place the bomb anywhere in the front and back 10 steps of the current position. Any player passing through the bomb will be wounded. To the hospital for three days.  \n");
    printf("Robot : Using this prop, you can clean up any other props in the 10 steps on the road ahead, such as bombs and roadblocks. \n");
    printf("Query : Display your assets. \n");
    printf("Help : View command help. \n");
    printf("Quit : Forced return. \n");
    printf("Step n : Telecontrol dice. \n");
}

void quit_cmd(PLAYER *player,BOOL* end_round){
    printf("Function is developing\n");
}

void sell_cmd(PLAYER *player, int position, BOOL *end_round) //轮到买家玩时，出售自己地图上绝对位置为n的房产，价格为投资总成本的2倍
{
    //int *HOUSE=(HOUSE *)malloc(sizeof(HOUSE)*61);
    if (MAPS[position].owner == player->name) //判断是否为自己的房产
    {
        char sell_level;             //相应等级
        for (int i = 0; i < 61; i++) //遍历查找相应的level
        {
            if (position == (player->house)->position)
            {
                sell_level = player->house->level;
            }
        }
        player->money = player->money + 2 * ((player->house->level + 1) * MAPS[position].price); //钱增加2倍投资成本

        player->house->position = NULL; //玩家房产清空
        MAPS[position].type = MAP_COM;  //该地变为公有
    }
    else
    {
        printf("This land is not your asset. \n");
    }
}

void bolck_cmd(PLAYER *player, int position,BOOL* end_round){
    //printf("Function is developing\n");
    int pos = position;
    int pos_tool;

    if((pos > 10) || (pos < -10) || (!pos))
    {
        printf("To use this tool, please input a number between -10 and 10 indicate behind or before you, 0 is not allowed! \r\n");
    }
    else 
    {            
        pos_tool = (player->position + pos) % MAX_POSITION;
        if((MAPS[pos_tool].tool > TOOL_NULL) || _isuser_symbol(MAPS[pos_tool].symbol))
        {
            printf("Can not be used in this place !\r\n");
            *end_round = FALSE;
            return;
        }
        if((player->tool[TOOL_L].num > 0) && (player->tool[TOOL_L].num < 11))
        {
            player->tool[TOOL_L].num--;
            MAPS[pos_tool].tool = TOOL_L;
            printf("Block is used successfully !\r\n");
         }
        else
        {
            player->tool[TOOL_L].num = 0;
            printf("Sorry, you don't have available tool(Block) now !\r\n");
        }
    }
    *end_round = FALSE;
}

void bomb_cmd(PLAYER *player, int position,BOOL* end_round){
    //printf("Function is developing\n");
    int pos = position;
    int pos_tool;

    if((pos > 10) || (pos < -10) || (!pos))
    {
        printf("To use this tool, please input a number between -10 and 10 indicate behind or before you, 0 is not allowed! \r\n");
    }
    else 
    {            
        pos_tool = (player->position + pos) % MAX_POSITION;
        if((MAPS[pos_tool].tool > TOOL_NULL) || _isuser_symbol(MAPS[pos_tool].symbol))
        {
            printf("Can not be used in this place !\r\n");
            *end_round = FALSE;
            return;
        }
        if((player->tool[TOOL_B].num > 0) && (player->tool[TOOL_B].num < 11))
        {
            player->tool[TOOL_B].num--;
            MAPS[pos_tool].tool = TOOL_B;
            printf("Bomb is used successfully !\r\n");
         }
        else
        {
            player->tool[TOOL_B].num = 0;
            printf("Sorry, you don't have available tool(Bomb) now !\r\n");
        }
    }
    *end_round = FALSE;
}

void robot_cmd(PLAYER* player,BOOL* end_round){
    //printf("Function is developing\n");
    char pos = player->position;
    char pos_scan = pos;
    
    if((player->tool[TOOL_R].num > 0) && (player->tool[TOOL_R].num < 11))
    {
        player->tool[TOOL_R].num--;
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
                MAPS[pos_scan].tool = TOOL_NULL;  
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
        player->tool[TOOL_R].num = 0;
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
    if(strcmp(ROLL,arg)==0)
    {
        dice_num = dice_cmd(player,end_round);
    } 
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
        char _args[1024];
        gets(_args);
        
        if(args_parse(_args, player)) break;
    }
}

