#ifndef MAZE_h
#define MAZE_h 1

#ifndef WIDTH
#define WIDTH 5
#endif
#ifndef HEIGHT
#define HEIGHT 5
#endif

enum tile_t {
	tile_None,
	tile_Wall,
	tile_Start,
	tile_End,
};

enum dir {
	TOP = 1 << 0,
	RIGHT = 1 << 1,
	BOTTOM = 1 << 2,
	LEFT = 1 << 3,
};

struct maze {
	int w;
	int h;
	int start;
	int end;
	int now;
	int *pass_h;
	int *pass_v;
	int *visited;
	struct stack **backtrack;
};

int maze_Init (struct maze *this, int w, int h);
void maze_Close (struct maze *this);
void maze_Print (struct maze *this);
#endif
