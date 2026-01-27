/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_spawn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:28:38 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/27 11:50:29 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_spawn(char c)
{ //posicion inicial del jugador
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
} //esa posicion sera reemplazada despues por suelo (0)

static void	store_spawn(t_game *game, int x, int y)
{
	game->map.spawn_x = x;
	game->map.spawn_y = y;
	game->map.spawn_dir = game->map.grid[y][x];
	game->map.grid[y][x] = '0';
}

int	find_and_store_spawn(t_game *game)  //encontrar al jugador
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
			if (is_spawn(game->map.grid[y][x]) && ++count == 1) //con ++count solo entra en store_spawn si count == 1 (es decir solo un jugador)
			{   //guardas la posicion inicial (q no debe perderse) //guardas las coordenadas (es direccion spawn_dir)
				store_spawn(game, x, y); //conviertes a suelo '0'  //raycast tratara spawn como suelo
			}
			x++;
		}
		y++;
	}
	if (count != 1) // si hay 0 o mas de un spawn, error
		return (1);
	return (0); //lo correcto, un solo spawn
}
