/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 18:33:30 by adruz-to          #+#    #+#             */
/*   Updated: 2026/01/25 14:41:13 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Calcula el punto exacto (coordenada) del muro donde choca el rayo. 
	Devuelve un double entre 0.0 y 1.0 
	- Si side == 0 (impacto en pared vertical)
	- Si side == 1 (impacto en pared horizontal)
	Esta coordenada se usa para seleccionar la columna de la textura (tex_x)
*/

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

