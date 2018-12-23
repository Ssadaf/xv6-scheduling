#include "types.h"
#include "user.h"

#define NCHILD 30

int chartoint (char *inp, int *out)
{
  int i;
  *out = 0;
  for (i = 0; ; i++)
     if (inp[i] == 0)
       return 1;
     else if (inp[i] > '9' || inp[i] < '0')
       return 0;
     else
       *out = *out * 10 + (inp[i] - '0');
   return 0;
}

int main (int argc, char* argv[])
{
    if(argc != 3){
        printf(1, "2 argumnets required[queue_num pid]");
    }
    else{
        int num[2];
        if (chartoint(argv[1], num) == 0 || chartoint(argv[2], num + 1) == 0 )
        {
        printf(1, "invalid input. [not all inputs are integers]\n");
        exit();
        }

        changequeue(num[0], num[1]);
    }
	exit();

	return 0;
}
