/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:52:20 by adruz-to          #+#    #+#             */
/*   Updated: 2026/02/03 17:35:15 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

/* Initialize player position and orientation from parsed spawn */
static void	init_player(t_game *game)
{
	game->player.x = game->map.spawn_x + 0.5;
	game->player.y = game->map.spawn_y + 0.5;
	set_direction(game, game->map.spawn_dir);
}

/* Initialize ceiling and floor colors from parsed config */
static void	init_colors(t_game *game)
{
	game->ceiling = (game->cfg.ceiling_color[0] << 24)
		| (game->cfg.ceiling_color[1] << 16)
		| (game->cfg.ceiling_color[2] << 8)
		| 0xFF;
	game->floor = (game->cfg.floor_color[0] << 24)
		| (game->cfg.floor_color[1] << 16)
		| (game->cfg.floor_color[2] << 8)
		| 0xFF;
}

/* Initialize all game components (player, textures, colors) */
void	setup_game(t_game *game)
{
	init_player(game);
	init_textures(game);
	init_colors(game);
}
