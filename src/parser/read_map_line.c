/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:59:49 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/21 22:07:05 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

//lee todo el archivo pero saca la parte del mapa
int	read_map_lines(int fd, t_lines *arr)
{
	char	*line;
	int		in_map;

	arr->v = NULL;
	arr->count = 0;
	arr->cap = 0;
	arr->maxw = 0;

	in_map = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (!in_map && is_map_line(line))
			in_map = 1;

		if (in_map)
		{
			if (lines_push(arr, line) != 0)
				return (free(line), free_lines(arr), 1);
		}
		else
			free(line);
	}
	if (arr->count == 0)
		return (1);
	return (0);
}
