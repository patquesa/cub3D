/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:17:37 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/26 09:50:08 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_cell(char c)
{
	return (c == '0' || c == '1' || c == ' '); //suelo, pared, vacio
}

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
