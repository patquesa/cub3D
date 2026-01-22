/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_spawn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:28:38 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/22 21:38:16 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_spawn(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	find_and_store_spawn(t_game *game)  //encontrar al jugador
{
	int	x;
	int	y;
	int	count; //cuantos spawn se han encontrado

	count = 0;
	y = 0;
	while (y < game->map.height) //recorres todas filas
	{
		x = 0;
		while (x < game->map.width) //recorres todas columnas
		{
			if (is_spawn(game->map.grid[y][x])) //si encuentras N S E W
			{   //guardas la posicion inicial (q no debe perderse)
				game->map.spawn_x = x;
				game->map.spawn_y = y;
				game->map.spawn_dir = game->map.grid[y][x];
				game->map.grid[y][x] = '0'; //conviertes a sueo '0' (para que validate_map no tenga q aceptar NSEW)
				count++;                    //raycast tratara spawn como suelo
			}
			x++;
		}
		y++;
	}
	if (count != 1)
    	return (1);
	return (0); //correcto un solo spawn
}
