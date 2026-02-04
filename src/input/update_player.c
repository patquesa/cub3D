/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:22:00 by adruz-to          #+#    #+#             */
/*   Updated: 2026/02/04 11:52:35 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Comprueba si una celda del mapa es transitable (no es pared '1')
	Protege contra salirse del mapa y contra las paredes  */
/* Check if a map cell is walkable (not a wall '1')
	Protects against going out of bounds and hitting walls */
static int	is_walkable(t_map *map, double x, double y)
{
	const double	margin = 0.2; // margen para no pegarse a las paredes
	int				cx[4]; // array para guardar las coordenadas de las 4 esquinas
	int				cy[4];
	int 			i; // índice para recorrer las esquinas

	cx[0] = (int)(x + margin); // Esquina superior derecha
	cy[0] = (int)(y + margin);
	cx[1] = (int)(x - margin); // Esquina superior izquierda
	cy[1] = (int)(y + margin);
	cx[2] = (int)(x - margin); // Esquina inferior izquierda
	cy[2] = (int)(y - margin);
	cx[3] = (int)(x + margin); // Esquina inferior derecha
	cy[3] = (int)(y - margin);

	i = 0; // Inicializamos para recorrer las 4 esquinas
	while (i < 4)
	{
		// Comprobamos que la esquina no se salga de los límites del mapa
		if (cx[i] < 0 || cy[i] < 0 || cx[i] >= map->width
			|| cy[i] >= map->height)
			return (0);
		// Si la esquina cae en una pared (1), no se puede caminar
		if (map->grid[cy[i]][cx[i]] == '1')
			return (0);
		i++;
	}
	return (1);
}


/* Movimiento hacia adelante hacia atrás (Teclas W/S) */
/* Forward and backward movement (W/S keys) */
static void	move_forward_backward(t_game *game, double move)
{
	double		nx;
	double		ny;
	t_player	*p;

	p = &game->player;
	// Avanza
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		// Calculamos la nueva posición potencial según la dirección del jugador
		nx = p->x + p->dir_x * move;
		ny = p->y + p->dir_y * move;
		// Solo actualizamos X si es transitable
		if (is_walkable(&game->map, nx, p->y))
			p->x = nx;
		// Solo actualizamos Y si es transitable
		if (is_walkable(&game->map, p->x, ny))
			p->y = ny;
	}
	// Retrocede
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

/* Movimiento lateral (strafe) con las teclas A/D */
/* Lateral movement (strafe) with A/D keys */
static void	strafe(t_game *game, double move)
{
	double		nx;
	double		ny;
	t_player	*p;

	p = &game->player;
	// Izquierda
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		// Calculamos desplazamiento perpendicular a la dirección (plano cámara)
		nx = p->x - p->plane_x * move;
		ny = p->y - p->plane_y * move;
		if (is_walkable(&game->map, nx, p->y))
			p->x = nx;
		if (is_walkable(&game->map, p->x, ny))
			p->y = ny;
	}
	// Derecha
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

/* Rotación del jugador (Left/Right o teclas Q/E)
	- dir_x/y es dirección dónde mira el jugador
	- plane_x/y plano de cámara, define el punto de vista FOV */
/* Player rotation (Left/Right or Q/E keys)
	- dir_x/y is the direction where the player looks
	- plane_x/y camera plane, defines the FOV viewpoint */
static void	rotate(t_game *game, double rot)
{
	double		old_dir_x;
	double		old_plane_x;
	t_player	*p;

	p = &game->player;
	// Rotación a la izquierda
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT) || mlx_is_key_down(game->mlx,
			MLX_KEY_Q))
	{
		// Guardamos el valor original de dir_x para recalcular dir_y
		old_dir_x = p->dir_x;
		// un ángulo negativo (-rot) gira a la izquierda
		// cos() nos da la coordenada X
		// sin() nos da la coordenada Y
		p->dir_x = p->dir_x * cos(-rot) - p->dir_y * sin(-rot);
		p->dir_y = old_dir_x * sin(-rot) + p->dir_y * cos(-rot);
		// Guardamos el valor original del plano para rotar el plano de la cámara
		old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(-rot) - p->plane_y * sin(-rot);
		p->plane_y = old_plane_x * sin(-rot) + p->plane_y * cos(-rot);
	}
	// Rotación a la derecha
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT) || mlx_is_key_down(game->mlx,
			MLX_KEY_E))
	{
		old_dir_x = p->dir_x;
		// un ángulo positivo (rot) gira a la derecha
		p->dir_x = p->dir_x * cos(rot) - p->dir_y * sin(rot);
		p->dir_y = old_dir_x * sin(rot) + p->dir_y * cos(rot);
		old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(rot) - p->plane_y * sin(rot);
		p->plane_y = old_plane_x * sin(rot) + p->plane_y * cos(rot);
	}
}

/* Función principal de actualización del jugador. Llama a avance/retroceso,
	strafe y rotación en cada frame */
/* Main player update function. Calls forward/backward, strafe and rotation 
each frame */
void	update_player(t_game *game)
{
	double move; // velocidad de movimiento
	double rot;  // velocidad de rotación

	// Movimiento constante de 3 unidades por segundo
	move = 3.0 * game->mlx->delta_time;
	// Rotación constante de 2 radianes por segundo
	rot = 2.0 * game->mlx->delta_time;
	
	move_forward_backward(game, move);
	strafe(game, move);
	rotate(game, rot);
}
