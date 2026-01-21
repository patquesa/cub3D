/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:49:45 by adruz-to          #+#    #+#             */
/*   Updated: 2026/01/21 19:32:30 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	double	camera_x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		// Calcular posición en cámara (-1 a 1) 
		// Barremos todos los rayos de izq a drch
		camera_x = 2.0 * x / (double)WIDTH - 1.0;

		// Calcular dirección del rayo
		ray.dir_x = game->player.dir_x + game->player.plane_x * camera_x;
		ray.dir_y = game->player.dir_y + game->player.plane_y * camera_x;

		// Ejecutar DDA algorithm para encontrar la pared
		perform_dda(game, &ray);
		// TODO: Calcular distancia perpendicular
		// TODO: Dibujar columna

		x++;
	}
}

