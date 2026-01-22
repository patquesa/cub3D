/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:01:04 by adruz-to          #+#    #+#             */
/*   Updated: 2026/01/22 13:50:47 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Drawing column
	Dibujar columnas con colores sólidos */
void	draw_column(t_game *game, t_ray *ray, int x)
{
	int			y;
	uint32_t	color;

	// Techo
	y = 0;
	// Dibuja px del techo desde arriba (0) hasta donde empieza la pared
	while (y < ray->draw_start)
		mlx_put_pixel(game->img, x, y++, game->ceiling);

	// Pared (color diferente según el lado)
	if (ray->side == 0)
		color = 0xFF0000FF; //rojo para verticales (NS)
	else
		color = 0x800000FF; // rojo oscuro para horizontales (EO)
	// Dibuja la pared desde draw_start hasta draw_end
	while (y < ray->draw_end)
		mlx_put_pixel(game->img, x, y++, color);
	// Suelo
	// Dibuja el suelo desde donde termina la pared hasta el final de la pantalla
	while (y < HEIGHT)
		mlx_put_pixel(game->img, x, y++, game->floor);
}
