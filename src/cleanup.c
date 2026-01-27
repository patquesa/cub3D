/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:20:33 by adruz-to          #+#    #+#             */
/*   Updated: 2026/01/27 16:25:47 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Limpia todos los recursos de MLX y texturas. Se llama al cerrar el programa
 */
void	cleanup_game(t_game *game)
{
	free_textures(game); // Liberar texturas
	// Liberar imagen MLX
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	// Terminar MLX
	if (game->img)
		mlx_terminate(game->mlx);
	// TODO: free del mapa
	// free_map(&game->map);
}
