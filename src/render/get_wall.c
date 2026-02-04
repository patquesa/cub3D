/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 18:33:30 by adruz-to          #+#    #+#             */
/*   Updated: 2026/02/04 13:26:42 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Select the texture of the hit wall based on:
	- ray->side: 0 vertical wall (NS), 1 horizontal wall (EW)
	- sign of ray->dir_x/y to decide EW or NS face */
mlx_texture_t	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (game->textures.west);
		else
			return (game->textures.east);
	}
	else
	{
		if (ray->dir_y > 0)
			return (game->textures.north);
		else
			return (game->textures.south);
	}
}

/* Calculate the exact point (coordinate) where the ray hits the wall.
	Returns a double between 0.0 and 1.0
	- If side == 0 (impact on vertical wall)
	- If side == 1 (impact on horizontal wall)
	This coordinate is used to select the texture column (tex_x)
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
