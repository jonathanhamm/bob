#ifndef LEVEL_H_
#define LEVEL_H_

typedef struct level_s level_s;

struct level_s
{
	unsigned short width;
	unsigned short height;
	unsigned short x;
	unsigned short y;
	unsigned short x_;
	unsigned short y_;
	char *map;
};

#endif