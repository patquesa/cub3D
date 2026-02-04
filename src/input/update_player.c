/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:22:00 by adruz-to          #+#    #+#             */
/*   Updated: 2026/02/04 12:32:08 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Check if a map cell is walkable (not a wall '1')
	Protects against going out of bounds and hitting walls */
static int	is_walkable(t_map *map, double x, double y)
{
	const double	margin = 0.2;
	int				cx[4];
	int				cy[4];
	int				i;

	cx[0] = (int)(x + margin);
	cy[0] = (int)(y + margin);
	cx[1] = (int)(x - margin);
	cy[1] = (int)(y + margin);
	cx[2] = (int)(x - margin);
	cy[2] = (int)(y - margin);
	cx[3] = (int)(x + margin);
	cy[3] = (int)(y - margin);
	i = 0;
	while (i < 4)
	{
		if (cx[i] < 0 || cy[i] < 0 || cx[i] >= map->width
			|| cy[i] >= map->height)
			return (0);
		if (map->grid[cy[i]][cx[i]] == '1')
			return (0);
		i++;
	}
	return (1);
}

/* Forward and backward movement (W/S keys) */
static void	move_forward_backward(t_game *game, double move)
{
	double		nx;
	double		ny;
	t_player	*p;

	p = &game->player;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		nx = p->x + p->dir_x * move;
		ny = p->y + p->dir_y * move;
		if (is_walkable(&game->map, nx, p->y))
			p->x = nx;
		if (is_walkable(&game->map, p->x, ny))
			p->y = ny;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		nx = p->x - p->dir_x * move;
		ny = p->y - p->dir_y * move;
		if (is_walkable(&game->map, nx, p->y))
			p->x = nx;
		if (is_walkable(&game->map, p->x, ny))
			p->y = ny;
	}
}

/* Lateral movement (strafe) with A/D keys */
static void	strafe(t_game *game, double move)
{
	double		nx;
	double		ny;
	t_player	*p;

	p = &game->player;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		nx = p->x - p->plane_x * move;
		ny = p->y - p->plane_y * move;
		if (is_walkable(&game->map, nx, p->y))
			p->x = nx;
		if (is_walkable(&game->map, p->x, ny))
			p->y = ny;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		nx = p->x + p->plane_x * move;
		ny = p->y + p->plane_y * move;
		if (is_walkable(&game->map, nx, p->y))
			p->x = nx;
		if (is_walkable(&game->map, p->x, ny))
			p->y = ny;
	}
}

/* Player rotation (Left/Right or Q/E keys)
	- dir_x/y is the direction where the player looks
	- plane_x/y camera plane, defines the FOV viewpoint */
static void	rotate(t_game *game, double rot)
{
	double		old_dir_x;
	double		old_plane_x;
	t_player	*p;

	p = &game->player;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT) || mlx_is_key_down(game->mlx,
			MLX_KEY_Q))
	{
		old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(-rot) - p->dir_y * sin(-rot);
		p->dir_y = old_dir_x * sin(-rot) + p->dir_y * cos(-rot);
		old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(-rot) - p->plane_y * sin(-rot);
		p->plane_y = old_plane_x * sin(-rot) + p->plane_y * cos(-rot);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT) || mlx_is_key_down(game->mlx,
			MLX_KEY_E))
	{
		old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(rot) - p->dir_y * sin(rot);
		p->dir_y = old_dir_x * sin(rot) + p->dir_y * cos(rot);
		old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(rot) - p->plane_y * sin(rot);
		p->plane_y = old_plane_x * sin(rot) + p->plane_y * cos(rot);
	}
}

/* Main player update function. Calls forward/backward, strafe and rotation 
each frame */
void	update_player(t_game *game)
{
	double	move;
	double	rot;

	move = 3.0 * game->mlx->delta_time;
	rot = 2.0 * game->mlx->delta_time;
	move_forward_backward(game, move);
	strafe(game, move);
	rotate(game, rot);
}
