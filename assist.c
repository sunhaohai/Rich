#include "assist.h"
#include "function.h"

extern PLAYER USERS[4];
extern int USERS_NUMBER;
extern MAP MAPS[MAX_POSITION];

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

int* _read_n_players(int min_player, int max_player, int min_n, int max_n){
    //读取[min_n,max_n]个编号为[min_player,max_player]的玩家信息保存到全局变量当中
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

char _get_map_display(SYMBOL symbol){
    //根据symbol获取显示的char字符
    if(symbol==SYMBOL_$) return '$';
    else if(symbol==SYMBOL_0) return '0';
    else if(symbol==SYMBOL_1) return '1';
    else if(symbol==SYMBOL_2) return '2';
    else if(symbol==SYMBOL_3) return '3';
    else if(symbol==SYMBOL_A) return 'A';
    else if(symbol==SYMBOL_B) return 'B';
    else if(symbol==SYMBOL_J) return 'J';
    else if(symbol==SYMBOL_Q) return 'Q';
    else if(symbol==SYMBOL_M) return 'M';
    else if(symbol==SYMBOL_L) return 'L';
    else if(symbol==SYMBOL_S) return 'S';
    else if(symbol==SYMBOL_ST) return 's';
    else if(symbol==SYMBOL_H) return 'H';
    else if(symbol==SYMBOL_T) return 'T';
    else if(symbol==SYMBOL_G) return 'G';
    else if(symbol==SYMBOL_P) return 'P';
    else if(symbol==SYMBOL_R) return 'R';
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
        map->symbol = (map->pre_symbol)[MAX_USER-1];
        return;
    }
    for(int i=0;i<MAX_USER-1;i++){
        (map->pre_symbol)[i] = (map->pre_symbol)[i+1];
    }
}

void prison(PLAYER *player){
    //走到监狱的时候发生的事
    player->skip_num += 2;
    return;
}

void magic_house(PLAYER *player){
    //走到魔法屋的时候发生的事
    printf("Waiting to do\n");
}

void on_mine(char mine, PLAYER *player){
    //走到旷地放生的事
    player->money += mine;
    return;
}

void gift_house(PLAYER *player){
    //走到礼品屋发生的事
    int gift;
    printf("Welcome to gift house, please choose a gift：\n");
    printf("1:money 2:point card 3: lucky god\n");
    while (1){
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

void tool_house(PLAYER *player){
    //走到道具屋发生的事
    printf("Welcome to tool house, please choose a tool:\n");
    char tool;
    while (1){
        if (player->point <= 50){
            printf("you only can buy 2:robot baby \n");
            printf("if you want to leave,please enter F \n");
            scanf("%c", &tool);
        }
        else{
            printf("1:road barrier 2:robot baby 3:bomb\n");
            printf("if you want to leave,please enter F \n");
            scanf("%c", &tool);
        }
        switch (tool){
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

void pay_rent(int owner, int symbol, PLAYER *player){
    //玩家交租
    printf("Waiting to do\n");
}

void buy_upper_house(PLAYER *player, MAP *maps){
    //买房子和升级房子
    return;
}

void display_run_map(PLAYER* player, int fin_position){
    //将玩家放到map上的指定位置,fin_position是想要玩家前往的位置
    _del_symbol(&MAPS[(*player).position], _get_symbol(*player));
    (*player).position = fin_position;
    _add_symbol(&MAPS[(*player).position], _get_symbol(*player));
    display(MAPS);
}

void players_end_run(PLAYER *player, BOOL *end_round){
    //玩家走最后一步的时候发生的事件控制函数
    int pos_temp = (*player).position;
    if (MAPS[pos_temp].owner && MAPS[pos_temp].owner!=player->name)
        pay_rent(MAPS[pos_temp].owner, MAPS[pos_temp].symbol, player);
    else if (MAPS[pos_temp].type == MAP_COM)
        buy_upper_house(player, MAPS);
    else if(MAPS[pos_temp].owner==player->name)
        buy_upper_house(player, MAPS);
    else{
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

void players_run_in_the_way(PLAYER *player, BOOL *end_round){
    //玩家走在路上的时候可能发生的事件
    int steps = _get_rand(1, 6);
    int pos_temp = 0;
    for (int i = 1; i < steps; i++){
        pos_temp = (player->position + 1) % MAX_POSITION;
        switch (MAPS[pos_temp].symbol)
        {
        case SYMBOL_L:
            display_run_map(player, pos_temp);
            *end_round = TRUE;
            return;
        case SYMBOL_B:
            player->skip_num += 2;
            display_run_map(player, 14);
            *end_round = TRUE;
            return;
        default:
            display_run_map(player, pos_temp);
            break;
        }
    }
}