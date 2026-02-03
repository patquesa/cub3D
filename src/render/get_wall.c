/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 18:33:30 by adruz-to          #+#    #+#             */
/*   Updated: 2026/02/03 19:39:48 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Selecciona la textura de la pared golpeada según:
	- ray->side: 0 pared vertical (NS), 1 pared horizontal (EO)
	- signo de ray->dir_x/y para decidir cara EO o NS */
/* Select the texture of the hit wall based on:
	- ray->side: 0 vertical wall (NS), 1 horizontal wall (EW)
	- sign of ray->dir_x/y to decide EW or NS face */
mlx_texture_t	*get_wall_texture(t_game *game, t_ray *ray)
{
	// Si el rayo golpeó una pared vertical (lado Este u Oeste)
	if (ray->side == 0)
	{
		// Dirección positiva en X: mirando hacia el Este → textura Oeste
		if (ray->dir_x > 0)
			return (game->textures.west);
		else
			// Dirección negativa en X: mirando hacia el Oeste → textura Este
			return (game->textures.east);
	}
	else
	{
		// Si el rayo golpeó una pared horizontal (lado Norte o Sur)
		// Dirección positiva en Y: mirando hacia el Sur → textura Norte
		if (ray->dir_y > 0)
			return (game->textures.north);
		else
			// Dirección negativa en Y: mirando hacia el Norte → textura Sur
			return (game->textures.south);
	}
}

/* Calcula el punto exacto (coordenada) del muro donde choca el rayo. 
	Devuelve un double entre 0.0 y 1.0 
	- Si side == 0 (impacto en pared vertical)
	- Si side == 1 (impacto en pared horizontal)
	Esta coordenada se usa para seleccionar la columna de la textura (tex_x)
*/
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

