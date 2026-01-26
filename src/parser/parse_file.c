/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:51:47 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/26 13:10:31 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_only_header(const char *filename, t_game *game)
{
	int	fd;

	fd = open(filename, O_RDONLY);

	if (fd < 0)
		return (1);
	if (parse_header(fd, game) != 0)
	{
		gnl_reset(fd);
		close(fd);
		return (1);
	}
	gnl_reset(fd);
	close(fd);
	return (0);
}

static int	parse_only_map_lines(const char *filename, t_lines *arr)
{
	int	fd;

	fd = open(filename, O_RDONLY);

	if (fd < 0)
		return (1);
	if (read_map_lines(fd, arr) != 0) //lee y guarda las lineas del mapa en arr
	{
		gnl_reset(fd);
		close(fd);
		return (1);
	}
	gnl_reset(fd);
	close(fd);
	return (0);
}

//Director de orquesta: coordina todo
int	parse_file(const char *filename, t_game *game)
{
	t_lines	arr; //es un buffer temporal de parseo

	if (parse_only_header(filename, game) != 0)
		return (1);
	if (parse_only_map_lines(filename, &arr) != 0)
		return (1);
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
	return (0); //todo ok
}

