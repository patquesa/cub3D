/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:03:07 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/22 13:27:21 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	line_len_no_nl(const char *s)
{
	int i = 0;
	while (s[i] && s[i] != '\n' && s[i] != '\r')
		i++;
	return (i);
}

//pasar la lista a una matriz rectangular
int	build_grid(t_game *game, t_lines *arr)
{
	int	y;
	int	x;
	int	len;

	game->map.height = arr->count;
	game->map.width = arr->maxw;
	game->map.grid = (char **)malloc(sizeof(char *) * game->map.height);
	if (!game->map.grid)
		return (1);

	y = 0;
	while (y < game->map.height)
	{
		game->map.grid[y] = (char *)malloc(game->map.width + 1);
		if (!game->map.grid[y])
			return (1);
		len = line_len_no_nl(arr->v[y]);
		x = 0;
		while (x < game->map.width)
		{
			if (x < len)
			{
				char c = arr->v[y][x];
				if (c == '\t' || c == '\r')
					c = ' ';
				game->map.grid[y][x] = c;
			}
			else
				game->map.grid[y][x] = ' '; //rellena con espacios ' ' donde falten caracteres
			x++;
		}
		game->map.grid[y][game->map.width] = '\0';
		y++;
	}
	return (0);
}
