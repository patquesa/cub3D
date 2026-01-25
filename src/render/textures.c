/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 18:27:25 by adruz-to          #+#    #+#             */
/*   Updated: 2026/01/25 14:41:21 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Selecciona la textura de la pared golpeada según:
	- ray->side: 0 pared vertical (NS), 1 pared horizontal (EO) 
	- signo de ray->dir_x/y para decidir cara EO o NS */
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
			return(game->textures.south);
	}
}
