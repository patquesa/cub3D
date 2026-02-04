/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:39:55 by adruz-to          #+#    #+#             */
/*   Updated: 2026/02/04 13:29:28 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Rendering function executed each frame.
	- Registered with mlx_loop_hook and automatically called by MLX in the 
	main loop.
	- Updates player state (inputs/movement) before drawing.
	- Then calls cast_ray, which traverses all columns and draws the 
	complete frame.
*/
void	render_frame(void *param)
{
	t_game		*game;
	static int	frame = 0;

	game = (t_game *)param;
	if (frame == 0)
		printf("Primer frame - Iniciando render...\n");
	update_player(game);
	if (frame == 0)
		printf("update_player OK\n");
	cast_ray(game);
	if (frame == 0)
		printf("cast_ray OK\n");
	frame++;
}
