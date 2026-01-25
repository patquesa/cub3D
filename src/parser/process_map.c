/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:56:22 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/25 20:25:46 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
//Se encarga de ignorar líneas antes del mapa (cabecera)
static int	handle_until_map(int *in_map, const char *line)
{
	if (*in_map)
		return (0);
	if (is_blank_line(line))
		return (1);
	if (is_map_row(line))   // <-- IMPORTANTE: row, no line
	{
		*in_map = 1;
		return (0);
	}
	return (1); // cabecera/ruido antes del mapa: se ignora
}
static int	handle_map_body(t_lines *arr, char *line, int *end_map, int *consumed)
{
	*consumed = 0;

	if (is_blank_line(line))
	{
		//fprintf(stderr, "[MAP] blank => end_map=1\n");
		*end_map = 1;
		return (0); //no se guarda
	}
	if (is_map_row(line) == 0)
	{
		//fprintf(stderr, "[MAP] INVALID map row: '%s'\n", line);
		free_lines(arr);
		return (1);
	}
	if (lines_push(arr, line) != 0)
	{
		free_lines(arr);
		return (1);
	}
	*consumed = 1; // arr se queda con line
	return (0);
}

//despues del mapa, solo es valido lineas en blanco, cualquier otra cosa seria un error
static int	handle_after_map(t_lines *arr, char *line)
{
	if (is_blank_line(line) == 0)
	{
		//fprintf(stderr, "[MAP] NON-blank after map: '%s'\n", line);
		//free(line);
		free_lines(arr);
		return (1);
	}
	//fprintf(stderr, "[MAP] blank after map (ok)\n");
	//free(line); //lineas en blanco post al mapa, se ignoran
	return (0);
}

//analisis de las lineas antes, durante y tras el mapa
int	process_map_step(t_parse_state *st, t_lines *arr)
{
	int	consumed;

	if (!st->line)
		return (0);

	/* ANTES DEL MAPA */
	if (handle_until_map(&st->in_map, st->line))
	{
		free(st->line);
		st->line = get_next_line(st->fd);
		return (0);
	}

	/* DURANTE / DESPUÉS DEL MAPA */
	if (st->end_map == 0)
	{
		if (handle_map_body(arr, st->line, &st->end_map, &consumed) != 0)
		{
			free(st->line);
			st->line = NULL;
			return (1);
		}
		/*if (!consumed)          // no se guardó en arr (blank)
			free(st->line);*/
		if (consumed)
			st->line = NULL;   /* arr ya es dueño de la línea */
		else
			free(st->line);
	}
	else
	{
		if (handle_after_map(arr, st->line) != 0)
		{
			free(st->line);
			st->line = NULL;
			return (1);
		}
		free(st->line);
	}

	st->line = get_next_line(st->fd);
	return (0);
}

