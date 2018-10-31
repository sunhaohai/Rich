#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rich.h"
#include "init.h"
#include "display.h"
#include "run.h"
#include "test.h"

PLAYER USERS[4];
int USERS_NUMBER;
MAP MAPS[MAX_POSITION];
int game_over;
int dice_num;

char dot[8][30] = {
    "s0000000000000H0000000000000T\n",
    "$                           0\n",
    "$                           0\n",
    "$                           0\n",
    "$                           0\n",
    "$                           0\n",
    "$                           0\n",
    "M0000000000000P0000000000000G"};

FILE * test_log;


void test_random_traverse()
{
	if(!(test_log = fopen("./test.log","a")))
	{
		printf("open test.log failed\n");
		goto EXIT;
    }


	
	fprintf(test_log,"the random test result as follows\n\n");

	 int test_player[1] = {1};
	_init_players(test_player,10000);
	_init_maps();

	int total_step = 0;
	BOOL test_end_round = FALSE;

	for (int i = 1;i <= 70;i ++)
	{
 		dice_num = dice_cmd(USERS,&test_end_round);
 		fprintf(test_log,"dice num is %d\n",dice_num);

 		total_step = (total_step + dice_num)%70;

		if (USERS[0].position != total_step)
			fprintf(test_log,"test_player position wrong in %d\n",total_step);
		else
			fprintf(test_log,"total step is %d\n",total_step);
	}

	fprintf(test_log,"finish ramdon traverse test!\n");
	fclose(test_log);

EXIT:
	if(test_log)
		fclose(test_log);
return;

}

int main()
{
	test_random_traverse();
    printf("finish test \n");
  
    return 0;
}
