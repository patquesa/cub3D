/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_direction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:02:53 by adruz-to          #+#    #+#             */
/*   Updated: 2026/01/30 14:08:36 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_ns(t_game *game, char dir)
{
	if (dir == 'N')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = -1.0;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0.0;
	}
	else
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = 1.0;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0.0;
	}
}

static void	set_ew(t_game *game, char dir)
{
	if (dir == 'E')
	{
		game->player.dir_x = 1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = 0.66;
	}
	else
	{
		game->player.dir_x = -1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = -0.66;
	}
}

/* Helper para configurar dirección basada en el spawn 
	- En cub3D se usa un FOV de ≈ 66grados por tradición 
	- como trabajamos con vectores, esos 66grados equivalen a 0.66 */
void	set_direction(t_game *game, char dir)
{
	if (dir == 'N' || dir == 'S')
		set_ns(game, dir);
	else if (dir == 'E' || dir == 'W')
		set_ew(game, dir);
}

