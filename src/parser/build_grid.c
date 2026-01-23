/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:03:07 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/23 20:23:58 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	line_len_no_nl(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n' && s[i] != '\r')
		i++;
	return (i);
}

static void	free_partial_grid(char **grid, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

//si falla la reserva de memoria de la fila
static int	row_malloc_error(t_game *game, int y)
{
	free_partial_grid(game->map.grid, y);
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	return (1);
}

//para copiar/rellenar la fila
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

int	build_grid(t_game *game, t_lines *arr)
{
	int	y;

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
			return (row_malloc_error(game, y));
		fill_grid_row(game, arr, y);
		y++;
	}
	return (0);
}
