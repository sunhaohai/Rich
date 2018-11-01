#include <stdio.h>
#include "rich.h"
#include "init.h"

FILE * test_log;

void test_1_traverse()
{
	if(!(test_log = fopen("./test_r1.log","a")))
	{
		printf("open test_r1.log failed\n");
		goto EXIT;
	}
	fprintf(test_log, "the test result as follows\n\n");

	//init player
	int test_player[1] = {1};
	_init_players(test_player,10000);

	for (int i = 1;i <= 70;i ++)
	{
		dice_num = 1;
		//walk_func

		if (USERS[i].position != i)
			fprintf(test_log, "test_player position wrong in %d\n",i);

	}

	printf("finish one traverse test!result in test_r1.log\n");

	fclose(test_log);

EXIT:
	if(test_log)
		fclose(test_log);
    return;

}

void test_random_traverse()
{
	if(!(test_log = fopen("./test_r1.log","a")))
	{
		printf("open test_r1.log failed\n");
		goto EXIT;
	}
	
	fprintf(test_log, "the random test result as follows\n\n");

	//init player
	int test_player[1] = {1};
	_init_players(test_player,10000);

	int total_step = 0;

	for (int i = 1;i <= 70;i ++)
	{
		dice_num = _get_rand(1,6);
		total_step = (total_step + dice_num) % 70;
		//walk_func

		if (USERS[i].position != total_step)
			fprintf(test_log, "test_player position wrong in %d\n",total_step);

	}

	printf("finish ramdon traverse test!result in test_r1.log\n");


	fclose(test_log);

EXIT:
	if(test_log)
		fclose(test_log);
    return;
}
