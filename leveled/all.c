#include "all.h"
#include "extgraph.h"
#include <stdlib.h>

void delay (unsigned short time)
{
	unsigned short randNum;
	
  while (time-- > 0)
     randNum = rand() % time;
}

void refresh (void)
{
	FastCopyScreen(dbuf_hlight, dbuf_alight);
	FastCopyScreen(dbuf_hdark, dbuf_adark);
}