#include <stdio.h>
#include <string.h>
#include "function.h"
#include "assist.h"
extern PLAYER USERS[4];
extern int USERS_NUMBER;
extern MAP MAPS[MAX_POSITION];
extern int game_over;

int *_start_game(){
    // 开始游戏,等待玩家选择角色
    _clear();
    printf("1:Qian  2:Atubo, 3:Sun Meimei   4:Jing Beibei\n");
    printf("please input 1-4 to choose roles(at least 2 roles):");
    int *users = _read_n_players(2, 4, 1, 4);
    return users;
}

void _init_players(int *users, int init_money){
    //初始化用户信息   users为用户编号数组  数组index为掷骰子先后顺序
    //init_money 为初始化金钱数
    for (int i = 0; i < USERS_NUMBER; i++){
        USERS[i].name = users[i];
        USERS[i].short_name = _get_player_symbol(USERS[i].name); 
        USERS[i].id = i + 1;
        USERS[i].lucky_god = 0;
        USERS[i].money = init_money;
        USERS[i].point = 0;
        USERS[i].position = 0;
        USERS[i].skip_num = 0;
        for (int j = 0; j < TOOL_NUMBER; j++){
            USERS[i].tool[j].num = 0;
            USERS[i].tool[j].type = j;
        }
        for (int j = 0; j < MAX_POSITION; j++) USERS[i].house[j] = 0;
    }
}

void _init_one_map(MAP *map, int posi, MAP_TYPE type, USER_NAME name, TOOL_TYPE tool,
                   char mine, PRICE price, SYMBOL symbol){
    //初始化地图当中的一个点
    map[posi].type = type;
    map[posi].owner = name;
    map[posi].price = price;
    map[posi].symbol = symbol;
    map[posi].tool = tool;
    map[posi].mine = mine;
    for (int i = 0; i < MAX_USER; i++)
        map[posi].pre_symbol[i] = symbol;
    map[posi].price_all = _get_place_price(price);
}

void _init_maps(){
    //地图初始化
    _init_one_map(MAPS, 0, MAP_START, USER_NULL, TOOL_NULL, 0, PRICE_0, SYMBOL_ST);
    for (int i = 1; i <= 27; i++){
        if (i == 14){
            _init_one_map(MAPS, i, MAP_H, USER_NULL, TOOL_NULL, 0, PRICE_0, SYMBOL_H);
            continue;
        }
        _init_one_map(MAPS, i, MAP_COM, USER_NULL, TOOL_NULL, 0, PRICE_1, SYMBOL_0);
    }
    _init_one_map(MAPS, 28, MAP_T, USER_NULL, TOOL_NULL, 0, PRICE_0, SYMBOL_T);
    for (int i = 29; i <= 34; i++){
        _init_one_map(MAPS, i, MAP_COM, USER_NULL, TOOL_NULL, 0, PRICE_2, SYMBOL_0);
    }
    _init_one_map(MAPS, 35, MAP_G, USER_NULL, TOOL_NULL, 0, PRICE_0, SYMBOL_G);
    for (int i = 36; i <= 62; i++){
        if (i == 49){
            _init_one_map(MAPS, i, MAP_PRS, USER_NULL, TOOL_NULL, 0, PRICE_0, SYMBOL_P);
            continue;
        }
        _init_one_map(MAPS, i, MAP_COM, USER_NULL, TOOL_NULL, 0, PRICE_3, SYMBOL_0);
    }
    _init_one_map(MAPS, 63, MAP_M, USER_NULL, TOOL_NULL, 0, PRICE_0, SYMBOL_M);

    _init_one_map(MAPS, 64, MAP_$, USER_NULL, TOOL_NULL, 60, PRICE_0, SYMBOL_$);
    _init_one_map(MAPS, 65, MAP_$, USER_NULL, TOOL_NULL, 80, PRICE_0, SYMBOL_$);
    _init_one_map(MAPS, 66, MAP_$, USER_NULL, TOOL_NULL, 40, PRICE_0, SYMBOL_$);
    _init_one_map(MAPS, 67, MAP_$, USER_NULL, TOOL_NULL, 100, PRICE_0, SYMBOL_$);
    _init_one_map(MAPS, 68, MAP_$, USER_NULL, TOOL_NULL, 80, PRICE_0, SYMBOL_$);
    _init_one_map(MAPS, 69, MAP_$, USER_NULL, TOOL_NULL, 20, PRICE_0, SYMBOL_$);
    return;
}

void init_game(){
    // 开始游戏,完成游戏的初始化
    int *users = _start_game();
    printf("please input init money(1000-50000):");
    int init_money;
    while (1){
        setbuf(stdin, NULL);
        scanf("%d", &init_money);
        int c;
        while ((c = getchar()) != '\n' && c != EOF) ;
        if (init_money > 50000 || init_money < 1000)
            printf("please input init money(1000-50000) again:");
        else break;
    }
    _init_players(users, init_money);
    _init_maps();
}

