/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_spawn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:28:38 by patquesa          #+#    #+#             */
/*   Updated: 2026/02/03 17:35:13 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Check if character is a spawn point (N, S, E, or W) */
static int	is_spawn(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/* Store spawn position and direction, then replace with '0' in grid */
static void	store_spawn(t_game *game, int x, int y)
{
	game->map.spawn_x = x;
	game->map.spawn_y = y;
	game->map.spawn_dir = game->map.grid[y][x];
	game->map.grid[y][x] = '0';
}

/* Find and store the player spawn position (must be exactly one) */
int	find_and_store_spawn(t_game *game)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (is_spawn(game->map.grid[y][x]) && ++count == 1)
			{
				store_spawn(game, x, y);
			}
			x++;
		}
		y++;
	}
	if (count != 1)
		return (fail("Invalid player spawn"));
	return (0);
}
