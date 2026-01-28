#include "cub3d.h"

#include "cub3d.h"
#include <stdio.h>

void	dump_cfg(t_cfg *c)
{
	printf("=== CFG ===\n");
	printf("NO (north): %s\n", c->north);
	printf("SO (south): %s\n", c->south);
	printf("WE (west):  %s\n", c->west);
	printf("EA (east):  %s\n", c->east);

	printf("F: %d,%d,%d (set=%d)\n",
		c->floor_color[0], c->floor_color[1], c->floor_color[2], c->floor_set);
	printf("C: %d,%d,%d (set=%d)\n",
		c->ceiling_color[0], c->ceiling_color[1], c->ceiling_color[2], c->ceiling_set);
	printf("===========\n");
}

void	dump_grid(char **grid, int height)
{
	int	y;

	printf("=== MAP GRID ===\n");
	if (!grid)
	{
		printf("(null grid)\n");
		printf("================\n");
		return ;
	}
	for (y = 0; y < height; y++)
		printf("[%02d] \"%s\"\n", y, grid[y]);
	printf("================\n");
}

void	dump_spawn(t_game *g)
{
	printf("=== SPAWN ===\n");
	printf("pos: (%d, %d)\n", g->map.spawn_x, g->map.spawn_y);
	printf("dir: %c\n", g->map.spawn_dir);
	printf("=============\n");
}
