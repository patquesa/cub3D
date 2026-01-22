/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:34:44 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/22 12:08:58 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
//libera cada fila (string) y libera grid (array de punteros)
static void	free_grid(char **grid, int height)
{
	int	y;

	if (!grid)
		return;
	y = 0;
	while (y < height)
	{
		free(grid[y]); //libera cada fila
		y++;
	}
	free(grid); //libera array
}
//limpia tanto si falla como si sale bien
void	game_destroy(t_game *game)
{
	if (!game)
		return;
    //liberar mapa si existe
	if (game->map.grid)
	{
		free_grid(game->map.grid, game->map.height);
		game->map.grid = NULL;
	}
	game->map.width = 0;
	game->map.height = 0;
	game->map.spawn_x = 0;
	game->map.spawn_y = 0;
	game->map.spawn_dir = 0;
    //liberar rutas de texturas
	free(game->textures.north);
	free(game->textures.south);
	free(game->textures.east);
	free(game->textures.west);
	game->textures.north = NULL;
	game->textures.south = NULL;
	game->textures.east = NULL;
	game->textures.west = NULL;

	//aqui liberacion para MLX
}
