/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:49:45 by adruz-to          #+#    #+#             */
/*   Updated: 2026/01/22 16:45:03 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Calcula la dirección del rayo */
void	init_ray(t_ray *ray, t_game *game, int x)
{
	// Posición del rayo en el plano de la cámara (-1 - 1)
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	// Dirección del rayo en el espacio del mundo
	ray->dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	// Posiciñon inicial en el mapa donde comienza el rayo
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	// Distancia que recorre el rayo para avanzar una celda en X o Y
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30; // 1e30 es un double (infinito práctico)
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
}



/*
Lanzar rayos desde la posición del jugador:
- Calcular dirección de cada rayo
- Detectar colisiones con paredes
- Calcular distancias

Lógica:
- Loop por cada columna de pixeles (ray) en la pantalla
- Algoritmo DDA o similar para detectar paredes
- Cálculo de distancias perpendiculares

*/

void	cast_ray(t_game *game)
{
	int	x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH) // para cada columna de la pantalla
	{
		// Calcular dirección del rayo
		init_ray(&ray, game, x);

		// Ejecutar DDA algorithm para encontrar la pared
		perform_dda(&ray, game);

		// Calcular distancia y altura
		calculate_wall_height(&ray);
		
		// Dibujar la columna vertical
		draw_column(game, &ray, x);
		x++;
	}
}
