/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:55:48 by patquesa          #+#    #+#             */
/*   Updated: 2026/02/03 12:36:35 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Devuelve 1 si la línea contiene solo " 01NSEW" (hasta \n) y tiene al menos un '1' */
/* int	is_map_line(const char *s)
{
	int	i;
	int	has_wall;

	if (!s)
		return (0);
	i = 0;
	has_wall = 0;
	while (s[i] && s[i] != '\n')
	{
		if (s[i] == '1')
			has_wall = 1;
		else if (s[i] == '0' || s[i] == 'N' || s[i] == 'S'
			|| s[i] == 'E' || s[i] == 'W' || s[i] == ' ')
			;
		else
			return (0);
		i++;
	}
	return (has_wall);
} */

//si linea en blanco
int	is_blank_line(const char *s)
{
	int	i;

	if (!s) //Si s es NULL, la consideramos vacía por seguridad.
		return (1);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\r')
			return (0);
		i++;
	}
	return (1); //si hay lineas vacias o de solo tabuladores por ej
}

//comprueba si una linea del archivo es una linea valida del mapa
int	is_map_row(const char *s) //puede contener: 0, 1. N, S, E, W, (' '), ('\t'), o retorno//Debe contener al menos un carácter útil del mapa: '0', '1', 'N', 'S', 'E', 'W' (cell)
{
	int	i;
	int	has_cell;

	if (!s)
		return (0);
	i = 0;
	has_cell = 0;
	while (s[i] && s[i] != '\n')
	{
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\r')
			;
		else if (s[i] == '0' || s[i] == '1'
			|| s[i] == 'N' || s[i] == 'S' || s[i] == 'E' || s[i] == 'W')
			has_cell = 1;
		else
			return (0);
		i++;
	}
	return (has_cell);
}

int	is_valid_cell(char c) //liberas una copia del mapa (no real)
{
	return (c == '0' || c == '1' || c == ' '); //suelo, pared, vacio
}

void	free_grid_copy(char **g, int h) //char **g array de filas
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
}