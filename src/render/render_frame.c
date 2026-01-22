/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:39:55 by adruz-to          #+#    #+#             */
/*   Updated: 2026/01/22 15:41:36 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Función de renderizado que se ejecuta en cada frame. 
	Se llama automáticamente por mlx_loop_hook*/
void	render_frame(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	cast_ray(game);
}
