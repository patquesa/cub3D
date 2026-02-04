/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_height.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:00:28 by adruz-to          #+#    #+#             */
/*   Updated: 2026/02/03 19:40:55 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Wall calculation 
Calcula distancias y alturas (usa los datos del DDA) */
/* Calculate wall distances and heights (uses DDA data) */
void	calculate_wall_height(t_ray *ray)
{
	// Calcula la distancia perpendicular real a la pared, evita fisheye
	if (ray->side == 0) // si golpeó un lado vertical (NS)
		ray->perp_wall_dist = ray->side_dis_x - ray->delta_dist_x;
	else // Si golpeó un lado horizontal (EO)
		ray->perp_wall_dist = ray->side_dis_y - ray->delta_dist_y;
	// Calcula la altura de la pared en px, cuanto más lejos, menor altura
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	// Calcula donde empieza a dibujarse la pared verticalmente
	// desde el centro hacia arriba
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	// Si la pared es tan alta que se sale por arriba, recorta a 0
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	
	// Calcula donde termina de dibujarse la pared, desde el centro hacia abajo
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;

	// Si la pared se sale por abajo, recorta el último px
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}
