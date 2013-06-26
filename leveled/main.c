#include "TileMap.h"
#include "extgraph.h"
#include "sprites.h"
#include "level.h"
#include "gui.h"
#include "all.h"
#include <tigcclib.h>

#define INIT_MAPSIZE ((LCD_WIDTH / 8) * (8 + (LCD_HEIGHT / 8)))

static char fontbk;
void *dbuf_hlight;
void *dbuf_hdark;
void	*dbuf_alight;
void *dbuf_adark;
static INT_HANDLER ai1,ai5;
static char db_block[(unsigned long)GRAYDBUFFER_SIZE+2*GRAY_BIG_VSCREEN_SIZE+BIG_VSCREEN_SIZE+480];
static char big_vscreen[GRAY_BIG_VSCREEN_SIZE*2+LCD_SIZE*2];

static void eloop (void);
static inline void drawplane (level_s level) __attribute__((always_inline));
static inline void drawtile (level_s level, unsigned short tile) __attribute__((always_inline));

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
	GrayDBufInit (db_block);
	dbuf_hlight = GrayDBufGetHiddenPlane(LIGHT_PLANE);
	dbuf_hdark = GrayDBufGetHiddenPlane(DARK_PLANE);
	dbuf_alight = GrayDBufGetActivePlane (LIGHT_PLANE);
	dbuf_adark = GrayDBufGetActivePlane (DARK_PLANE);
	
	//menu_s *test = menu_s_ (
	
	eloop();
	
	//menu_s_(short x, short y, short width, short height, short color, key_s event);
	
	GrayOff();
	
	SetIntVec(AUTO_INT_1,ai1);
  SetIntVec(AUTO_INT_5,ai5);
  
  FontSetSys(fontbk);
}

void eloop (void)
{
	level_s level;
	unsigned char tile;
	
	tile = 1;
	memset(&level, 0, sizeof(level));
	menu_s *menu = menu_s_(4,4, AUTO_SIZE , COLOR_BLACK, EVENT_(RR_F1));
	menu_add (menu, "derp");
	menu_add (menu, "derp");
	menu_add (menu, "derp");
	menu_add (menu, "derp");
	
	level.plane.width = 1000;
	level.plane.sprites = tiles;
	level.plane.big_vscreen = big_vscreen;
	level.plane.force_update = 1;
	level.height = 20;
	level.plane.matrix = calloc(level.plane.width, level.height);
	if (!level.plane.matrix)
		return;
	
	while (!_keytest(RR_ESC)) {
		if (_keytest(RR_LEFT)) {
			if (level.x_ > 0) {
				level.x_--;
				if (level.x > 0)
					level.x--;
				else 
					level.mx -= 8;
			}
		}
		if (_keytest(RR_RIGHT)) {
			if (level.x_ < level.plane.width) {
				level.x_++;
				if (level.x < (LCD_WIDTH / 8) - 1)
					level.x++;
				else
					level.mx += 8;
			}
		}
		if (_keytest(RR_UP)) {
			if (level.y_ > 0) {
				level.y_--;
				if (level.y > 0)
					level.y--;
				else
					level.my -= 8;
			}
		}
		if (_keytest(RR_DOWN)) {
			if (level.y_ < level.height) {
				level.y_++;
				if (level.y < LCD_HEIGHT / 8)
					level.y++;
				else
					level.my += 8;
			}
		}
		if (_keytest(RR_2ND)) {
			((char *)level.plane.matrix)[level.y_ * level.plane.width + level.x_] = tile;
		}
		drawplane (level);
		drawtile (level, tile);
		menu->condition(menu);
		refresh();
		delay(1000);
	}
	free(level.plane.matrix);
}

inline void drawplane (level_s level)
{
	DrawGrayPlane(level.mx, level.my, &level.plane, dbuf_hlight, dbuf_hdark, TM_GRPLC, TM_G8B);
}

inline void drawtile (level_s level, unsigned short tile)
{
	GrayITile8x8_RPLC_R(level.x, level.y << 3, tiles[tile], dbuf_hlight, dbuf_hdark);
}