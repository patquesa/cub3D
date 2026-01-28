/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:49:45 by adruz-to          #+#    #+#             */
/*   Updated: 2026/01/28 12:16:54 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Calcula la dirección del rayo
	- camera_x mapea la columna [0..WIDTH) al plano de cámara [-1..1].
	- dir_x/dir_y combinan la dirección del jugador y el plano (FOV) para obtener
		la dirección del rayo en el mundo.
	- map_x/map_y es la celda del mapa donde está el jugador al iniciar el rayo.
	- delta_dist_x/delta_dist_y son las distancias que avanza el rayo al cruzar
		una línea de rejilla en X o Y (usadas por el DDA).
	- hit se inicializa a 0 y el DDA lo pondrá a 1 cuando se encuentre una pared.
*/
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
Lanza y procesa todos los rayos desde la posición del jugador:
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
	int		x;
	t_ray	ray;
	t_wall	wall;

	x = 0;
	while (x < WIDTH) // para cada columna de la pantalla
	{
		// Calcular dirección del rayo
		init_ray(&ray, game, x);
		// Ejecutar DDA algorithm para encontrar una pared
		perform_dda(&ray, game);
		// Calcular distancia, altura y límites de dibujo
		calculate_wall_height(&ray);
		// Si hay texturas, dibuja texturizado; si no, color plano
		if (game->textures.north && game->textures.south && game->textures.east
			&& game->textures.west)
		{
			wall = init_wall(game, &ray);
			draw_wall(game, &ray, &wall, x);
		}
		else
			// Dibujar la columna vertical
			draw_column(game, &ray, x);
		x++;
	}
}
