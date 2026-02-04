/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:17:37 by patquesa          #+#    #+#             */
/*   Updated: 2026/02/04 13:16:51 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Create a copy of the map grid for flood fill validation */
static char	**copy_grid(t_game *game)
{
	char	**cpy;
	int		y;

	cpy = (char **)malloc(sizeof(char *) * game->map.height);
	if (!cpy)
		return (NULL);
	y = 0;
	while (y < game->map.height)
	{
		cpy[y] = ft_strdup(game->map.grid[y]);
		if (!cpy[y])
		{
			free_grid_copy(cpy, y);
			return (NULL);
		}
		y++;
	}
	return (cpy);
}

/* Return 1 if map is open (goes out of bounds or touches ' ') */
static int	flood(char **g, t_game *game, int y, int x)
{
	if (y < 0 || x < 0 || y >= game->map.height || x >= game->map.width)
		return (1);
	if (g[y][x] == ' ')
		return (1);
	if (g[y][x] == '1' || g[y][x] == 'V')
		return (0);
	if (g[y][x] != '0')
		return (1);
	g[y][x] = 'V';
	if (flood(g, game, y - 1, x))
		return (1);
	if (flood(g, game, y + 1, x))
		return (1);
	if (flood(g, game, y, x - 1))
		return (1);
	if (flood(g, game, y, x + 1))
		return (1);
	return (0);
}

/* Validate map closure using flood fill algorithm */
static int	validate_flood(t_game *game)
{
	char	**cpy;
	int		open;

	cpy = copy_grid(game);
	if (!cpy)
		return (1);
	open = flood(cpy, game, game->map.spawn_y, game->map.spawn_x);
	free_grid_copy(cpy, game->map.height);
	if (open)
		return (1);
	return (0);
}

/* Check if a floor cell is properly surrounded by walls */
static int	is_closed_floor(t_game *g, int y, int x)
{
	if (y == 0 || x == 0 || y == g->map.height - 1 || x == g->map.width - 1)
		return (0);
	if (g->map.grid[y - 1][x] == ' ' || g->map.grid[y + 1][x] == ' '
		|| g->map.grid[y][x - 1] == ' ' || g->map.grid[y][x + 1] == ' ')
		return (0);
	if (g->map.grid[y - 1][x - 1] == ' ' || g->map.grid[y - 1][x + 1] == ' '
		|| g->map.grid[y + 1][x - 1] == ' ' || g->map.grid[y + 1][x + 1] == ' ')
		return (0);
	return (1);
}

/* Validate the entire map: check characters and closure */
int	validate_map(t_game *game)
{
	int		y;
	int		x;
	char	c;

	if (!game || !game->map.grid
		|| game->map.height <= 0 || game->map.width <= 0)
		return (fail("Invalid map"));
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			c = game->map.grid[y][x];
			if (!is_valid_cell(c))
				return (fail("Invalid map character"));
			if (c == '0' && !is_closed_floor(game, y, x))
				return (fail("Map is not closed"));
			x++;
		}
		y++;
	}
	if (validate_flood(game) != 0)
		return (fail("Map is not closed"));
	return (0);
}
