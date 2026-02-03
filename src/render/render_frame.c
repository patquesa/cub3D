/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:39:55 by adruz-to          #+#    #+#             */
/*   Updated: 2026/02/03 19:40:40 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Función de renderizado que se ejecuta en cada frame.
	- Se registra con mlx_loop_hook y MLX la invoca automáticamente en el bucle
		principal.
	- Aquí puedes actualizar el estado del jugador (inputs/movimiento) antes de
		dibujar.
	- Después se llama a cast_ray, que recorre todas las columnas y dibuja el
		frame completo.
*/
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
	static int	frame = 0; // TODO Borrar debug!!

	// El hook de MLX pasa el puntero al estado global del juego vía param
	game = (t_game *)param;
	if (frame == 0)
		printf("Primer frame - Iniciando render...\n");
	// Actualiza el movimiento continuo del jugador si lo necesitas (opcional)
	// Recomendación: implementar colisión para evitar atravesar paredes
	update_player(game);
	if (frame == 0)
		printf("update_player OK\n");
	// Laza el pipeline de raycasting:
	// - Para cada columna: init_ray -> perform_dda -> calculate_wall_height
	// - Dibuja textura si están cargadas; si no, color plano con draw_column
	cast_ray(game);
	if (frame == 0)
		printf("cast_ray OK\n");
	frame++;
}
