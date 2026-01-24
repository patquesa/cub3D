/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:51:47 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/24 21:32:59 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Director de orquesta: coordina todo
int	parse_file(const char *filename, t_game *game)
{
	int		fd;
	t_lines	arr; //es un buffer temporal de parseo

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (1);
	if (parse_header(fd, game) != 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (1);
	if (read_map_lines(fd, &arr) != 0) //lee y guarda las lineas del mapa en arr
	{
		close(fd);
		return (1);
	}
	close(fd);
	if (build_grid(game, &arr) != 0)
	{
		free_lines(&arr);
		return (1);
	}
	free_lines(&arr);
	if (find_and_store_spawn(game) != 0)
		return (1);
	if (validate_map(game) != 0)
		return (1);
	return (0); //todo OK
}
