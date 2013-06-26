#include "all.h"
#include "gui.h"
#include "extgraph.h"
#include <tigcclib.h>
#include <stdlib.h>

#define EVENT__(event) event.row, event.column

static void *activedefault (menu_s *menu);
static void *eventdefault (menu_s *menu);

menu_s *menu_s_(short x, short y, short width, short height, short color, key_s event)
{
	menu_s *menu;
	
	menu = calloc(1, sizeof(*menu));
	if (!menu)
		return NULL;
	menu->x = x;
	menu->y = y;
	menu->width = width;
	menu->height = height;
	menu->color = color;
	menu->event = event;
	menu->active = activedefault;
	menu->condition = eventdefault;
	return menu;
}


toolbar_s *toolbar_s_ (void)
{
	return calloc(1, sizeof(toolbar_s));
}

/*
struct menu_s 
{
	short x;
	short y;
	key_s event;
	short nitems;
	char **text;
};
*/

void menu_add (menu_s *menu, const char *name)
{
	if (menu->nitems)
		menu->text = realloc(menu->text, (menu->nitems + 1) * sizeof(*menu->text));
	else
		menu->text = malloc(sizeof(*menu->text));
	menu->text[menu->nitems] = (char *)name;
	menu->nitems++;
}

/*
struct toolbar_s
{
	short nmenus;
	menu_s *menus;
};
*/

void toolbar_add (toolbar_s *toolbar, menu_s *menu)
{
	if (toolbar->nmenus)
		toolbar->menus = realloc(toolbar->menus, (toolbar->nmenus + 1) * sizeof(*toolbar->menus));
	else
		toolbar->menus = malloc(sizeof(*toolbar->menus));
	toolbar->menus[toolbar->nmenus] = menu;
	toolbar->nmenus++;
}

void draw_menu (menu_s *menu)
{
	short i;
	short eff_width;
	
	eff_width = (menu->width / 8) + (menu->width % 8) ? 1 : 0;
	menu->backup = malloc(2 * ((menu->width + (8 - menu->width % 8)) * menu->height));
	if (!menu->backup)
		return;
	for (i = 0; i < eff_width; i++)
		GrayFastGetBkgrnd8_R(menu->x + (8 * i), menu->y, menu->height, dbuf_alight, dbuf_adark, menu->backup);
	GrayFastFillRect_R(dbuf_alight, dbuf_adark, menu->x, menu->y, menu->x + menu->width, menu->y + menu->height, menu->color);
}

void hide_menu (menu_s *menu)
{
	
}

void *activedefault (menu_s *menu)
{
	while (!_keytest(RR_ESC)) {
		
	}
	return NULL;
}

static void *eventdefault (menu_s *menu)
{
	if (_keytest(EVENT__(menu->event))) {
		draw_menu(menu);
		return menu->active(menu);
	}
	return NULL;
}