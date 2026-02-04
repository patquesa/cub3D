/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:59:49 by patquesa          #+#    #+#             */
/*   Updated: 2026/02/04 13:13:56 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Initialize the t_lines structure */
static void	init_lines(t_lines *arr)
{
	arr->v = NULL;
	arr->count = 0;
	arr->cap = 0;
	arr->maxw = 0;
}

/* Check if the map is empty and return an error if so */
static int	check_empty_map(t_lines *arr)
{
	if (arr->count == 0)
	{
		free_lines(arr);
		return (fail("Map is empty"));
	}
	return (0);
}

/* Read and store all map lines from the file */
int	read_map_lines(int fd, t_lines *arr)
{
	t_parse_state	st;

	init_lines(arr);
	st.fd = fd;
	st.in_map = 0;
	st.end_map = 0;
	st.line = get_next_line(fd);
	while (st.line != NULL)
	{
		if (process_map_step(&st, arr) != 0)
		{
			if (st.line)
				free(st.line);
			free_lines(arr);
			return (1);
		}
	}
	return (check_empty_map(arr));
}
