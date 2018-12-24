#include "types.h"
#include "user.h"

#define NCHILD 30

int main ()
{
	int pid;

	pid = fork();
	int i;
	changepriority(2, getpid());
	for (i = 1; i < NCHILD; i++)
		if (pid < 0)
		{
			printf(1, "fork failed\n");
			exit();
		}
		else if (pid > 0)
		{
			if(i == 13)
			{
				changequeue(1, pid);
				changelotterytickets(10, pid);
			}

			if(i == 18)
			{
				changequeue(1, pid);
				changelotterytickets(50, pid);
			}

			if (i == 9)
				changequeue(2, pid);
			if (i == 6)
				changequeue(2, pid);
			if(i == NCHILD-1)
				printproc();
			changepriority(NCHILD - i + 10, getpid());
			pid = fork();
		}
		else
			break;
	
	if (pid < 0)
	{
		printf(1, "fork failed\n");
		exit();
	}
	else if (pid == 0)
	{
		float j = 0;
        int z = 1;
        for(j = 0; j < 10000000.0; j+=0.5)
            z += (j + 1);
		printf (2, "", z);
		printf(2, "child %d is done\n", i);
	}
	else
	{
		for (i = 0; i < NCHILD; i++)
			wait();
		printf(1, "test finished\n");
	}

	exit();

	return 0;
}