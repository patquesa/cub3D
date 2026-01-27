/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:01:04 by adruz-to          #+#    #+#             */
/*   Updated: 2026/01/27 15:22:53 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Inicializa la información de la pared a dibujar (texturizada) para una
columna.
	- Selecciona la textura correcta (N,S,E,O) según el lado impactado y la
	dirección del rayo
*/
t_wall	init_wall(t_game *game, t_ray *ray)
{
	t_wall	wall;

	// Determina qué textura usar (N S E O) segun la dirección del rayo y el lado
	// de la pared golpeado
	wall.texture = get_wall_texture(game, ray);
	// Calcula la coordenada exacta (entre 0.0 y 1.0) donde el rayo golpeó la pared
	wall.wall_x = get_wall_x(game, ray);
	// Normalizar a [0, 1) para poder mapear a columnas de la textura
	// evita índices fuera de rango si get_wall_x devuelve valores > 1
	wall.wall_x -= floor(wall.wall_x);
	// Convierte la coordenada en un índice de columna de la textura
	wall.tex_x = (int)(wall.wall_x * wall.texture->width);
	// Invertir la textura horizontalmente en casos concretos para no verla al revés
	//	Convención típica (LodeV):
	//	- side == 0 (pared vertical): si el rayo va hacia +X, invierte
	//	- side == 1 (pared horizontal): si el rayo va hacia -Y, invierte
	if (ray->side == 0 && ray->dir_x > 0)
		wall.tex_x = wall.texture->width - wall.tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		wall.tex_x = wall.texture->width - wall.tex_x - 1;
	// Clamp defensivo por si redondeos dejan tex_x fuera de [0, width)
	if (wall.tex_x < 0)
		wall.tex_x = 0;
	if (wall.tex_x >= (int)wall.texture->width)
		wall.tex_x = (int)wall.texture->width - 1;
	return (wall);
}

/* Lee el color RGBA de la textura en (x, y) y lo devuelve empaquetado
	como 0xRRGGBBAA */
uint32_t	get_tex_color(mlx_texture_t *texture, int x, int y)
{
	int	index;

	// Comprobación de límites para evitar lecturas fuera de memoria
	if (x < 0 || x >= (int)texture->width || y < 0 || y >= (int)texture->height)
		return (0x000000FF);
	// Índice nase de píxel (cada pixel son 4 bytes: R, G, B, A)
	index = (y * texture->width + x) * 4;
	// Empequetado a 0xRRGGBBAA mediante desplazamientos de bits
	return ((texture->pixels[index] << 24) | (texture->pixels[index
			+ 1] << 16) | (texture->pixels[index
			+ 2] << 8) | texture->pixels[index + 3]);
}

/* Dibuja la sección de pared texturizada para una columna de pantalla en x */
void	draw_wall(t_game *game, t_ray *ray, t_wall *wall, int x)
{
	int			y;
	uint32_t	color;

	int d;     // acumulador en punto fijo xa calcular la posición en la textura
	int tex_y; // fila de la textura a muestrear
	// Dibujar el techo primero
	y = 0;
	while (y < ray->draw_start)
		mlx_put_pixel(game->img, x, y++, game->ceiling);
	// Dibujar pared con textura
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		// Cálculo de la posición vertical en la textura usando un punto fijo
		// multiplicador 256
		d = y * 256 - HEIGHT * 128 + ray->line_height * 128;
		// mapeo de d a la coordenada tex_y dentro de la textura
		tex_y = ((d * wall->texture->height) / ray->line_height) / 256;
		// Toma el color de la textura en (tex_x, tex_y)
		color = get_tex_color(wall->texture, wall->tex_x, tex_y);
		// Pinta el píxel en la imagen destino
		mlx_put_pixel(game->img, x, y, color);
		y++;
	}
	// Dibujar suelo
	while (y < HEIGHT)
		mlx_put_pixel(game->img, x, y++, game->floor);
}

/* Drawing column
	Dibujar una columna sin texturas con colores planos: techo, pared y suelo */
void	draw_column(t_game *game, t_ray *ray, int x)
{
	int			y;
	uint32_t	color;

	// Techo
	y = 0;
	// Dibuja px del techo desde arriba (0) hasta donde empieza la pared
	while (y < ray->draw_start)
		mlx_put_pixel(game->img, x, y++, game->ceiling);
	// Pared (color plano distinto según el lado del impacto)
	if (ray->side == 0)
		color = 0xFF0000FF; // rojo para verticales (NS)
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

/*
init_wall
	Qué hace: prepara la info para dibujar una pared con textura en una columna.
	Cómo lo hace:
	- Elige la textura correcta con get_wall_texture según el lado golpeado y
		la dirección del rayo.
	- Calcula la coordenada exacta del impacto en la pared (wall_x en [0,1])
		con get_wall_x.
	- Convierte wall_x a una columna de la textura (tex_x).
	- Invierte la textura horizontalmente en ciertos casos para que no se vea
		del revés.
	- Nota: la segunda condición de inversión probablemente debería ser
		ray->side == 1 && ray->dir_y < 0, no ray->side == 0.

get_tex_color
	Qué hace: obtiene el color RGBA de la textura en (x, y) y lo devuelve
		como 0xRRGGBBAA.
	Cómo lo hace:
	- Comprueba límites; si (x,y) está fuera, devuelve negro opaco.
	- Calcula el índice lineal del píxel: (y * width + x) * 4.
	- Lee 4 bytes consecutivos (R, G, B, A) y los empaqueta en un entero de
		32 bits.

draw_wall
	Qué hace: dibuja la porción de pared texturizada de una columna en la
		pantalla.
	Cómo lo hace:
	- Recorre y desde draw_start hasta draw_end.
	- Usa aritmética de punto fijo (escala 256) para mapear la posición de
		pantalla a la posición vertical de la textura:
		- d = y256 - HEIGHT128 + line_height*128
		- tex_y = ((d * texture->height) / line_height) / 256
	- Toma el color de la textura en (tex_x, tex_y) y lo pinta con
		mlx_put_pixel.

draw_column
	Qué hace: dibuja una columna sin textura (solo colores planos): techo,
		pared y suelo.
	Cómo lo hace:
	- Techo: pinta desde y=0 hasta draw_start con game->ceiling.
	- Pared: pinta de draw_start a draw_end con un color que depende de
		ray->side (0 vertical NS, 1 horizontal EO).
	- Suelo: pinta desde draw_end hasta HEIGHT con game->floor.
*/