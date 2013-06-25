
#include <tigcclib.h>

static void eloop (void);

void _main(void)
{
	eloop();
}

void eloop (void)
{
	while (_keytest(RR_ESC)) {
		
	}
}