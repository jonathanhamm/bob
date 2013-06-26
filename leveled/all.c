#include "all.h"
#include <stdlib.h>

void delay (unsigned short time)
{
	unsigned short randNum;
	
  while (time-- > 0)
     randNum = rand() % time;
}
