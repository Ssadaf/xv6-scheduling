#include "types.h"
#include "user.h"

#define NCHILD 1

int main ()
{
	int pid;

	pid = fork();
	
	if (pid < 0)
	{
		printf(1, "fork failed\n");
		exit();
	}
	else if (pid == 0)
	{
		float j = 0;
        int z = 1;
        for(j = 0; j < 100000000.0; j+=0.5)
            z += (j + 1);
		printf (2, "", z);
		printf(2, "child with pid %d is done\n", getpid());
	}
	else
	{
		wait();
		printf(2, "parent with pid %d is done\n", getpid());
	}

	exit();

	return 0;
}