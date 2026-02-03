/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:03:07 by patquesa          #+#    #+#             */
/*   Updated: 2026/02/03 17:35:06 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Calculate the length of the line (without \n) */
static int	line_len_no_nl(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n' && s[i] != '\r')
		i++;
	return (i);
}

/* Handle malloc error while building the grid (cleanup partial allocation) */
static int	row_malloc_error(t_game *game, int y)
{
	int	i;

	i = 0;
	while (i < y)
	{
		free(game->map.grid[i]);
		i++;
	}
	free(game->map.grid);
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	return (1);
}

/* Copy a line from the original map to the final grid, normalizing
   characters and padding to make it rectangular */
static void	fill_grid_row(t_game *game, t_lines *arr, int y)
{
	int		x;
	int		len;
	char	c;

	len = line_len_no_nl(arr->v[y]);
	x = 0;
	while (x < game->map.width)
	{
		if (x < len)
		{
			c = arr->v[y][x];
			if (c == '\t' || c == '\r')
				c = ' ';
			game->map.grid[y][x] = c;
		}
		else
			game->map.grid[y][x] = ' ';
		x++;
	}
	game->map.grid[y][game->map.width] = '\0';
}

/* Build the final rectangular grid map */
int	build_grid(t_game *game, t_lines *arr)
{
	int	y;

	if (arr->count <= 0 || arr->maxw <= 0)
		return (1);
	game->map.height = arr->count;
	game->map.width = arr->maxw;
	game->map.grid = (char **)malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		return (1);
	y = 0;
	while (y < game->map.height)
	{
		game->map.grid[y] = (char *)malloc(game->map.width + 1);
		if (!game->map.grid[y])
			return (row_malloc_error(game, y));
		fill_grid_row(game, arr, y);
		y++;
	}
	game->map.grid[game->map.height] = NULL;
	return (0);
}
