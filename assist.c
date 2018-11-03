#include <ctype.h>

#include "assist.h"
#include "function.h"

extern PLAYER USERS[4];
extern int USERS_NUMBER;
extern MAP MAPS[MAX_POSITION];
extern int game_over;

int _get_rand(int min, int max){
    //生成大小在[min,max]当中的随机数
    return rand() % (max - min + 1) + min;
}

void _clear(){
    //清屏函数
    system("clear");
}

int* _read_number(){
    //从屏幕读取罗干数字输入,以换行符结束
    //bug待处理:输入包涵char的时候USERS_NUMBER会不对
    int *result = (int *)malloc(sizeof(int));
    result[0] = -1;
    int now_n;
    int i = 0;
    char c;
    while (1){
        scanf("%d", &now_n);
        result[i] = now_n;
        i++;
        result = (int *)realloc(result, ((i + 1) * sizeof(int)));
        if ((c = getchar()) == '\n'){
            USERS_NUMBER = i;
            break;
        }
    }
    return result;
}

char* _str_upper(char* str)
{
    char* s = str;
    int i;
//    printf("before toupper() : %s\n", s);
    for(i = 0; i < strlen(s); i++)
    s[i] = toupper(s[i]);
//    printf("after toupper() : %s\n", s);
    return s;
}

PLAYER* _find_player(USER_NAME name)
{
    char i = 0;
    for(i=0;i < USERS_NUMBER;i++)
    if(USERS[i].name == name) {
        return &USERS[i];
    }
}

int* _read_n_players(int min_player, int max_player, int min_n, int max_n){
    //读取[min_n,max_n]个编号为[min_player,max_player]的玩家信息保存到全局变量当中
    //TODO: input check
    while (1){
    REIN:
        setbuf(stdin, NULL);
        int *result = _read_number();
        if (USERS_NUMBER > max_player || USERS_NUMBER < min_player){
            printf("you should input players number between %d-%d,and input again:", min_player, max_player);
            goto REIN;
        }
        for (int i = 0; i < USERS_NUMBER; i++){
            if (result[i] < min_n || result[i] > max_n){
                printf("you should input number between %d-%d,and input again:", min_n, max_n);
                goto REIN;
            }
            for (int j = i + 1; j < USERS_NUMBER; j++){
                if (result[i] == result[j]){
                    printf("you should input non-repeating number,and input again:");
                    goto REIN;
                }
            }
        }
        return result;
    }
}

char _get_player_symbol(USER_NAME name){
    //获取用户的字符symbol
    char result;
    if (name == QIAN) result = 'Q';
    else if (name == ATUBO) result = 'A';
    else if (name == SUN) result = 'S';
    else if (name == JING) result = 'J';
    else result = '0';
    return result;
}

int _get_place_price(PRICE place){
    //获取地段的价格
    if (place == PRICE_1) return 200 ;
    else if (place == PRICE_2) return 500 ;
    else if (place == PRICE_3) return 300 ;
    else return 0;
}

/////
/////
/////下面是和显示相关的函数
void print_red(char *chars){
    //print red chars
    printf(RED_Q);
    printf("%s", chars);
    printf(ORI);
}

void print_green(char *chars){
    //print green chars
    printf(GREEN_A);
    printf("%s", chars);
    printf(ORI);
}

void print_blue(char *chars){
    //print blue chars
    printf(BLUE_J);
    printf("%s", chars);
    printf(ORI);
}

void print_yellow(char *chars){
    //print yellow chars
    printf(YELLOW_S);
    printf("%s", chars);
    printf(ORI);
}

void print_player(char *chars, USER_NAME name){
    //根据用户的姓名打印对应颜色的字符
    if (name == QIAN)
        print_red(chars);
    else if (name == ATUBO)
        print_green(chars);
    else if (name == JING)
        print_blue(chars);
    else if (name == SUN)
        print_yellow(chars);
    else
        printf("%s", chars);
}

void print_prompt(PLAYER *player){
    //打印用户提示符
    if ((*player).name == QIAN){
        char name[] = "Qian>";
        print_player(name, (*player).name);
    }
    else if ((*player).name == ATUBO){
        char name[] = "Atubo>";
        print_player(name, (*player).name);
    }
    else if ((*player).name == JING){
        char name[] = "Jing>";
        print_player(name, (*player).name);
    }
    else if ((*player).name == SUN){
        char name[] = "Sun>";
        print_player(name, (*player).name);
    }
    else{
        printf("print_prompt error!");
    }
}

