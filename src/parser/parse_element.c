/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:23:07 by patquesa          #+#    #+#             */
/*   Updated: 2026/02/04 12:48:54 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Convert RGB values to RGBA uint32_t format */
static uint32_t	rgb_to_rgba_u32(int r, int g, int b)
{
	return (((uint32_t)r << 24)
		| ((uint32_t)g << 16)
		| ((uint32_t)b << 8)
		| 255u);
}

/* Parse texture identifiers (NO, SO, WE, EA) */
static int	parse_texture_identifiers(const char *line, t_game *g)
{
	if (ft_strncmp(line, "NO", 2) == 0 && is_ws(line[2]))
		return (set_path_once(&g->cfg.north, line + 2));
	if (ft_strncmp(line, "SO", 2) == 0 && is_ws(line[2]))
		return (set_path_once(&g->cfg.south, line + 2));
	if (ft_strncmp(line, "WE", 2) == 0 && is_ws(line[2]))
		return (set_path_once(&g->cfg.west, line + 2));
	if (ft_strncmp(line, "EA", 2) == 0 && is_ws(line[2]))
		return (set_path_once(&g->cfg.east, line + 2));
	return (-1);
}

/* Parse floor color (F identifier) */
static int	parse_floor_color(const char *line, t_game *g)
{
	if (g->cfg.floor_set)
		return (fail("Duplicate floor color"));
	if (parse_color_payload(line + 2, g->cfg.floor_color) != 0)
		return (1);
	g->cfg.floor_set = 1;
	g->floor = rgb_to_rgba_u32(g->cfg.floor_color[0],
			g->cfg.floor_color[1], g->cfg.floor_color[2]);
	return (0);
}

/* Parse ceiling color (C identifier) */
static int	parse_ceiling_color(const char *line, t_game *g)
{
	if (g->cfg.ceiling_set)
		return (fail("Duplicate ceiling color"));
	if (parse_color_payload(line + 2, g->cfg.ceiling_color) != 0)
		return (1);
	g->cfg.ceiling_set = 1;
	g->ceiling = rgb_to_rgba_u32(g->cfg.ceiling_color[0],
			g->cfg.ceiling_color[1], g->cfg.ceiling_color[2]);
	return (0);
}

/* Parse a header element line - returns 0 if valid, 1 if error */
int	parse_header_element(const char *line, t_game *g)
{
	int	result;

	result = parse_texture_identifiers(line, g);
	if (result != -1)
		return (result);
	if (line[0] == 'F' && is_ws(line[1]))
		return (parse_floor_color(line, g));
	if (line[0] == 'C' && is_ws(line[1]))
		return (parse_ceiling_color(line, g));
	return (fail("Invalid header line"));
}
