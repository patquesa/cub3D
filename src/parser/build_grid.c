/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:03:07 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/22 21:07:57 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	line_len_no_nl(const char *s)
{
	int i = 0;
	while (s[i] && s[i] != '\n' && s[i] != '\r')
		i++;
	return (i);
}

static void	free_partial_grid(char **grid, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

//pasar la lista a una matriz rectangular
int	build_grid(t_game *game, t_lines *arr)
{
	int		y; //fila
	int		x; //columna
	int		len; //len linea
	char	c;
//estas dos primeras lineas fijan tamaño del grid
	game->map.height = arr->count;
	game->map.width = arr->maxw; // significa:todas las filas del grid tendrán exactax maxw columnas
	game->map.grid = (char **)malloc(sizeof(char *) * game->map.height);
	if (!game->map.grid) //reserva memoria para array punteros
		return (1);
	y = 0;
	while (y < game->map.height)
	{
		game->map.grid[y] = (char *)malloc(game->map.width + 1);
		if (!game->map.grid[y])
		{
			free_partial_grid(game->map.grid, y); //Libera lo que ya habías reservado (evita leaks)
			game->map.grid = NULL;
			game->map.width = 0; //reseteas dimensiones mapa
			game->map.height = 0;
			return (1);
		}
		len = line_len_no_nl(arr->v[y]); //longitud de la linea mapa (sin \n)
		x = 0;
		while (x < game->map.width)
		{
			if (x < len) //si no hemos llegado al final de la anchura
			{
				c = arr->v[y][x]; //copias el caracter del mapa en esa posicion
				if (c == '\t' || c == '\r') //si aparece tab o \r
					c = ' ';   //lo conviertes en espacio
				game->map.grid[y][x] = c; //guardas el caracter en el grid (mapa definitivo)
			}
			else
				game->map.grid[y][x] = ' '; //rellena con espacios ' ' donde falten caracteres
			x++;
		}
		game->map.grid[y][game->map.width] = '\0'; //cerramos la fila con \0
		y++;
	}
	return (0);
}
