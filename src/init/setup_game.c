/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:52:20 by adruz-to          #+#    #+#             */
/*   Updated: 2026/01/30 14:08:42 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>


/* Inicializa la posición y orientación del jugador desde el spawn parseado */
static void	init_player(t_game *game)
{
	// Posición inicial del spawn parseado (centro de la celda)
	game->player.x = game->map.spawn_x + 0.5;
	game->player.y = game->map.spawn_y + 0.5;

	// Dirección inicial según spawn_dir (N, S, E, W)
	set_direction(game, game->map.spawn_dir);
}

/* Inicializa los colores del techo y suelo desde cfg parseado */
static void	init_colors(t_game *game)
{
	// Formato: 0xAARRGGBB
	// Convierte RGB parseado a formato uint32_t
	game->ceiling = (0xFF << 24)
		| (game->cfg.ceiling_color[0] << 16)
		| (game->cfg.ceiling_color[1] << 8)
		| game->cfg.ceiling_color[2];
	game->floor = (0xFF << 24)
		| (game->cfg.floor_color[0] << 16)
		| (game->cfg.floor_color[1] << 8)
		| game->cfg.floor_color[2];
}

/* Inicializa todos los componentes del juego */
void	setup_game(t_game *game)
{
	// El mapa ya viene parseado, solo inicializamos jugador, texturas y colores
	init_player(game);
	init_textures(game);
	init_colors(game);
}
