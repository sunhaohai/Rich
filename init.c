#include "init.h"

extern PLAYER USERS[4];
extern int USERS_NUMBER;
extern MAP MAPS[MAX_POSITION];
extern int game_over;
extern int dice_num;
extern char dot[8][30];

int _get_rand(int min, int max)
{
    /*
    get random int number
    @param
    min:min number
    max:max number
    @exp
    input min=1 and max=6
    return number=[1-6]
    */
    srand((unsigned)time(NULL));
    return rand() % (max - min + 1) + min;
}

void _clear()
{
    system("clear");
}

int* _read_number(){
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

int* _read_n_players(int min_player,int max_player,int min_n,int max_n){
    //read n number bewteen min_n-max_n
    while(1){
REIN:        
        setbuf(stdin,NULL);
        int* result = _read_number();
        //for (int j=0;j < USERS_NUMBER;j++)
            //printf("%d\n",result[j] );
        //printf("USERS_NUMBER = %d\n",USERS_NUMBER);
        if(USERS_NUMBER>max_player||USERS_NUMBER<min_player){
            printf("you should input players number between %d-%d,and input again:", min_player, max_player);
            goto REIN;
        }
        for(int i=0;i<USERS_NUMBER;i++){
            if(result[i]<min_n||result[i]>max_n){
                printf("you should input number between %d-%d,and input again:", min_n, max_n);
                goto REIN;
            }
            for(int j=i+1;j<USERS_NUMBER;j++){
                if(result[i]==result[j]){
                    printf("you should input non-repeating number,and input again:");
                    goto REIN;
                }
            }
        }
        return result;
    }    
} 

int *_start_game()
{
    // get users and user number
    _clear();
    printf("1:Qian  2:Atubo, 3:Sun Meimei   4:Jing Beibei\n");
    printf("please input 1-4 to choose roles(at least 2 roles):");
    int *users = _read_n_players(2, 4, 1, 4);
    
    //USERS_NUMBER = sizeof(users) / sizeof(int) - 1;
    //printf("%d\n", USERS_NUMBER);
    return users;
}

char _get_player_symbol(USER_NAME name)
{
    char result;
    if (name == QIAN)
        result = 'Q';
    else if (name == ATUBO)
        result = 'A';
    else if (name == SUN)
        result = 'S';
    else if (name == JING)
        result = 'J';
    else
        result = '0';
    return result;
}

void _init_players(int *users, int init_money)
{
    //USERS = (PLAYER *)malloc(sizeof(PLAYER) * USERS_NUMBER);
    for (int i = 0; i < USERS_NUMBER; i++)
    {
        USERS[i].name = users[i];
        USERS[i].short_name = _get_player_symbol(USERS[i].name); ///
        USERS[i].id = i + 1;
        USERS[i].lucky_god = FALSE;
        USERS[i].money = init_money;
        USERS[i].point = 0;
        USERS[i].position = 0;
        USERS[i].skip_num = 0;
        for (int j = 0; j < TOOL_NUMBER; j++)
        {
            USERS[i].tool[j].num = 0;
            USERS[i].tool[i].type = j + 1;
        }
    }
}

void _init_one_map(MAP* map,int posi, MAP_TYPE type, USER_NAME name, TOOL_TYPE tool, 
                    char mine, PRICE price, SYMBOL symbol)
{
    map[posi].type = type;
    map[posi].owner = name;
    map[posi].price = price;
    map[posi].symbol = symbol;
    map[posi].tool = tool;
    map[posi].mine = mine;
    for(int i=0;i<MAX_USER;i++) map[posi].pre_symbol[i] = symbol;

}

void _init_maps()
{
    _init_one_map(MAPS,0,MAP_START,USER_NULL,TOOL_NULL,0,PRICE_0,SYMBOL_ST);
    for(int i=1;i<=27;i++){
        if(i==14){
            _init_one_map(MAPS,i,MAP_H,USER_NULL,TOOL_NULL,0,PRICE_0,SYMBOL_H);
            continue;
        }
        _init_one_map(MAPS,i,MAP_COM,USER_NULL,TOOL_NULL,0,PRICE_1,SYMBOL_0);
    }
    _init_one_map(MAPS,28,MAP_T,USER_NULL,TOOL_NULL,0,PRICE_0,SYMBOL_T);
    for(int i=29;i<=34;i++){
        _init_one_map(MAPS,i,MAP_COM,USER_NULL,TOOL_NULL,0,PRICE_2,SYMBOL_0);
    }
    _init_one_map(MAPS, 35, MAP_G, USER_NULL, TOOL_NULL, 0, PRICE_0, SYMBOL_G);
    for(int i=36;i<=62;i++){
        if(i==49){
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

void init_game()
{
    int *users = _start_game();
    for (int j=0;j < USERS_NUMBER;j++)
        printf("%d\n",users[j] );


    printf("please input init money(1000-50000):");
    int init_money;

    while(1)
    {   
        setbuf(stdin,NULL);
        scanf("%d", &init_money);
        int c;
        while((c = getchar()) != '\n' && c != EOF);

        if (init_money > 50000 || init_money < 1000)
                printf("please input init money(1000-50000) again:");
        else
            break;
    }
    
    _init_players(users, init_money);
    //printf("init players end!\n");
    _init_maps();
}

void use_tool()
{

    char usetool;   //usetool是所选道具
    //Display_tool(); //显示总道具
    printf(" Do you use props now?\n");
    printf("NO:please input '0'\n");
    printf("roadblock:please input 'block n'\n");
    printf("bomb:please input 'bomb n'\n");
    printf("machine doll:please input 'robot'\n");
    scanf("%c",&usetool);
    printf("Now randomly throw dice from 1~6\n");
    dice_num = rand() % 6 + 1;
    printf("your dice number is:%d\n", dice_num); //生成打印骰>子数

    return;
}
