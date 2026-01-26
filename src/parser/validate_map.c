/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:17:37 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/26 19:16:40 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_cell(char c)
{
	return (c == '0' || c == '1' || c == ' '); //suelo, pared, vacio
}

static void	free_grid_copy(char **g, int h)
{
	int	y;

	if (!g)
		return ;
	y = 0;
	while (y < h)
	{
		free(g[y]);
		y++;
	}
	free(g);
}

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

/* Devuelve 1 si detecta mapa abierto (sale o toca ' ') */
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

int	validate_map(t_game *game)
{
	int		y;
	int		x;
	char	c;

	if (!game || !game->map.grid || game->map.height <= 0 || game->map.width <= 0)
		return (1);

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			c = game->map.grid[y][x];
			if (!is_valid_cell(c))
				return (1);
			x++;
		}
		y++;
	}
	if (validate_flood(game) != 0)
		return (1);
	return (0);
}

/*

static int	is_closed_floor(t_game *g, int y, int x)
{
	if (y == 0 || x == 0 || y == g->map.height - 1 || x == g->map.width - 1)
		return (0);
	if (g->map.grid[y - 1][x] == ' ' || g->map.grid[y + 1][x] == ' '
		|| g->map.grid[y][x - 1] == ' ' || g->map.grid[y][x + 1] == ' ')
		return (0); //mapa abierto (0)
	return (1); //mapa cerrado (1)
}

int	validate_map(t_game *game)
{
	int		y;
	int		x;
	char	c;

	if (!game || !game->map.grid || game->map.height <= 0 || game->map.width <= 0) //si grid es NULL
		return (1);
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			c = game->map.grid[y][x];
			if (!is_valid_cell(c))
				return (1);
			if (c == '0' && !is_closed_floor(game, y, x))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}
*/