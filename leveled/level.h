#ifndef LEVEL_H_
#define LEVEL_H_

#include "TileMap.h"

typedef struct level_s level_s;

struct level_s
{
	unsigned short height;
	unsigned short x;
	unsigned short y;
	unsigned short x_;
	unsigned short y_;
	unsigned short mx;
	unsigned short my;
	Plane plane;
};

#endif