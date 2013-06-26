#include "gui.h"
#include "extgraph.h"
#include <stdlib.h>

#define EVENT_(event) event.row, event.column

menu_s *menu_s_(short x, short y, short color, key_s event)
{
	menu_s *menu;
	
	menu = calloc(1, sizeof(*menu));
	if (!menu)
		return NULL;
	menu->x = x;
	menu->y = y;
	menu->color = color;
	menu->event = event;
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
		menu->text = malloc(sizeof(*menu->text));
	else
		menu->text = realloc(menu->text, (menu->nitems + 1) * sizeof(*menu->text));
	menu->text[menu->nitems] = (char *)name;
	menu->nitems++;
}

void toolbar_add (toolbar_s *toolbar, menu_s *menu)
{
	
}