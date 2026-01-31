/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:17:37 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/31 14:02:45 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
static int	is_valid_cell(char c) //liberas una copia del mapa (no real)
{
	return (c == '0' || c == '1' || c == ' '); //suelo, pared, vacio
}

static void	free_grid_copy(char **g, int h) //char **g array de filas
{
	int	y; //contador de filas

	if (!g)
		return ;
	y = 0;
	while (y < h) //recorres todas las filas y las vas liberando
	{
		free(g[y]);
		y++;
	}
	free(g);
}*/

static char	**copy_grid(t_game *game) //copia del grid para no tocar el original
{
	char	**cpy; //la copia del grid
	int		y; //indice filas
	//reserva memoria para punteros a filas
	cpy = (char **)malloc(sizeof(char *) * game->map.height);
	if (!cpy)
		return (NULL);
	y = 0;
	while (y < game->map.height)
	{
		cpy[y] = ft_strdup(game->map.grid[y]); //se copia cada fila
		if (!cpy[y])
		{
			free_grid_copy(cpy, y);
			return (NULL);
		}
		y++;
	}
	return (cpy); //devuelves la copia
}

/* Devuelve 1 si detecta mapa abierto (sale o toca ' ') */
static int	flood(char **g, t_game *game, int y, int x)
{
	if (y < 0 || x < 0 || y >= game->map.height || x >= game->map.width)
		return (1);
	if (g[y][x] == ' ')
		return (1);
	if (g[y][x] == '1' || g[y][x] == 'V')
		return (0);
	if (g[y][x] != '0')
		return (1);
	g[y][x] = 'V';
	if (flood(g, game, y - 1, x))
		return (1);
	if (flood(g, game, y + 1, x))
		return (1);
	if (flood(g, game, y, x - 1))
		return (1);
	if (flood(g, game, y, x + 1))
		return (1); //mapa abierto
	return (0); //mapa cerrado
}

static int	validate_flood(t_game *game) //flood va marcando las casillas Ya visitadas, por eso necesitamos una copia (no tocar original)
{
	char	**cpy;
	int		open; //guarda si se detecto apertura

	cpy = copy_grid(game); //duplicas grid
	if (!cpy)
		return (1);
	open = flood(cpy, game, game->map.spawn_y, game->map.spawn_x); //arrancas desde la posicion del jugador
	free_grid_copy(cpy, game->map.height); //siempre liberas la copia (con/sin error)
	if (open)
		return (1); //mapa invalido
	return (0);
}

static int	is_closed_floor(t_game *g, int y, int x)
{
	if (y == 0 || x == 0 || y == g->map.height - 1 || x == g->map.width - 1) //si un 0 (suelo pisable) esta en borde, error
		return (0);
	if (g->map.grid[y - 1][x] == ' ' || g->map.grid[y + 1][x] == ' '
		|| g->map.grid[y][x - 1] == ' ' || g->map.grid[y][x + 1] == ' ')
		return (0);
	// Verificar las 4 diagonales
	if (g->map.grid[y - 1][x - 1] == ' ' || g->map.grid[y - 1][x + 1] == ' '
		|| g->map.grid[y + 1][x - 1] == ' ' || g->map.grid[y + 1][x + 1] == ' ')
		return (0); //mapa abierto (0)
	return (1); //mapa cerrado (1)
}

int	validate_map(t_game *game)
{
	int		y;
	int		x;
	char	c; //caracter en una posicion grid[y][x]

	if (!game || !game->map.grid
		|| game->map.height <= 0 || game->map.width <= 0)
		return (fail("Invalid map"));
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			c = game->map.grid[y][x];
			if (!is_valid_cell(c)) //comprueba si la celda es valida (0, 1, ' ')
				return (fail("Invalid map character"));
			if (c == '0' && !is_closed_floor(game, y, x))
				return (fail("Map is not closed"));
			x++;
		}
		y++;
	}
	if (validate_flood(game) != 0)
		return (fail("Map is not closed"));
	return (0);
}
