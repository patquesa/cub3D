/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:59:49 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/26 13:10:58 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//init_lines prepara el “contenedor” donde vas a guardar las líneas del mapa.
static void	init_lines(t_lines *arr)
{
	arr->v = NULL;
	arr->count = 0;
	arr->cap = 0;
	arr->maxw = 0;
}
//si no se guardó ninguna línea válida del mapa, libera para no seguir con un mapa vacio
static int	check_empty_map(t_lines *arr)
{
	if (arr->count == 0)
	{
		free_lines(arr);
		return (1);
	}
	return (0);
}

int	read_map_lines(int fd, t_lines *arr)
{
	t_parse_state	st; //estado interno del parseo

	init_lines(arr); //Prepara arr para empezar a almacenar líneas
	st.fd = fd; //de que fd leer
	st.in_map = 0; //si estamos dentro del mapa
	st.end_map = 0; //si termino
	st.line = get_next_line(fd); //linea actual
	//fprintf(stderr, "[DEBUG] FIRST LINE FROM GNL: '%s'\n", st.line);
	while (st.line != NULL) //mientras haya una linea, llamas a process_map
	{
		//fprintf(stderr, "[MAP] in_map=%d end_map=%d line='%s'\n",st.in_map, st.end_map, st.line);
		if (process_map_step(&st, arr) != 0)
		{//fprintf(stderr, "[MAP] ERROR returned by process_map_step\n");
			if (st.line)
				free(st.line);
			free_lines(arr);
			return (1);
		}
	}
	return (check_empty_map(arr)); //verificar que el mapa no este vacio
}
