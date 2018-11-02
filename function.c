#include <string.h>
#include "function.h"
#include "assist.h"
extern PLAYER USERS[4];
extern int USERS_NUMBER;
extern MAP MAPS[MAX_POSITION];
extern int NOW_ID;

FILE * pdump;
char order_buf[5] = {'\0'};


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
        scanf("%s", _args);
        if(args_parse(_args, player)) break;
    }
    return;
}

void bolck_cmd(PLAYER *plary, int position,BOOL* end_round){
    printf("Function is developing\n");
}

void bomb_cmd(PLAYER *plary, int position,BOOL* end_round){
    printf("Function is developing\n");
}

void robot_cmd(PLAYER* player,BOOL* end_round){
    printf("Function is developing\n");
}

void step_cmd(PLAYER *plary, int position,BOOL* end_round){
    printf("Function is developing\n");
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
    printf("Function is developing\n");
}

void sell_cmd(PLAYER *player, int position, BOOL *end_round) {
    printf("Function is developing\n");
}

void dice_cmd(PLAYER* player,BOOL* end_round){
    //玩家执行Roll命令后的一系列情况
    players_run_in_the_way(player, end_round);
    if (*end_round) return;
    display_run_map(player,player->position+1);
    players_end_run(player, end_round);
    *end_round = TRUE;
}

void dump()
{
    if (!(pdump = fopen("./dump.txt","a")))
    {
        printf("open dump.txt failed\ndump failed!\n");
        goto EXIT;
    }

    dump_user();

    dump_map();
   
    dump_money();

    dump_point();

    dump_tool_user();

    dump_tool_map();

    dump_loc();

    dump_next();

    printf("dump finished\n");

    fclose(pdump);

EXIT:
    if(pdump)
        fclose(pdump);

    return;
}

void dump_user()
{
    char buf[5] = {'\0'};
    char temp[5] = {'\0'};

    for (int i = 0; i < USERS_NUMBER; ++i)
        strcat(buf,&USERS[i].short_name);

    for (int i = 0; i < USERS_NUMBER; ++i)
    {
        if (buf[i] == 'A')
            temp[0] = 'A';
        if (buf[i] == 'Q')
            temp[1] = 'Q';
        if (buf[i] == 'S')
            temp[2] = 'S';
        if (buf[i] == 'J')
            temp[3] = 'J';
    }

    int j=0;
    for (int i = 0; i < 4; ++i)
    {
        if (temp[i] != '\0')
            order_buf[j++]=temp[i];
    }

    fprintf(pdump,"user %s\n",order_buf);

    return;
}

void dump_map()
{   
    for (int i = 0; i < MAX_POSITION; ++i)
    {
        if (MAPS[i].owner != USER_NULL)
            fprintf(pdump,"map[%d] %c %d\n",i,_get_player_symbol(MAPS[i].owner),MAPS[i].symbol);      
    }

    return;
}

void dump_money()
{
    for (int i = 0; i < USERS_NUMBER; ++i)
        fprintf(pdump,"fund %c %d\n",order_buf[i],_get_money_by_symbol(order_buf[i]));
    return;
}

void dump_point()
{
    for (int i = 0; i < USERS_NUMBER; ++i)
        fprintf(pdump,"credit %c %d\n",order_buf[i],_get_point_by_symbol(order_buf[i]));
    return;
}

void dump_tool_user()
{
    for (int i = 0; i < USERS_NUMBER; ++i)
    {
        for (int j = 0; j < USERS_NUMBER; ++j)
        {
            if (USERS[j].short_name == order_buf[i])
            {
                fprintf(pdump,"gift %c bomb %d\n",order_buf[i],USERS[j].tool[1].num);
                fprintf(pdump,"gift %c barrier %d\n",order_buf[i],USERS[j].tool[0].num);
                fprintf(pdump,"gift %c robot %d\n",order_buf[i],USERS[j].tool[2].num);
                fprintf(pdump,"gift %c god %d\n",order_buf[i],USERS[j].lucky_god);
            }
        }   
    }
    return;
}


void dump_tool_map()
{
    for (int i = 0; i < MAX_POSITION; ++i)
    {
        if (MAPS[i].tool == 1)
            fprintf(pdump,"bomb in %d\n",i);      
    }

    for (int i = 0; i < MAX_POSITION; ++i)
    {
        if (MAPS[i].tool == 0)
            fprintf(pdump,"barrier in %d\n",i);      
    }
    return;
}

void dump_loc()
{
    for (int i = 0; i < USERS_NUMBER; ++i)
    {
        for (int j = 0; j < USERS_NUMBER; ++j)
        {
            if (USERS[j].short_name == order_buf[i])
            {
                if (USERS[j].skip_num == 0)
                    fprintf(pdump,"userloc %c %d\n",order_buf[i],USERS[j].position);
                else
                    fprintf(pdump,"userloc %c %d %d\n",order_buf[i],USERS[j].position,USERS[j].skip_num);
            }

        }
    }
    return;
    
}

void dump_next()
{
    int next_id;

    for (int i = 0; i < USERS_NUMBER; ++i)
    {
        if (USERS[i].id == NOW_ID)
        {           
            if ( NOW_ID < USERS_NUMBER )
                next_id = NOW_ID + 1 + (USERS[i+1].skip_num != 0);
                
            else if ( NOW_ID == USERS_NUMBER)
                next_id = NOW_ID + 1 + (USERS[0].skip_num != 0);
        }
    }

    if (next_id == USERS_NUMBER)
        fprintf(pdump,"nextuser %c\n",USERS[next_id-1].short_name);
    else
        fprintf(pdump,"nextuser %c\n",USERS[next_id%USERS_NUMBER-1].short_name);
    return;
}

