#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "stack.h"

static void list_Shuffle (int *this, int size)
{
	for (int n = size; n > 0; n--) {
		int k = rand() % n;
		int tmp = this[0];
		this[0] = this[k];
		this[k] = tmp;
	}
}

static int maze_RandomizeNext (struct maze *this, int *now) {
	enum dir list[4] = {TOP, RIGHT, BOTTOM, LEFT};
	list_Shuffle((int *)list, 4);

	for (int i = 0; i < 4; i++) {
		enum dir d = list[i];
		int x = this->now % this->w + (d == RIGHT) - (d == LEFT);
		int y = this->now / this->w + (d == BOTTOM) - (d == TOP);
		if (x < 0 || x >= this->w || y < 0 || y >= this->h)
			continue;
		int next = y * this->w + x;
		if (this->visited[next])
			continue;
		if (now)
			*now = next;
		return 0;
	}
	return 1;
}

static enum tile_t maze_TileType (struct maze *this, int i, int j)
{
	int x = (i - 1) / 2;
	int y = (j - 1) / 2;
	int now = y * this->w + x;

	int is_start = now == this->start;
	int is_end = now == this->end;

	if (!(i % 2 || j % 2))
		return tile_Wall;

	if (i == 0 || j == 0 || i == 2 * this->w || j == 2 * this->h) {
		if (is_start)
			return tile_None;
		else if (is_end)
			return tile_None;
		return tile_Wall;
	}

	if (!(j % 2) && i % 2)
		return this->pass_h[now] ? tile_None : tile_Wall;
	if (j % 2 && !(i % 2))
		return this->pass_v[now] ? tile_None : tile_Wall;

	if (is_start)
		return tile_Start;
	if (is_end)
		return tile_End;
	return tile_None;
}

static void maze_RemoveWall (struct maze *this, int next) {
	int x = this->now % this->w, y = this->now / this->w;
	int nx = next % this->w, ny = next / this->w;

	if (nx - x)
		this->pass_v[y * this->w + (nx > x ? x : nx)] = 1;
	if (ny - y)
		this->pass_h[(ny > y ? y : ny) * this->w + x] = 1;
}

static void maze_Generate (struct maze *this)
{
	this->now = rand() % (this->w * this->h);
	stack_Push(this->backtrack, this->now);
	while (*this->backtrack) {
		if (stack_Pop(this->backtrack, &this->now)) {
			fprintf(stderr, "error @ stack_Pop\n");
			break;
		}
		int next;
		if (maze_RandomizeNext(this, &next))
			continue;
		stack_Push(this->backtrack, this->now);
		maze_RemoveWall(this,  next);
		this->visited[next] = 1;
		stack_Push(this->backtrack, next);
		this->now = next;
	}
}

static void maze_PrintTile (enum tile_t t)
{
	switch (t) {
	case tile_Wall:
		printf("##");
		break;
	case tile_Start:
		printf("\033[41m  \033[0m");
		break;
	case tile_End:
		printf("\033[42m  \033[0m");
		break;
	default:
		printf("  ");
	}
}

int maze_Init (struct maze *this, int w, int h)
{
	this->w = w;
	this->h = h;

	this->start = this->w;
	this->end = this->w * (this->h - 1) - 1;

	this->visited = calloc(this->h * this->w, sizeof(int));
	this->backtrack = malloc(sizeof(struct stack *));
	this->pass_h = calloc(this->w * this->h, sizeof(int));
	this->pass_v = calloc(this->w * this->h, sizeof(int));

	maze_Generate(this);
	return 0;
}

void maze_Print (struct maze *this)
{
	for (int j = 0; j < 2 * this->h + 1; j++) {
		for (int i = 0; i < 2 * this->w + 1; i++) {
			enum tile_t t = maze_TileType(this, i, j);
			maze_PrintTile(t);
		}
		printf("\n");
	}
}

void maze_Close (struct maze *this)
{
	free(this->pass_h);
	free(this->pass_v);
	free(this->backtrack);
	free(this->visited);
}
