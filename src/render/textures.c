/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 18:27:25 by adruz-to          #+#    #+#             */
/*   Updated: 2026/01/26 09:22:09 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Selecciona la textura de la pared golpeada según:
	- ray->side: 0 pared vertical (NS), 1 pared horizontal (EO) 
	- signo de ray->dir_x/y para decidir cara EO o NS */
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
			return(game->textures.south);
	}
}
