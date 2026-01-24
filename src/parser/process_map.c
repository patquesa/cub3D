/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:56:22 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/24 18:24:26 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
//Se encarga de ignorar líneas antes del mapa (cabecera)
static int	handle_until_map(int *in_map, char **line, int fd)
{
	if (*in_map == 1) //estoy dentro del mapa, no hago nada
		return (0);
	if (is_map_line(*line)) //estaba fuera pero encuentro una linea del mapa, lo marco
	{
		*in_map = 1;
		return (0);
	}
	free(*line); //no he llegado al mapa, sigo leyendo...
	*line = get_next_line(fd);
	return (1);
}
//Procesa una línea mientras el mapa no ha terminado (end_map == 0)
static int	handle_map_body(t_lines *arr, char *line, int *end_map)
{
	if (is_blank_line(line))
	{
		*end_map = 1; //marca q ha terminado el mapa
		free(line);
		return (0);
	}
	if (is_map_row(line) == 0) //comprueba si la linea es valida (si es valida devuelve has_cell)
	{
		free(line); 
		free_lines(arr);
		return (1);
	}
	if (lines_push(arr, line) != 0) //guarda la linea valida
	{
		free(line); //si falla push (malloc), limpias
		free_lines(arr);
		return (1);
	}
	return (0);
}
//despues del mapa, solo es valido lineas en blanco, cualquier otra cosa seria un error
static int	handle_after_map(t_lines *arr, char *line)
{
	if (is_blank_line(line) == 0)
	{
		free(line);
		free_lines(arr);
		return (1);
	}
	free(line); //lineas en blanco post al mapa, se ignoran
	return (0);
}
//analisis de las lineas antes, durante y tras el mapa
int	process_map_step(t_parse_state *st, t_lines *arr)
{
	if (handle_until_map(&st->in_map, &st->line, st->fd))
		return (0);
	if (st->end_map == 0)
	{
		if (handle_map_body(arr, st->line, &st->end_map) != 0)
			return (1);
		if (st->end_map == 1)
		{
			st->line = get_next_line(st->fd);
			return (0);
		}
	}
	else
	{
		if (handle_after_map(arr, st->line) != 0)
			return (1);
	}
	st->line = get_next_line(st->fd);
	return (0);
}
