/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:37:07 by adruz-to          #+#    #+#             */
/*   Updated: 2026/02/03 19:38:30 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Calcula la dirección de paso (step) y la distancia inicial (side_dist)
	- step: en qué dirección avanzar en el mapa (+1 o -1)
	- side_dist: distancia desde la posición actual hasta la primera
	intersección
*/
/* Calculate step direction and initial side distance
	- step: which direction to advance in the map (+1 or -1)
	- side_dist: distance from current position to first intersection
*/
static void	calculate_step_and_side_dist(t_ray *ray, t_game *game)
{
	// STEP Y SIDE_DIST EN X
	// Determina si el rayo va hacia la izq o hacia la derecha
	if (ray->dir_x < 0)
	{
		ray->step_x = -1; // Avanza hacia la izquierda (oeste)
		// Distancia desde la posición del jugador hasta el borde izq del cuadrado
		ray->side_dis_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1; // Avanza hacia la derecha (este)
		// Distancia desde la posición del jugador hasta el borde derecho del cuadrado
		ray->side_dis_x = (ray->map_x + 1.0 - game->player.x)
			* ray->delta_dist_x;
	}
	// STEP Y SIDE_DIST EN Y
	// Determina si el rayo va hacia la izq o hacia la derecha
	if (ray->dir_y < 0)
	{
		ray->step_y = -1; // Avanza hacia la izquierda (oeste)
		// Distancia desde la posición del jugador hasta el borde izq del cuadrado
		ray->side_dis_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1; // Avanza hacia la derecha (este)
		// Distancia desde la posición del jugador hasta el borde derecho del cuadrado
		ray->side_dis_y = (ray->map_y + 1.0 - game->player.y)
			* ray->delta_dist_y;
	}
}

/*
Algoritmo DDA (Digital Differential Analysis):
	Se encarga solo de encontar una pared
- Avanza cuadrícula por cuadrícula hasta encontrar una pared
- Calcula la distancia deltaX y deltaY entre intersecciones
- Determina qué lado de la pared se golpeó (N/S/E/O)
*/
/* DDA (Digital Differential Analysis) algorithm:
	Only responsible for finding a wall
- Advances grid by grid until finding a wall
- Calculates deltaX and deltaY distance between intersections
- Determines which side of the wall was hit (N/S/E/W)
*/
void	perform_dda(t_ray *ray, t_game *game)
{
	// Calcular la dirección de paso y la distancia inicial
	calculate_step_and_side_dist(ray, game);
	// Avanzar hasta encontrar pared
	while (ray->hit == 0)
	{
		// Saltar al siguiente lado del mapa
		if (ray->side_dis_x < ray->side_dis_y)
		{
			ray->side_dis_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dis_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		// Validar que no se salga del mapa
		if (ray->map_x < 0 || ray->map_x >= game->map.width || ray->map_y < 0
			|| ray->map_y >= game->map.height)
		{
			ray->hit = 1; // Tratar fuera del mapa como pared
			break;
		}
			// Verificamos si golpeó una pared
			if (game->map.grid[ray->map_y][ray->map_x] == '1')
				ray->hit = 1;
	}
}
