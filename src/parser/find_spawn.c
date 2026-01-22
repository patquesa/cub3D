/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_spawn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:28:38 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/22 18:27:32 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_spawn(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	find_and_store_spawn(t_game *game)  //encontrar al jugador
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
			if (is_spawn(game->map.grid[y][x]))
			{
				game->map.spawn_x = x;
				game->map.spawn_y = y;
				game->map.spawn_dir = game->map.grid[y][x];
				game->map.grid[y][x] = '0';
				count++;
			}
			x++;
		}
		y++;
	}
	if (count != 1)
    	return (1);
	return (0);
}
