/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:56:22 by patquesa          #+#    #+#             */
/*   Updated: 2026/02/03 19:34:21 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//ignora lineas anteriores al mapa
/* Handle lines before the map starts (skip blanks, detect first map row) */
static int	handle_until_map(int *in_map, const char *line)
{
	if (*in_map)
		return (0);
	if (is_blank_line(line))
		return (1);
	if (is_map_row(line))
	{
		*in_map = 1;
		return (0);
	}
	return (1); //cabecera antes del mapa se ignora
}

/* Handle map body lines (store valid rows, detect end) */
static int	handle_map_body(t_lines *arr, char **line, int *end_map)
{
	if (is_blank_line(*line))
	{
		*end_map = 1;
		free(*line);
		return (0);
	}
	if (is_map_row(*line) == 0)
	{
		free(*line);
		free_lines(arr);
		return (fail("Invalid map line"));
	}
	if (lines_push(arr, *line) != 0)
	{
		free(*line);
		free_lines(arr);
		return (1);
	}
	*line = NULL;
	return (0);
}

//despues del mapa, solo es valido lineas en blanco, cualquier otra cosa seria un error
/* Handle lines after the map ends (only blanks allowed) */
static int	handle_after_map(t_lines *arr, char **line)
{
	if (is_blank_line(*line) == 0)
	{
		free(*line);
		free_lines(arr);
		return (fail("Invalid map line"));
	}
	free(*line);
	return (0);
}

//analisis de las lineas antes, durante y tras el mapa
/* Process one step of map parsing (state machine) */
int	process_map_step(t_parse_state *st, t_lines *arr)
{
	int	ret;

	if (!st->line)
		return (0);
	if (handle_until_map(&st->in_map, st->line))
	{
		free(st->line);
		st->line = get_next_line(st->fd);
		return (0);
	}
	if (st->end_map == 0)
		ret = handle_map_body(arr, &st->line, &st->end_map);
	else
		ret = handle_after_map(arr, &st->line);
	if (ret != 0)
	{
		st->line = NULL;
		return (1);
	}
	st->line = get_next_line(st->fd);
	return (0);
}
