#ifndef GUI_H_
#define GUI_H_

#define EVENT_(event) (key_s){event}

typedef struct toolbar_s toolbar_s;
typedef struct menu_s menu_s;
typedef struct key_s key_s;

struct key_s
{
	char row;
	char column;
};

struct toolbar_s
{
	short nmenus;
	menu_s **menus;
};

struct menu_s 
{
	short x;
	short y;
	short width;
	short height;
	short color;
	key_s event;
	void *(*active)(menu_s *);
	void *(*condition)(menu_s *);
	void *backup;
	short nitems;
	char **text;
};

extern menu_s *menu_s_(short x, short y, short width, short height, short color, key_s event);
extern toolbar_s *toolbar_s_ (void) __attribute__((always_inline));

extern void menu_add(menu_s *menu, const char *name);
extern void toolbar_add (toolbar_s *toolbar, menu_s *menu);

extern void draw_menu (menu_s *menu);
extern void hide_menu (menu_s *menu);

#endif