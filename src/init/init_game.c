/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:52:20 by adruz-to          #+#    #+#             */
/*   Updated: 2026/01/26 13:08:33 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

/* Reserva memoria para el grid del mapa */
static void	allocate_map_memory(t_game *game)
{
	int i;

	game->map.width = 8;
	game->map.height = 8;
	// Reserva memoria para el mapa
	game->map.grid = malloc(sizeof(char *) * game->map.height);
	i = 0;
	while (i < game->map.height)
	{
		game->map.grid[i] = malloc(sizeof(char) * game->map.width);
		i++;
	}
}

/* Inicializa el mapa temporal hardcodeado para pruebas
	1 pared
	0 espacio vacío

	Mapa de prueba (vista desde arriba)
	1 1 1 1 1 1 1 1
	1 0 0 0 0 0 0 1
	1 0 0 0 0 0 0 1
	1 0 0 0 0 0 0 1
	1 0 0 0 0 0 0 1
	1 0 0 0 0 0 0 1
	1 0 0 0 0 0 0 1
	1 1 1 1 1 1 1 1

*/
static void	init_map(t_game *game)
{
	int	y;
	int	x;

	allocate_map_memory(game);
	// Rellena el mapa
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (x == 0 || x == game->map.width - 1 || y == 0
				|| y == game->map.height - 1)
				game->map.grid[y][x] = '1'; // paredes exteriores
			else
				game->map.grid[y][x] = '0'; // espacio vacío
			x++;
		}
		game->map.grid[y][x] = '\0'; // Terminar la cadena
		y++;
	}
}

/* Inicializa la posición y orientación del jugador */
static void	init_player(t_game *game)
{
	// Posición inicial en el centro del mapa
	game->player.x = 4.5;
	game->player.y = 4.5;

	// Dirección inicial: mirando hacia el norte (arriba)
	game->player.dir_x = 0.0;
	game->player.dir_y = -1.0;

	// Plano de la cámara (perpendicular a la dirección)
	// Define el campo de visión (FOV)
	game->player.plane_x = 0.66; // FOV de ~66 grados
	game->player.plane_y = 0.0;
}

/* Inicializa los colores del techo y suelo */
static void	init_colors(t_game *game)
{
	// Formato: 0xRRGGBBAA
	game->ceiling = 0x87CEEBFF; // Azul cielo
	game->floor = 0x8B4513FF; // Marrón tierra
}

/* Inicializa todos los componentes del juego */
void	init_game(t_game *game)
{
	init_map(game);
	init_player(game);
	init_colors(game);
}