void print_player_name(PLAYER *player){
    //打印player name
    if ((*player).name == QIAN){
        char name[] = "Qian";
        print_player(name, (*player).name);
    }
    else if ((*player).name == ATUBO){
        char name[] = "Atubo";
        print_player(name, (*player).name);
    }
    else if ((*player).name == JING){
        char name[] = "Jing";
        print_player(name, (*player).name);
    }
    else if ((*player).name == SUN){
        char name[] = "Sun";
        print_player(name, (*player).name);
    }
    else{
        printf("print_player_name error!");
    }
}

char _get_map_display(SYMBOL symbol){
    //根据symbol获取显示的char字符
    if(symbol==SYMBOL_$) return '$';
    else if(symbol==SYMBOL_0)  return  '0';
    else if(symbol==SYMBOL_1)  return  '1';
    else if(symbol==SYMBOL_2)  return  '2';
    else if(symbol==SYMBOL_3)  return  '3';
    else if(symbol==SYMBOL_A)  return  'A';
    else if(symbol==SYMBOL_B)  return  '@';
    else if(symbol==SYMBOL_J)  return  'J';
    else if(symbol==SYMBOL_Q)  return  'Q';
    else if(symbol==SYMBOL_M)  return  'M';
    else if(symbol==SYMBOL_L)  return  '#';
    else if(symbol==SYMBOL_S)  return  'S';
    else if(symbol==SYMBOL_ST) return  's';
    else if(symbol==SYMBOL_H)  return  'H';
    else if(symbol==SYMBOL_T)  return  'T';
    else if(symbol==SYMBOL_G)  return  'G';
    else if(symbol==SYMBOL_P)  return  'P';
    else if(symbol==SYMBOL_R)  return  'R';
    else return '0';
}

void _print_map_symbol(MAP* map){
    //打印地图的一个字符
    char p = _get_map_display(map->symbol);
    if(map->tool==TOOL_B) p = _get_map_display(SYMBOL_B);
    else if(map->tool==TOOL_L) p = _get_map_display(SYMBOL_L);
    else if(map->tool==TOOL_R) p = _get_map_display(SYMBOL_R);
    char pt[2];
    pt[0] = p;
    if(p=='Q') print_player(pt,QIAN);
    else if(p=='J') print_player(pt,JING);
    else if(p=='A') print_player(pt,ATUBO);
    else if(p=='S') print_player(pt,SUN);
    else print_player(pt,map->owner);
}

BOOL args_parse(char* arg, PLAYER* player){
    //命令行解析函数
    BOOL end_round=FALSE; //end this round or not
    int args_field_n = _args_num_parse(arg);
    if(args_field_n==1) _args_parse_one(_str_upper(arg),player,&end_round);
    else if(args_field_n==2){
        char* t=strtok(arg," ");
        char* f1=t;
        t=strtok(NULL," ");
        char* f2=t;
        _args_parse_two(_str_upper(f1),player,atoi(f2),&end_round);
    }
    else help_cmd();
    return end_round;
}

void _args_parse_one(char* arg, PLAYER* player,BOOL* end_round){
    //deal cmd without param
    if(strcmp("ROLL",arg)==0) dice_cmd(player,end_round);
    else if(strcmp("ROBOT",arg)==0) robot_cmd(player,end_round);
    else if(strcmp("QUERY",arg)==0) query_cmd(player,end_round);
    else if(strcmp("QUIT",arg)==0) quit_cmd(player,end_round);
    else help_cmd();
}

