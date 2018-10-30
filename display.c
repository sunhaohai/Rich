#include "display.h"
#include "rich.h"

extern PLAYER USERS[4];
extern int USERS_NUMBER;
extern MAP MAPS[MAX_POSITION];
extern int game_over;
extern int dice_num;
extern char dot[8][30];

void print_red(char* chars){
    printf(RED_Q);
    printf("%s",chars);
    printf(ORI);
}

void print_green(char* chars){
    printf(GREEN_A);
    printf("%s", chars);
    printf(ORI);
}

void print_blue(char *chars)
{
    printf(BLUE_J);
    printf("%s", chars);
    printf(ORI);
}

void print_yellow(char *chars)
{
    printf(YELLOW_S);
    printf("%s", chars);
    printf(ORI);
}

void print_player(char *chars, USER_NAME name)
{
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

void print_prompt(PLAYER *player)
{
    //print player's name prompt
    if ((*player).name == QIAN)
    {
        char name[] = "Qian>";
        print_player(name, (*player).name);
    }
    else if ((*player).name == ATUBO)
    {
        char name[] = "Atubo>";
        print_player(name, (*player).name);
    }
    else if ((*player).name == JING)
    {
        char name[] = "Jing>";
        print_player(name, (*player).name);
    }
    else if ((*player).name == SUN)
    {
        char name[] = "Sun>";
        print_player(name, (*player).name);
    }
    else
    {
        printf("print_prompt error!");
    }
}

void display(char position, char short_name)
{
    //oneD2twoD(position,short_name);
    printMap(dot[0], position, short_name);
}

void printMap(char line[], char position, char short_name)
{
    system("clear");
    char color[MAX_POSITION] = {0};
    for (int i = 0; i < MAX_POSITION; i++)
    {
        switch (MAPS[i].symbol)
        {
        case 0:
            oneD2twoD(i, 'Q');
            break;
        case 1:
            oneD2twoD(i, 'A');
            break;
        case 2:
            oneD2twoD(i, 'S');
            break;
        case 3:
            oneD2twoD(i, 'J');
            break;
        case 4:
            switch (MAPS[i].owner)
            {
            case 0:
                oneD2twoD(i, '0');
                break;
            case 1:
                oneD2twoD(i, RED0_Q);
                break;
            case 2:
                oneD2twoD(i, GREEN0_A);
                break;
            case 3:
                oneD2twoD(i, BLUE0_S);
                break;
            case 4:
                oneD2twoD(i, YELLOW0_J);
                break;
            default:
                break;
            }
            break;
        case 5:
            switch (MAPS[i].owner)
            {
            case 0:
                oneD2twoD(i, '1');
                break;
            case 1:
                oneD2twoD(i, RED1_Q);
                break;
            case 2:
                oneD2twoD(i, GREEN1_A);
                break;
            case 3:
                oneD2twoD(i, BLUE1_S);
                break;
            case 4:
                oneD2twoD(i, YELLOW1_J);
                break;
            default:
                break;
            }
            break;
        case 6:
            switch (MAPS[i].owner)
            {
            case 0:
                oneD2twoD(i, '2');
                break;
            case 1:
                oneD2twoD(i, RED2_Q);
                break;
            case 2:
                oneD2twoD(i, GREEN2_A);
                break;
            case 3:
                oneD2twoD(i, BLUE2_S);
                break;
            case 4:
                oneD2twoD(i, YELLOW2_J);
                break;
            default:
                break;
            }
            break;
        case 7:
            switch (MAPS[i].owner)
            {
            case 0:
                oneD2twoD(i, '3');
                break;
            case 1:
                oneD2twoD(i, RED3_Q);
                break;
            case 2:
                oneD2twoD(i, GREEN3_A);
                break;
            case 3:
                oneD2twoD(i, BLUE3_S);
                break;
            case 4:
                oneD2twoD(i, YELLOW3_J);
                break;
            default:
                break;
            }
            break;
        case 8:
            oneD2twoD(i, 's');
            break;
        case 9:
            oneD2twoD(i, 'H');
            break;
        case 10:
            oneD2twoD(i, 'T');
            break;
        case 11:
            oneD2twoD(i, 'G');
            break;
        case 12:
            oneD2twoD(i, 'P');
            break;
        case 13:
            oneD2twoD(i, 'M');
            break;
        case 14:
            oneD2twoD(i, '$');
            break;
        case 15:
            oneD2twoD(i, 'L');
            break;
        case 16:
            oneD2twoD(i, 'R');
            break;
        case 17:
            oneD2twoD(i, 'B');
            break;
        default:
            break;
        }
    }
    oneD2twoD(position, short_name);
    for (int i = 0; i < strlen(line); i++)
    {

        if (line[i] == 'Q')
            print_red("Q");
        else if (line[i] == 'A')
            print_green("A");
        else if (line[i] == 'S')
            print_blue("S");
        else if (line[i] == 'J')
            print_yellow("J");
        else if (line[i] == RED0_Q)
            print_red("0");
        else if (line[i] == RED1_Q)
            print_red("1");
        else if (line[i] == RED2_Q)
            print_red("2");
        else if (line[i] == RED3_Q)
            print_red("3");
        else if (line[i] == GREEN0_A)
            print_green("0");
        else if (line[i] == GREEN1_A)
            print_green("1");
        else if (line[i] == GREEN2_A)
            print_green("2");
        else if (line[i] == GREEN3_A)
            print_green("3");
        else if (line[i] == BLUE0_S)
            print_blue("0");
        else if (line[i] == BLUE1_S)
            print_blue("1");
        else if (line[i] == BLUE2_S)
            print_blue("2");
        else if (line[i] == BLUE3_S)
            print_blue("3");
        else if (line[i] == YELLOW0_J)
            print_yellow("0");
        else if (line[i] == YELLOW1_J)
            print_yellow("1");
        else if (line[i] == YELLOW2_J)
            print_yellow("2");
        else if (line[i] == YELLOW3_J)
            print_yellow("3");
        else
            printf("%c", line[i]);
    }
    printf("\n");
}

void oneD2twoD(char position, char short_name)
{
    switch (position)
    {
    case 0:
        dot[0][0] = short_name;
        break;
    case 1:
        dot[0][1] = short_name;
        break;
    case 2:
        dot[0][2] = short_name;
        break;
    case 3:
        dot[0][3] = short_name;
        break;
    case 4:
        dot[0][4] = short_name;
        break;
    case 5:
        dot[0][5] = short_name;
        break;
    case 6:
        dot[0][6] = short_name;
        break;
    case 7:
        dot[0][7] = short_name;
        break;
    case 8:
        dot[0][8] = short_name;
        break;
    case 9:
        dot[0][9] = short_name;
        break;
    case 10:
        dot[0][10] = short_name;
        break;
    case 11:
        dot[0][11] = short_name;
        break;
    case 12:
        dot[0][12] = short_name;
        break;
    case 13:
        dot[0][13] = short_name;
        break;
    case 14:
        dot[0][14] = short_name;
        break;
    case 15:
        dot[0][15] = short_name;
        break;
    case 16:
        dot[0][16] = short_name;
        break;
    case 17:
        dot[0][17] = short_name;
        break;
    case 18:
        dot[0][18] = short_name;
        break;
    case 19:
        dot[0][19] = short_name;
        break;
    case 20:
        dot[0][20] = short_name;
        break;
    case 21:
        dot[0][21] = short_name;
        break;
    case 22:
        dot[0][22] = short_name;
        break;
    case 23:
        dot[0][23] = short_name;
        break;
    case 24:
        dot[0][24] = short_name;
        break;
    case 25:
        dot[0][25] = short_name;
        break;
    case 26:
        dot[0][26] = short_name;
        break;
    case 27:
        dot[0][27] = short_name;
        break;
    case 28:
        dot[0][28] = short_name;
        break;
    case 29:
        dot[1][28] = short_name;
        break;
    case 30:
        dot[2][28] = short_name;
        break;
    case 31:
        dot[3][28] = short_name;
        break;
    case 32:
        dot[4][28] = short_name;
        break;
    case 33:
        dot[5][28] = short_name;
        break;
    case 34:
        dot[6][28] = short_name;
        break;
    case 35:
        dot[7][28] = short_name;
        break;
    case 36:
        dot[7][27] = short_name;
        break;
    case 37:
        dot[7][26] = short_name;
        break;
    case 38:
        dot[7][25] = short_name;
        break;
    case 39:
        dot[7][24] = short_name;
        break;
    case 40:
        dot[7][23] = short_name;
        break;
    case 41:
        dot[7][22] = short_name;
        break;
    case 42:
        dot[7][21] = short_name;
        break;
    case 43:
        dot[7][20] = short_name;
        break;
    case 44:
        dot[7][19] = short_name;
        break;
    case 45:
        dot[7][18] = short_name;
        break;
    case 46:
        dot[7][17] = short_name;
        break;
    case 47:
        dot[7][16] = short_name;
        break;
    case 48:
        dot[7][15] = short_name;
        break;
    case 49:
        dot[7][14] = short_name;
        break;
    case 50:
        dot[7][13] = short_name;
        break;
    case 51:
        dot[7][12] = short_name;
        break;
    case 52:
        dot[7][11] = short_name;
        break;
    case 53:
        dot[7][10] = short_name;
        break;
    case 54:
        dot[7][9] = short_name;
        break;
    case 55:
        dot[7][8] = short_name;
        break;
    case 56:
        dot[7][7] = short_name;
        break;
    case 57:
        dot[7][6] = short_name;
        break;
    case 58:
        dot[7][5] = short_name;
        break;
    case 59:
        dot[7][4] = short_name;
        break;
    case 60:
        dot[7][3] = short_name;
        break;
    case 61:
        dot[7][2] = short_name;
        break;
    case 62:
        dot[7][1] = short_name;
        break;
    case 63:
        dot[7][0] = short_name;
        break;
    case 64:
        dot[6][0] = short_name;
        break;
    case 65:
        dot[5][0] = short_name;
        break;
    case 66:
        dot[4][0] = short_name;
        break;
    case 67:
        dot[3][0] = short_name;
        break;
    case 68:
        dot[2][0] = short_name;
        break;
    case 69:
        dot[1][0] = short_name;
        break;
    default:
        return;
    }
}