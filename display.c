#include "display.h"
#include "rich.h"
#include "init.h"

extern PLAYER USERS[4];
extern int USERS_NUMBER;
extern MAP MAPS[MAX_POSITION];
extern int game_over;
extern int dice_num;
extern char dot[8][30];

void print_red(char* chars){
    //print red chars
    printf(RED_Q);
    printf("%s",chars);
    printf(ORI);
}

void print_green(char* chars){
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
    //print with color depends on name
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
    //print player's name prompt
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

void display(MAP* maps){
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
