/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:51:47 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/22 18:59:50 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//funcion que coordina todo
int	parse_file(const char *filename, t_game *game)
{
	int		fd;
	t_lines	arr; //es un buffer temporal de parseo

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (1);

	if (read_map_lines(fd, &arr) != 0)
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

/*
#include "cub3d.h"

int	parse_file(const char *filename, t_game *game)
{
    int		fd;
    t_lines	arr;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (write(2, "Error: cannot open file\n", 24), 1);

    if (read_map_lines(fd, &arr) != 0)
        return (close(fd), write(2, "Error: read_map_lines failed\n", 29), 1);
    close(fd);
    
    write(1, "read_map_lines OK\n", 18);

    if (build_grid(game, &arr) != 0)
        return (free_lines(&arr), write(2, "Error: build_grid failed\n", 25), 1);
    
    write(1, "build_grid OK\n", 14);
    free_lines(&arr);

    if (find_and_store_spawn(game) != 0)
        return (write(2, "Error: find_and_store_spawn failed\n", 35), 1);

    write(1, "parse_file OK\n", 14);
    return (0);
}
*/