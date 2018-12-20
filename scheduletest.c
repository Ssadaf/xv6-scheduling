#include "types.h"
#include "user.h"

#define NCHILD 10

int main ()
{
	int pid;

	pid = fork();
	int i;
	for (i = 1; i < NCHILD; i++)
		if (pid < 0)
		{
			printf(1, "fork failed\n");
			exit();
		}
		else if (pid > 0){
			pid = fork();
        }
	
	if (pid < 0)
	{
		printf(1, "fork failed\n");
		exit();
	}
	else if (pid == 0)
	{
        int i, j;
        int z = 1;
        for(i = 0; i < 8000; i++)
            for(j = 0; j < 8000; j++)
                z *= i * j;
	}
	else
	{
		for (i = 0; i < NCHILD; i++)
			wait();
		printf(1, "priority queue test finished\n");
	}

	exit();

	return 0;
}
