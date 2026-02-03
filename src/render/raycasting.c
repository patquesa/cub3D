/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:49:45 by adruz-to          #+#    #+#             */
/*   Updated: 2026/02/03 17:37:07 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Calculate ray direction
	- camera_x maps the column [0..WIDTH) to the camera plane [-1..1].
	- dir_x/dir_y combine player direction and plane (FOV) to get the ray 
	direction in the world.
	- map_x/map_y is the map cell where the player is when the ray starts.
	- delta_dist_x/delta_dist_y are the distances the ray advances when 
	crossing a grid line in X or Y (used by DDA).
	- hit is initialized to 0 and DDA will set it to 1 when a wall is found.
*/
void	init_ray(t_ray *ray, t_game *game, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
}

/* Cast and process all rays from player position:
- Calculate direction of each ray
- Detect wall collisions
- Calculate distances

Logic:
- Loop through each pixel column (ray) on screen
- DDA algorithm or similar to detect walls
- Calculate perpendicular distances
*/
void	cast_ray(t_game *game)
{
	int		x;
	t_ray	ray;
	t_wall	wall;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(&ray, game, x);
		perform_dda(&ray, game);
		calculate_wall_height(&ray);
		if (game->textures.north && game->textures.south && game->textures.east
			&& game->textures.west)
		{
			wall = init_wall(game, &ray);
			draw_wall(game, &ray, &wall, x);
		}
		else
			draw_column(game, &ray, x);
		x++;
	}
}
