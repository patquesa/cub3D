/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:34:44 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/27 19:21:34 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
//libera cada fila (string) y libera grid (array de punteros)
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

static void	free_textures(t_tex *t)
{
	if (t->north)
		mlx_delete_texture(t->north);
	if (t->south)
		mlx_delete_texture(t->south);
	if (t->west)
		mlx_delete_texture(t->west);
	if (t->east)
		mlx_delete_texture(t->east);
	t->north = NULL;
	t->south = NULL;
	t->west = NULL;
	t->east = NULL;
}

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
	free_textures(&game->textures);
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

/*
//limpia tanto si falla como si sale bien
void	game_destroy(t_game *game)
{
	if (!game)
		return;
    //liberar mapa si existe
	if (game->map.grid)
	{
		free_grid(game->map.grid);
		game->map.grid = NULL;
	}
	game->map.width = 0;
	game->map.height = 0;
	game->map.spawn_x = 0;
	game->map.spawn_y = 0;
	game->map.spawn_dir = 0;
    //liberar rutas de texturas
	free(game->cfg.north);
	free(game->cfg.south);
	free(game->cfg.east);
	free(game->cfg.west);
	game->cfg.north = NULL;
	game->cfg.south = NULL;
	game->cfg.east = NULL;
	game->cfg.west = NULL;
	//colores
	game->cfg.floor_color[0] = -1;
	game->cfg.ceiling_color[0] = -1;

	/aqui liberacion para MLX
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
}*/
