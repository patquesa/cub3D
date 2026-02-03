/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:34:44 by patquesa          #+#    #+#             */
/*   Updated: 2026/02/03 19:43:04 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

//libera cada fila (string) y libera grid (array de punteros)
/* Free each row (string) and free grid (array of pointers) */
static void	free_grid(char **grid)
{
	int	y;

	if (!grid)
		return;
	y = 0;
	while (grid[y])
	{
		free(grid[y]); //libera cada fila
		y++;
	}
	free(grid); //libera array
}

/* Free all texture paths in configuration */
static void	free_cfg_paths(t_cfg *cfg)
{
	free(cfg->north);
	free(cfg->south);
	free(cfg->east);
	free(cfg->west);
	cfg->north = NULL;
	cfg->south = NULL;
	cfg->east = NULL;
	cfg->west = NULL;
}

/* Clean up and free all game resources (grid, paths, textures, MLX) */
void	game_destroy(t_game *game)
{
	if (!game)
		return ;
	if (game->map.grid)
	{
		free_grid(game->map.grid);
		game->map.grid = NULL;
	}
	free_cfg_paths(&game->cfg);
	free_textures(game);
	if (game->img && game->mlx)
	{
		mlx_delete_image(game->mlx, game->img);
		game->img = NULL;
	}
	if (game->mlx)
	{
		mlx_terminate(game->mlx);
		game->mlx = NULL;
	}
}

