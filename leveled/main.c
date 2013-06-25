#include "TileMap.h"
#include "extgraph.h"
#include "sprites.h"
#include "level.h"
#include <tigcclib.h>

#define INIT_MAPSIZE ((LCD_WIDTH / 8) * (LCD_HEIGHT / 8))

static INT_HANDLER ai1,ai5;
static char fontbk;
static char block[(unsigned long)GRAYDBUFFER_SIZE+2*GRAY_BIG_VSCREEN_SIZE+BIG_VSCREEN_SIZE+480];
static void eloop (void);
static inline void refresh() __attribute__((always_inline));

void _main(void)
{
	clrscr();
	
 	fontbk = FontGetSys();
	FontSetSys(F_4x6);
	
	ai1=GetIntVec(AUTO_INT_1);
  ai5=GetIntVec(AUTO_INT_5);
  SetIntVec(AUTO_INT_1,DUMMY_HANDLER);
  SetIntVec(AUTO_INT_5,DUMMY_HANDLER);
  
	if (!GrayOn())
		return;
	GrayDBufInit (block);
	
	eloop();
	
	GrayOff();
	
	SetIntVec(AUTO_INT_1,ai1);
  SetIntVec(AUTO_INT_5,ai5);
  
  FontSetSys(fontbk);
}

void eloop (void)
{
	level_s level;
	
	level.map = calloc(1, INIT_MAPSIZE);
	if (!level.map)
		return;
	while (!_keytest(RR_ESC)) {
		if (_keytest(RR_LEFT)) {
		}
		else if (_keytest(RR_RIGHT)) {
			
		}
		else if (_keytest(RR_UP)) {
			
		}
		else if (_keytest(RR_DOWN)) {
			
		}
		else if (_keytest(RR_2ND)) {
			
		}
	}
}

inline void refresh()
{
	
}