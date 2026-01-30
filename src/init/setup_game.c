/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:52:20 by adruz-to          #+#    #+#             */
/*   Updated: 2026/01/30 13:50:00 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

/* Helper para configurar dirección basada en el spawn
	- En cub3D se usa un FOV de ≈ 66grados por tradición
	- como trabajamos con vectores, esos 66grados equivalen a 0.66 */
static void	set_direction(t_game *game, char dir)
{
	if (dir == 'N')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = -1.0;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0.0;
	}
	else if (dir == 'S')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = 1.0;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0.0;
	}
	else if (dir == 'E')
	{
		game->player.dir_x = 1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		game->player.dir_x = -1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = -0.66;
	}
}

/* Inicializa la posición y orientación del jugador desde el spawn parseado */
static void	init_player(t_game *game)
{
	game->player.x = game->map.spawn_x + 0.5;
	game->player.y = game->map.spawn_y + 0.5;
	set_direction(game, game->map.spawn_dir);
}

/* Inicializa los colores del techo y suelo desde cfg parseado */
static void	init_colors(t_game *game)
{
	game->ceiling = (0xFF << 24) | (game->cfg.ceiling_color[0] << 16)
		| (game->cfg.ceiling_color[1] << 8) | game->cfg.ceiling_color[2];
	game->floor = (0xFF << 24) | (game->cfg.floor_color[0] << 16)
		| (game->cfg.floor_color[1] << 8) | game->cfg.floor_color[2];
}

/* Inicializa todos los componentes del juego */
void	setup_game(t_game *game)
{
	init_player(game);
	init_textures(game);
	init_colors(game);
}
