/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 18:33:30 by adruz-to          #+#    #+#             */
/*   Updated: 2026/01/24 18:39:30 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Calcula el punto exacto del muro donde choca el rayo. 
	Devuelve un double entre 0.0 y 1.0 */

double	get_wall_x(t_game *game, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->player.x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

