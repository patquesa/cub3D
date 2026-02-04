/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:53:56 by patquesa          #+#    #+#             */
/*   Updated: 2026/02/04 12:52:04 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Check if all header elements are present */
static int	header_complete(t_game *g)
{
	return (g->cfg.north && g->cfg.south
		&& g->cfg.east && g->cfg.west
		&& g->cfg.floor_set && g->cfg.ceiling_set);
}

/* Free line and return value */
static int	free_and_return(char *line, int ret)
{
	free(line);
	return (ret);
}

/* Process one step of header parsing */
static int	process_header_step(int fd, t_game *game, char **raw)
{
	char	*line;

	if (is_blank_line(*raw))
	{
		free(*raw);
		*raw = get_next_line(fd);
		return (0);
	}
	line = ft_strtrim(*raw, " \t\r\n");
	free(*raw);
	*raw = NULL;
	if (!line)
		return (1);
	if (is_map_row(line))
	{
		free(line);
		if (header_complete(game))
			return (2);
		return (fail("Header is incomplete"));
	}
	if (parse_header_element(line, game) != 0)
		return (free_and_return(line, 1));
	free(line);
	*raw = get_next_line(fd);
	return (0);
}

/* Main orchestrator for header parsing */
int	parse_header(int fd, t_game *game)
{
	char	*raw;
	int		status;

	raw = get_next_line(fd);
	if (!raw)
		return (fail("Empty file"));
	while (raw)
	{
		status = process_header_step(fd, game, &raw);
		if (status == 1)
			return (1);
		if (status == 2)
			return (0);
	}
	if (header_complete(game))
		return (0);
	return (fail("Header is incomplete"));
}
