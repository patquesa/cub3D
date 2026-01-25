/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:23:07 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/25 13:24:12 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

int	parse_header_element(const char *line, t_game *g)
{
	/* Texturas */
	if (ft_strncmp(line, "NO", 2) == 0 && is_ws(line[2]))
		return (set_path_once(&g->textures.north, line + 2));
	if (ft_strncmp(line, "SO", 2) == 0 && is_ws(line[2]))
		return (set_path_once(&g->textures.south, line + 2));
	if (ft_strncmp(line, "WE", 2) == 0 && is_ws(line[2]))
		return (set_path_once(&g->textures.west, line + 2));
	if (ft_strncmp(line, "EA", 2) == 0 && is_ws(line[2]))
		return (set_path_once(&g->textures.east, line + 2));

	/* Colores */
	if (line[0] == 'F' && is_ws(line[1]))
	{
		if (g->textures.floor_set)
			return (1); // duplicado
		if (parse_color_payload(line + 2, g->textures.floor_color) != 0)
			return (1);
		g->textures.floor_set = 1;
		g->floor = rgb_to_rgba_u32(g->textures.floor_color[0],
				g->textures.floor_color[1], g->textures.floor_color[2]);
		return (0);
	}
	if (line[0] == 'C' && is_ws(line[1]))
	{
		if (g->textures.ceiling_set)
			return (1); // duplicado
		if (parse_color_payload(line + 2, g->textures.ceiling_color) != 0)
			return (1);
		g->textures.ceiling_set = 1;
		g->ceiling = rgb_to_rgba_u32(g->textures.ceiling_color[0],
				g->textures.ceiling_color[1], g->textures.ceiling_color[2]);
		return (0);
	}
	return (1); // línea inválida dentro de la cabecera
}
