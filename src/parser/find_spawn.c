/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_spawn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:28:38 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/31 18:54:58 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_spawn(char c)
{
	//posicion inicial del jugador
	//esa posicion sera reemplazada despues por suelo (0)
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	store_spawn(t_game *game, int x, int y)
{
	game->map.spawn_x = x;
	game->map.spawn_y = y;
	game->map.spawn_dir = game->map.grid[y][x];
	game->map.grid[y][x] = '0';
}

/* Encontrar al jugador */
int	find_and_store_spawn(t_game *game)
{
	int	x;
	int	y;
	int	count; //contador de spawn (solo debe haber 1)

	count = 0;
	y = 0;
	while (y < game->map.height) //recorres todas filas
	{
		x = 0;
		while (x < game->map.width) //recorres todas columnas
		{
			// con ++count solo entra en store_spawn 
			// si count == 1 (es decir solo un jugador)
			if (is_spawn(game->map.grid[y][x]) && ++count == 1)
			{
				//guardas la posicion inicial (q no debe perderse)
				//guardas las coordenadas (es direccion spawn_dir)
				store_spawn(game, x, y); //conviertes a suelo '0'  //raycast tratara spawn como suelo
			}
			x++;
		}
		y++;
	}
	if (count != 1) // si hay 0 o mas de un spawn, error
		return (fail("Invalid player spawn"));
	return (0); //lo correcto, un solo spawn
}