void display(MAP* maps){
    //打印地图 
    _clear();
    for(int i=0;i<29;i++)
        _print_map_symbol(maps + i);
    for(int i=29;i<35;i++){
        printf("\n");
        _print_map_symbol(maps + MAX_POSITION - (i-28));
        for(int j=0;j<27;j++) printf(" ");
        _print_map_symbol(maps+i);
    }
    printf("\n");
    for(int i=63;i>=35;i--) _print_map_symbol(maps+i);
    printf("\n");
}

void player_round(PLAYER* player){
    //玩家回合控制总函数
    if((*player).skip_num>0){
        (*player).skip_num--;
        return;
    }
    while(1){
        printf("\n");
        print_prompt(player);
        char _args[10];
        rewind(stdin);
        setbuf(stdin, NULL);
        gets(_args);
        if(args_parse(_args, player)) break;
    }
    if(USERS_NUMBER<2){
        printf("游戏结束!\n");
        getchar();
        game_over = 1;
    }
    if(player->lucky_god) player->lucky_god--;
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

void step_cmd(PLAYER *player, int position, BOOL *end_round){
    players_run_in_the_way(player, position, end_round);
    if (*end_round) return;
    display_run_map(player, player->position + 1);
    players_end_run(player, end_round);
    *end_round = TRUE;
}

void help_cmd() {
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

void query_cmd(PLAYER *player, BOOL *end_round) {
    printf("your total money:%ld\n", player->money);
    printf("your total point:%ld\n", player->point);
    printf("your total house:");                                      //显示房产（等级和位置）
    printf("\nyour total tool>>\n");                            //显示道具（种类和数量）
    printf("Block's number:%d\n", player->tool[TOOL_L].num); //路障数量
    printf("Bomb's number:%d\n", player->tool[TOOL_B].num);  //炸弹数量
    printf("Robot's number:%d\n", player->tool[TOOL_R].num); //路障数量
}

void quit_cmd(PLAYER *player,BOOL* end_round){
    *end_round = 1;
    game_over = 1;
}

void sell_cmd(PLAYER *player, int position, BOOL *end_round) {
    if(player->house[position]==0){
        printf("这不是你都房子,你不能卖!\n");
        return;
    }
    MAPS[position].owner = USER_NULL;
    MAPS[position].type = MAP_COM;
    player->money += MAPS[position].price_all * 2;
    printf("你的房子卖了:%d\n",MAPS[position].price_all * 2);
    *end_round = 1;
}

void dice_cmd(PLAYER* player,BOOL* end_round){
    //玩家执行Roll命令后的一系列情况
    int steps = _get_rand(1, 6);
    players_run_in_the_way(player,steps, end_round);
    if (*end_round) return;
    display_run_map(player,player->position+1);
    players_end_run(player, end_round);
    *end_round = TRUE;
}
void save_cmd()
{
    FILE *fp;
    if((fp = fopen("save.txt","w+"))==NULL){
         printf("The file save.txt can not be opened.\n");
         return;
    } 
    //save all player's info to save.txt
    for(int i = 0;i < USERS_NUMBER; i++){
        fprintf(fp,"%d %d %d %d %d %ld %ld ",
        USERS[i].name, USERS[i].short_name, USERS[i].position, USERS[i].id, USERS[i].skip_num, USERS[i].money, USERS[i].point);
        for(int j = 0;j < MAX_POSITION; j++){
            fprintf(fp, "%d ", USERS[i].house[j]);
        }
        for(int j = 0;j < TOOL_NUMBER; j++){
            fprintf(fp, "%d %d ", USERS[i].tool[j].type, USERS[i].tool[j].num);
        }
        fprintf(fp, "%d \n", USERS[i].lucky_god);
    }
    //save all map's info to save.txt
    for(int i = 0;i < MAX_POSITION;i++){
        fprintf(fp,"type:%d owner:%d tool:%d mine:%d price:%d symbol:%d ",
        MAPS[i].type, MAPS[i].owner, MAPS[i].tool, MAPS[i].mine, MAPS[i].price, MAPS[i].symbol);
        for(int j = 0;j < MAX_USER;j++){
            fprintf(fp,"pre_symbol:%d ",MAPS[i].pre_symbol[j]);
        }
        fprintf(fp,"price_all:%d \n",MAPS[i].price_all);
    }
    fclose(fp);
}

void read_archive(){
    FILE *fp;
    char str[1000];
    char *single;
    int flag = 0, file_row = 0, count = 0;
    if((fp = fopen("save.txt","r"))==NULL){
         printf("The file save.txt can not be opened.\n");
         return;
    }
    for(int i = 0;i < USERS_NUMBER;i++){
        fgets(str,1000,fp);
        // printf("%s",str);
        single = strtok(str, " "); 
        while(single != NULL){
            printf("%s\n",single);
            single = strtok(NULL, " ");
        } 
    }
    // printf("%d\n",single);
    // while (!feof(fp)) { 
    //     fgets(str,1000,fp);  //读取一行
    //     printf("%s\n", str); //输出
    //     single = strtok(str, " "); 
    //     while(single != NULL){
    //         printf("%s\n",single);
    //         single = strtok(NULL, " ");
    //     } 
    // }     
    // printf("%d",USERS_NUMBER);
    fclose(fp);
}