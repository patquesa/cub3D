/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 10:11:04 by adruz-to          #+#    #+#             */
/*   Updated: 2026/01/27 16:13:09 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Carga las texturas desde los archivos PNG */
void	init_textures(t_game *game)
{
	// Cargar texturas
	game->textures.north = mlx_load_png("textures/north.png");
	game->textures.south = mlx_load_png("textures/south.png");
	game->textures.east = mlx_load_png("textures/east.png");
	game->textures.west = mlx_load_png("textures/west.png");
	// Validar que se cargaron correctamente
	if (!game->textures.north || !game->textures.south || !game->textures.east
		|| !game->textures.west)
	{
		printf("Error: The textures could not be loaded\n");
		printf("Make sure 'textures/' folder exists with:\n");
		printf(" - north.png\n - south.png\n - east.png\n - west.png\n");
		exit(1);
	}
	printf("Textures OK");
}

/* Libera memoria de las texturas */
void	free_textures(t_game *game)
{
	if (game->textures.north)
		mlx_delete_texture(game->textures.north);
	if (game->textures.south)
		mlx_delete_texture(game->textures.south);
	if (game->textures.east)
		mlx_delete_texture(game->textures.east);
	if (game->textures.west)
		mlx_delete_texture(game->textures.west);
}
