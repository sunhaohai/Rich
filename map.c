#include<stdio.h>
#include<string.h>
/* map */
char dot[8][30]= {"s0000000000000H0000000000000T\n",
                    "$                           0\n",
                    "$                           0\n",
                    "$                           0\n",
                    "$                           0\n",
                    "$                           0\n",
                    "$                           0\n",
                    "M0000000000000P0000000000000G"};
/* change the value of position with short_name */
void oneD2twoD(char position,char short_name);
/* print map ,param [in] = map */
void printMap(char line[]);
void main()
{   
    printf("original map:\n");  
    printMap(dot[0]);
    printf("\n after A is added: \n");
    oneD2twoD(60,'A');
    //printMap(dot[0]);
    return;
}

void printMap(char line[]){
    system("clear");
    for(int i = 0;i < strlen(line);i++){
        if(line[i] == 'Q'){
            printf("\033[31mQ\033[0m");
        }else if(line[i]=='A') {
            printf("\033[32mA\033[0m");            
        }else if(line[i]=='S') {
            printf("\033[34mS\033[0m");            
        }else if(line[i]=='J') {
            printf("\033[33mJ\033[0m");            
        }
        else{
            printf("%c",line[i]);
        }
    }
}

void oneD2twoD(char position,char short_name){ 
    switch(position){
        case 0: dot[0][0] = short_name; break;
        case 1: dot[0][1] = short_name; break;
        case 2: dot[0][2] = short_name; break;
        case 3: dot[0][3] = short_name; break;
        case 4: dot[0][4] = short_name; break;
        case 5: dot[0][5] = short_name; break;
        case 6: dot[0][6] = short_name; break;
        case 7: dot[0][7] = short_name; break;
        case 8: dot[0][8] = short_name; break;
        case 9: dot[0][9] = short_name; break;
        case 10: dot[0][10] = short_name; break;
        case 11: dot[0][11] = short_name; break;
        case 12: dot[0][12] = short_name; break;
        case 13: dot[0][13] = short_name; break;
        case 14: dot[0][14] = short_name; break;
        case 15: dot[0][15] = short_name; break;
        case 16: dot[0][16] = short_name; break;
        case 17: dot[0][17] = short_name; break;
        case 18: dot[0][18] = short_name; break;
        case 19: dot[0][19] = short_name; break;
        case 20: dot[0][20] = short_name; break;
        case 21: dot[0][21] = short_name; break;
        case 22: dot[0][22] = short_name; break;
        case 23: dot[0][23] = short_name; break;
        case 24: dot[0][24] = short_name; break;
        case 25: dot[0][25] = short_name; break;
        case 26: dot[0][26] = short_name; break;
        case 27: dot[0][27] = short_name; break;
        case 28: dot[0][28] = short_name; break;
        case 29: dot[1][28] = short_name; break;
        case 30: dot[2][28] = short_name; break;
        case 31: dot[3][28] = short_name; break;
        case 32: dot[4][28] = short_name; break;
        case 33: dot[5][28] = short_name; break;
        case 34: dot[6][28] = short_name; break;
        case 35: dot[7][28] = short_name; break;
        case 36: dot[7][27] = short_name; break;
        case 37: dot[7][26] = short_name; break;
        case 38: dot[7][25] = short_name; break;
        case 39: dot[7][24] = short_name; break;
        case 40: dot[7][23] = short_name; break;
        case 41: dot[7][22] = short_name; break;
        case 42: dot[7][21] = short_name; break;
        case 43: dot[7][20] = short_name; break;
        case 44: dot[7][19] = short_name; break;
        case 45: dot[7][18] = short_name; break;
        case 46: dot[7][17] = short_name; break;
        case 47: dot[7][16] = short_name; break;
        case 48: dot[7][15] = short_name; break;
        case 49: dot[7][14] = short_name; break;
        case 50: dot[7][13] = short_name; break;
        case 51: dot[7][12] = short_name; break;
        case 52: dot[7][11] = short_name; break;
        case 53: dot[7][10] = short_name; break;
        case 54: dot[7][9] = short_name; break;
        case 55: dot[7][8] = short_name; break;
        case 56: dot[7][7] = short_name; break;
        case 57: dot[7][6] = short_name; break;
        case 58: dot[7][5] = short_name; break;
        case 59: dot[7][4] = short_name; break;
        case 60: dot[7][3] = short_name; break;
        case 61: dot[7][2] = short_name; break;
        case 62: dot[7][1] = short_name; break;
        case 63: dot[7][0] = short_name; break;
        case 64: dot[6][0] = short_name; break;
        case 65: dot[5][0] = short_name; break;
        case 66: dot[4][0] = short_name; break;
        case 67: dot[3][0] = short_name; break;
        case 68: dot[2][0] = short_name; break;
        case 69: dot[1][0] = short_name; break;
        default: return;
    } 
}