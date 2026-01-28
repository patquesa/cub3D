/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:03:07 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/24 19:03:21 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//calculas la longitud de la linea (sin \n)
static int	line_len_no_nl(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n' && s[i] != '\r')
		i++;
	return (i);
}

//Cuando estás construyendo el grid y algo falla a mitad
static int	row_malloc_error(t_game *game, int y)
{
	int	i;

	i = 0;
	while (i < y)
	{
		free(game->map.grid[i]); //liberas cada linea reservada
		i++;
	}
	free(game->map.grid); //liberas el array de punteros
	game->map.grid = NULL; //reseteas
	game->map.width = 0;
	game->map.height = 0;
	return (1);
}


//Esta función copia una línea del mapa original al grid final, normalizando caracteres y rellenando para q sea rectangular
static void	fill_grid_row(t_game *game, t_lines *arr, int y)
{
	int		x;
	int		len;
	char	c;

	len = line_len_no_nl(arr->v[y]);
	x = 0;
	while (x < game->map.width) //Recorres todas las columnas del mapa (para q sea rectangular)
	{
		if (x < len)
		{
			c = arr->v[y][x]; //copias caracter original
			if (c == '\t' || c == '\r') //si es raro, lo sustituyes por espacios
				c = ' ';
			game->map.grid[y][x] = c; //Copias el carácter en la misma posición (y, x) del grid final.
		}
		else //si La línea original era más corta que el ancho máximo del mapa
			game->map.grid[y][x] = ' '; //rellenas con espacios
		x++;
	}
	game->map.grid[y][game->map.width] = '\0';
}

int	build_grid(t_game *game, t_lines *arr) //construye el mapa final grid (rectangular)
{
	int	y;

	if (arr->count <= 0 || arr->maxw <= 0)
		return (1);
	game->map.height = arr->count;//fijamos dimensiones mapa (total lineas y ancho como linea mas ancha)
	game->map.width = arr->maxw; //ANCHO COINCIDE CON LA LINEA MAS LARGA ENCONTRADA (MAPA RECTANGULAR)
	game->map.grid = (char **)malloc(sizeof(char *) * (game->map.height + 1));//reserva memoria para array punteros a filas
	if (!game->map.grid)
		return (1);
	y = 0;
	while (y < game->map.height) //recorres todas las filas y reservas memoria para cada una de las filas
	{
		game->map.grid[y] = (char *)malloc(game->map.width + 1);//
		if (!game->map.grid[y])
			return (row_malloc_error(game, y));
		fill_grid_row(game, arr, y); //copiamos cada linea al grid final
		y++;
	}
	game->map.grid[game->map.height] = NULL; //cerramos array de punteros (se reservo memoria +1)
	return (0);
}
