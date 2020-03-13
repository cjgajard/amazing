#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze.h"

static int opt_width = 5;
static int opt_height = 5;
static struct option l_options[] = {
	{"width", required_argument, 0, 'w'},
	{"height", required_argument, 0, 'h'},
	{0, 0, 0, 0},
};

int load_args (void)
{
	char *w_str = getenv("WIDTH");
	if (w_str)
		opt_width = atoi(w_str);

	char *h_str = getenv("HEIGHT");
	if (h_str)
		opt_height = atoi(h_str);

	return 0;
}

int parse_args (int argc, char *argv[])
{
	int quit = 0;
	while (!quit) {
		int c = getopt_long(argc, argv, "w:h:", l_options, NULL);
		switch (c) {
		case -1:
			quit = 1;
			break;
		case 'w':
			opt_width = atoi(optarg);
			break;

		case 'h':
			opt_height = atoi(optarg);
			break;
		default:
			return 1;
		}
	}
	return 0;
}

int main (int argc, char *argv[])
{
	if (load_args())
		return 1;
	if (parse_args(argc, argv))
		return 1;

	srand(time(0));
	printf("Maze generator (%dx%d)\n", opt_width, opt_height);

	struct maze m;
	maze_Init(&m, opt_width, opt_height);
	maze_Print(&m);
	maze_Close(&m);
	return 0;
}