void _args_parse_two(char *arg, PLAYER *player, int position,BOOL* end_round){
    //deal cmd with param
    if(strcmp("SELL",arg)==0) sell_cmd(player,position,end_round);
    else if(strcmp("BLOCK",arg)==0) bolck_cmd(player,position,end_round);
    else if(strcmp("BOMB",arg)==0) bomb_cmd(player,position,end_round);
    else if(strcmp("STEP",arg)==0) step_cmd(player,position,end_round);
    else help_cmd();
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

SYMBOL _get_symbol(PLAYER player){
    //获取玩家的symbol
    if(player.name==QIAN) return SYMBOL_Q;
    else if(player.name==JING) return SYMBOL_J;
    else if(player.name==SUN) return SYMBOL_S;
    else if(player.name==ATUBO) return  SYMBOL_A;
    else return SYMBOL_0;
}

BOOL _isuser_symbol(SYMBOL sym){
    //判断这个符号是否是玩家的符合
    if( (sym==SYMBOL_J)||(sym==SYMBOL_S)||(sym==SYMBOL_A)||(sym==SYMBOL_Q) )
    return TRUE;
    return FALSE;
}

void _add_symbol(MAP* map,SYMBOL adds){
    //当玩家走到当前地点的时候将前面覆盖的符号保存
    for(int i=0;i<MAX_USER-1;i++){
        if(!_isuser_symbol((map->pre_symbol)[i])){
            (map->pre_symbol)[i] = map->symbol;
            break;
        }
    }
    map->symbol=adds;
}

void _del_symbol(MAP* map,SYMBOL dels){
    //玩家离开时显示 被覆盖的符号
    if(map->symbol==dels) {
        for(int i = MAX_USER-1;i>0;i--){
            if( (map->pre_symbol)[i] != (map->pre_symbol)[i-1] ){
                map->symbol = (map->pre_symbol)[i - 1];
                (map->pre_symbol)[i - 1] = (map->pre_symbol)[i];
                return;
            }
        }
        map->symbol = (map->pre_symbol)[0];
        return;
    }
    for(int i=0;i<MAX_USER-1;i++){
        if(map->pre_symbol[i] == dels){
            for(int j=i;j<MAX_USER-1;j++)
                map->pre_symbol[j] = map->pre_symbol[j+1]; 
        }
    }
}

void prison(PLAYER *player){
    //走到监狱的时候发生的事  step 49
    printf("You are in prison and will stay here for 2 days!\n");
    player->skip_num = SKIP_P;
    return;
}

void magic_house(PLAYER *player){
    //走到魔法屋的时候发生的事
    printf("你来到了魔法屋 Waiting to do\n");
}

void on_mine(char mine, PLAYER *player){
    //走到旷地放生的事 step 64~69
    player->point += mine;
    printf("You got %hhd point in mine!\n""Your point: %ld -> %ld\n",
            mine, ((player -> point)-mine), (player -> point));
    return;
}

void gift_house(PLAYER *player){
    //走到礼品屋发生的事 step 35
    printf("Welcome to gift house, you can choose a gift you want here：\n");
    printf("(Choose a gift by input its number correctly)\n");
    printf("->1: money (Increase 2000 instantly) \n"
           "->2: point card (Increase 200 instantly) \n"
           "->3: lucky god (Free to pass for 5 days) \n");
    while (1){
        char chose, clear;
        printf("(1/2/3): ");
        chose = getchar();
        if(chose != '\n')while ((clear = getchar()) != EOF && clear != '\n');
        switch (chose){
        case '1':
            player -> money += 2000;
            printf("Your money increased 2000!\n"
                   "You money: %ld -> %ld\n", ((player -> money) - 2000), (player -> money));
            return;
        case '2':
            (player -> point) += 200;
                printf("Your point increased 200!\n"
                       "You point: %ld -> %ld\n", ((player -> point) - 200), (player -> point));
            return;
        case '3':
            (player -> lucky_god) += 5;
            printf("You got a lucky god!\n");
            return;
        default:
            printf("***** please choose again *****\n");
            break;
        }
    }
}

void tool_house(PLAYER *player){
    //走到道具屋发生的事 step 35 -> step 63
    char chose, clear;
    printf("Welcome to tool house, you can spend point buy a tool you want here:\n");
    printf("(Choose a tool by input its number correctly)\n");
    while (1){
        printf("Your point: %ld\n", (player -> point));
        printf("->1: Block(50)  ->2: Robot(30)  ->3: Bomb(50)\n");
        if ((player->point) < 50) printf("you only can buy ->2: Robot(30) \n");
        printf("if you want to leave, please enter F. \n""(1/2/3/F): ");
        chose = getchar();
        if(chose != '\n')while ((clear = getchar()) != EOF && clear != '\n');
        switch (chose){
        case '1':
            if((player -> point) < 50){
                printf("Sorry, you don't have enough point.\n");
                break;
            }
            else{
                player->tool[TOOL_L].num++;
                player->point -= 50;
                printf("You got a BLOCK, your point: %ld\n", player -> point);
            }
            return;
        case '2':
            player->tool[TOOL_R].num++;
            player->point -= 30;
            printf("You got a ROBOT, your point: %ld\n", player -> point);
            return;
        case '3':
            if((player -> point) < 50){
                printf("Sorry, you don't have enough point.\n");
                break;
            }
            else{
                player->tool[TOOL_B].num++;
                player->point -= 50;
                printf("You got a BOMB, your point: %ld\n", player -> point);
            }
            return;
        case 'F':
        case 'f':
            printf("You bought nothing and left Tool Shop!\n");
            return;
        default:
            printf("***** please choose again ~~~ *****\n");
            break;
        }
    }
}

void _usercmp(PLAYER* user1, PLAYER* user2){
    //PLAYER 结构赋值
    user1->name = user2->name;
    user1->short_name = user2->short_name;
    user1->position = user2->position;
    user1->id = user2->id;
    user1->skip_num = user2->skip_num;
    user1->money = user2->money;
    user1->point = user2->point;
    for(int i=0;i<MAX_POSITION;i++)
        user1->house[i] = user2->house[i];
    for(int i=0;i<TOOL_NUMBER;i++){
        user1->tool[i].type = user2->tool[i].type;
        user1->tool[i].num = user2->tool[i].num;
    }
    user1->lucky_god = user2->lucky_god;
}

void rm_user(PLAYER* users,USER_NAME name, int* user_size){
    //玩家破产,删除玩家, cover the dead player
    for(int i=0;i<MAX_POSITION;i++){
        if(MAPS[i].owner==name){
            MAPS[i].type = MAP_COM;
            MAPS[i].owner = USER_NULL;
        }
    }
    for(int i=0;i<*user_size;i++){
        if(users[i].name==name){
            _del_symbol(&MAPS[users[i].position],_get_symbol(users[i]));
            for(int j=i;j<*user_size-1;j++){
                _usercmp(users+j,users+j+1);
            }
        }
    }
    *user_size -= 1;
}

void pay_rent(PLAYER *player, MAP *maps){
    //玩家交租
    PLAYER* owner;
    char rent = 0;
    if(player->lucky_god)
    {
        (player->lucky_god) --;
        printf("Lucky god pay the rent for you, %d more times rent can be pay!\n", (player->lucky_god));
        printf("Your money : %ld\n", (player -> money));
        return;
    }
    owner = _find_player(maps[player->position].owner);
    printf("You arrived at ");
    print_player_name(owner);
    printf("'s place\n");
    rent = ((maps[player->position]).price_all ) / 2;
    if(owner -> skip_num != SKIP_NULL)
    {
        printf("You didn't pay the rent and nobody knew.\n");
        return;
    }
    if( (player->money) < rent ){
        owner->money += player->money;
        rm_user(USERS,player->name,&USERS_NUMBER);
        printf("Sorry, you're bankrupt!!\n");
        print_player_name(owner);
        printf("'s money : %ld -> %ld\n",  (owner->money - rent), owner->money);
        return;
    }
    player->money -= rent;
    owner->money += rent;
    printf("You have to pay the rent %d.\n", rent);
    printf("Your money : %ld -> %ld\n", (player->money + rent), player->money);
    print_player_name(owner);
    printf("'s money : %ld -> %ld\n",  (owner->money - rent), owner->money);
    return ;
}

void buy_upper_house(PLAYER *player, MAP *maps){
    //买房子和升级房子
//    print_player_name(player);
    //买房子
    if(maps[player->position].type == MAP_COM){
        printf("This house price: %d\n",maps[player->position].price_all);
        if (player->money >= maps[player->position].price_all){
            while(1){
                char chose, clear;
                printf("Your Money: %ld\n",player->money);
                printf("You can buy this house(Y/N):");
                chose = getchar();
                if(chose != '\n')while ((clear = getchar()) != EOF && clear != '\n');
                if (chose == 'N' || chose == 'n'){
                    printf("You didn't buy it.\n");
                    return;
                }
                else if (chose == 'Y' || chose == 'y' || chose == '\n'){
                    player->house[player->position] = 1;
                    maps[player->position].owner = player->name;
                    maps[player->position].type = MAP_PRI;
                    player->money -= maps[player->position].price_all;
                    printf("After you buy the house you have money:%ld\n",player->money);
                    return;
                }
                printf("***** Invalid input, choose again *****\n");
            }
        }
        else printf("You money is not enough!\n");
    }
    else{
        SYMBOL tmp = maps[player->position].pre_symbol[MAX_USER - 1];
        if(tmp == SYMBOL_3) {
            printf("This house belongs to you and it's highest level.\n");
            return;
        }
        printf("\n");
        printf("To upper you house cost %d\n",_get_place_price(maps[player->position].price));
        if (player->money >= _get_place_price(maps[player->position].price)){
            while(1){
                char chose, clear;
                printf("Your Money: %ld\n",player->money);
                printf("You can upper this house(Y/N):");
                chose = getchar();
                if(chose != '\n')while ((clear = getchar()) != EOF && clear != '\n');
                if (chose == 'N' || chose == 'n')
                {
                    printf("You didn't upper it.\n");
                    return;
                }
                else if (chose == 'Y' || chose == 'y' || chose == '\n'){
                    maps[player->position].price_all += _get_place_price(maps[player->position].price);
                    player->money -= _get_place_price(maps[player->position].price);
                    (player -> house[player->position]) ++;
                    //更新标志
                    for (int i = 0; i < MAX_USER; i++){
                        if (maps[player->position].pre_symbol[i] == tmp)
                            maps[player->position].pre_symbol[i] += 1;
                        if (maps[player->position].symbol == tmp)
                            maps[player->position].symbol += 1;
                    }
                    printf("Upper successfully! Your money: %ld\n", player->money);
                    return;
                }
                printf("***** Invalid input, choose again *****\n");
            }
        }
    }
    return;
}

void display_run_map(PLAYER* player, int fin_position){
    //将玩家放到map上的指定位置,fin_position是想要玩家前往的位置
    _del_symbol(&MAPS[(*player).position], _get_symbol(*player));
    (*player).position = fin_position % MAX_POSITION;
    _add_symbol(&MAPS[(*player).position], _get_symbol(*player));
    display(MAPS);
}

void players_end_run(PLAYER *player,BOOL *end_round){
    //玩家走最后一步的时候发生的事件控制函数
    //TODO: adjust order in round
    int pos_temp = (*player).position;
    if (MAPS[pos_temp].owner && MAPS[pos_temp].owner!=player->name)
        pay_rent(player,MAPS);
    else if (MAPS[pos_temp].type == MAP_COM || MAPS[pos_temp].owner == player->name)
        buy_upper_house(player, MAPS);
    else{
        switch (MAPS[pos_temp].type)
        {
        case MAP_T: {
            char tool_num = player->tool[TOOL_L].num + player->tool[TOOL_B].num + player->tool[TOOL_R].num;
            if (player->point < 30) {
                printf("You are too pool to buy any tool.\n");
            } else if (tool_num >= 10) {
                printf("You already have a maximum limit number of tools.\n");
            } else {
                tool_house(player);
            }
            break;
        }
        case MAP_G:
            gift_house(player);
            break;
        case MAP_M:
            magic_house(player);
            break;
        case MAP_PRS:
            prison(player);
            break;
        case MAP_$:
            on_mine(MAPS[pos_temp].mine, player);
            break;
        default:
            return;
        }
    }
    *end_round = TRUE;
}

void players_run_in_the_way(PLAYER *player, int steps,BOOL *end_round){
    //玩家走在路上的时候可能发生的事件
    char pos_start = player -> position;
    int pos_temp = 0;
    for (int i = 1; i < steps; i++){
        pos_temp = (player->position + 1) % MAX_POSITION;
        switch (MAPS[pos_temp].tool)
        {
        case TOOL_L:
            MAPS[pos_temp].tool = TOOL_NULL;
            display_run_map(player, pos_temp);
            print_player_name(player);
            printf(":\nYou meet a BLOCK on the way! You walked %d steps forward.\n", (pos_temp - pos_start));
            *end_round = TRUE;
            return;
        case TOOL_B:
            MAPS[pos_temp].tool = TOOL_NULL;
            player->skip_num = SKIP_H;
            display_run_map(player, 14);
            print_player_name(player);
            printf(":\nYou meet a BOMB on the way! You were injured and sent to the hospital in time.\n"
                   "You have to rest in the hospital for 3 days.\n");
            *end_round = TRUE;
            return;
        default:
            display_run_map(player, pos_temp);
            break;
        }
    }
}