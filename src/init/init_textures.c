/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 10:11:04 by adruz-to          #+#    #+#             */
/*   Updated: 2026/02/04 12:24:38 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Load textures from parsed paths in the .cub file */
void	init_textures(t_game *game)
{
	game->textures.north = mlx_load_png(game->cfg.north);
	game->textures.south = mlx_load_png(game->cfg.south);
	game->textures.east = mlx_load_png(game->cfg.east);
	game->textures.west = mlx_load_png(game->cfg.west);
	if (!game->textures.north || !game->textures.south || !game->textures.east
		|| !game->textures.west)
	{
		printf("Error: Could not load textures\n");
		printf("Check paths in .cub file:\n");
		printf(" NO: %s\n", game->cfg.north);
		printf(" SO: %s\n", game->cfg.south);
		printf(" EA: %s\n", game->cfg.east);
		printf(" WE: %s\n", game->cfg.west);
		exit(1);
	}
}

/* Free up memory from textures */
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
