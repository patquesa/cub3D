/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:01:04 by adruz-to          #+#    #+#             */
/*   Updated: 2026/02/04 13:25:56 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Initialize wall information to draw (textured) for a column.
	- Selects the correct texture (N,S,E,W) based on the hit side and 
	ray direction
*/
t_wall	init_wall(t_game *game, t_ray *ray)
{
	t_wall	wall;

	wall.texture = get_wall_texture(game, ray);
	wall.wall_x = get_wall_x(game, ray);
	wall.wall_x -= floor(wall.wall_x);
	wall.tex_x = (int)(wall.wall_x * wall.texture->width);
	if (ray->side == 0 && ray->dir_x > 0)
		wall.tex_x = wall.texture->width - wall.tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		wall.tex_x = wall.texture->width - wall.tex_x - 1;
	if (wall.tex_x < 0)
		wall.tex_x = 0;
	if (wall.tex_x >= (int)wall.texture->width)
		wall.tex_x = (int)wall.texture->width - 1;
	return (wall);
}

/* Read RGBA color from texture at (x, y) and return it packed as 0xRRGGBBAA */
uint32_t	get_tex_color(mlx_texture_t *texture, int x, int y)
{
	int	index;

	if (x < 0 || x >= (int)texture->width || y < 0 || y >= (int)texture->height)
		return (0x000000FF);
	index = (y * texture->width + x) * 4;
	return ((texture->pixels[index] << 24)
		| (texture->pixels[index + 1] << 16)
		| (texture->pixels[index + 2] << 8)
		| texture->pixels[index + 3]);
}

/* Draw the textured wall section for a screen column at x */
void	draw_wall(t_game *game, t_ray *ray, t_wall *wall, int x)
{
	int			y;
	uint32_t	color;
	int			d;
	int			tex_y;

	y = 0;
	while (y < ray->draw_start)
		mlx_put_pixel(game->img, x, y++, game->ceiling);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		d = y * 256 - HEIGHT * 128 + ray->line_height * 128;
		tex_y = ((d * wall->texture->height) / ray->line_height) / 256;
		color = get_tex_color(wall->texture, wall->tex_x, tex_y);
		mlx_put_pixel(game->img, x, y, color);
		y++;
	}
	while (y < HEIGHT)
		mlx_put_pixel(game->img, x, y++, game->floor);
}

/* Draw a column without textures using flat colors: ceiling, wall and floor */
void	draw_column(t_game *game, t_ray *ray, int x)
{
	int			y;
	uint32_t	color;

	y = 0;
	while (y < ray->draw_start)
		mlx_put_pixel(game->img, x, y++, game->ceiling);
	if (ray->side == 0)
		color = 0xFF0000FF;
	else
		color = 0x800000FF;
	while (y < ray->draw_end)
		mlx_put_pixel(game->img, x, y++, color);
	while (y < HEIGHT)
		mlx_put_pixel(game->img, x, y++, game->floor);
}
