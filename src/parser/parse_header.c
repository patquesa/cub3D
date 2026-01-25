/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:53:56 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/25 13:27:11 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

static int	is_ws(char c)
{
	return (c == ' ' || c == '\t' || c == '\r');
}

static int	header_complete(t_game *g)
{
	return (g->textures.north && g->textures.south
		&& g->textures.east && g->textures.west
		&& g->textures.floor_set && g->textures.ceiling_set);
}

/* Convierte RGB a uint32 RGBA (útil para MLX42 al pintar) */
static uint32_t	rgb_to_rgba_u32(int r, int g, int b)
{
	return ((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | 255u;
}

/* Guarda una ruta SOLO si no estaba seteada antes */
static int	set_path_once(char **dst, const char *payload)
{
	char	*trimmed;

	if (*dst != NULL)
		return (1); // duplicado
	trimmed = ft_strtrim(payload, " \t\r");
	if (!trimmed || trimmed[0] == '\0')
		return (free(trimmed), 1);
	*dst = ft_strdup(trimmed);
	free(trimmed);
	return (*dst == NULL);
}

/* Parse de un componente 0..255, permitiendo espacios alrededor */
static int	parse_rgb_comp(const char *s, int *out)
{
	long	val;
	int		i;

	if (!s || !*s)
		return (1);
	i = 0;
	while (s[i] && is_ws(s[i]))
		i++;
	if (s[i] < '0' || s[i] > '9')
		return (1);
	val = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		val = val * 10 + (s[i] - '0');
		if (val > 255)
			return (1);
		i++;
	}
	while (s[i] && is_ws(s[i]))
		i++;
	if (s[i] != '\0')
		return (1);
	*out = (int)val;
	return (0);
}

static int	parse_color_payload(const char *payload, int rgb[3])
{
	char	**parts;

	parts = ft_split(payload, ',');
	if (!parts)
		return (1);
	if (!parts[0] || !parts[1] || !parts[2] || parts[3])
		return (ft_split_free(parts), 1);
	if (parse_rgb_comp(parts[0], &rgb[0])
		|| parse_rgb_comp(parts[1], &rgb[1])
		|| parse_rgb_comp(parts[2], &rgb[2]))
		return (ft_split_free(parts), 1);
	ft_split_free(parts);
	return (0);
}

//DIRECTOR DE ORQUESTA (COORDINA PARSER HEADER)
int	parse_header(int fd, t_game *game)
{
	char	*raw;
	char	*line;

	while ((raw = get_next_line(fd)) != NULL)
	{
		if (is_blank_line(raw))
		{
			free(raw);
			continue;
		}
		line = ft_strtrim(raw, " \t\r\n");
		free(raw);
		if (!line)
			return (1);

		/* Si detecto inicio de mapa, la cabecera debe estar completa */
		if (is_map_row(line))
		{
			free(line);
			return (header_complete(game) ? 0 : 1);
		}

		if (parse_header_element(line, game) != 0)
		{
			free(line);
			return (1);
		}
		free(line);
	}
	/* EOF: acepto solo si cabecera completa */
	return (header_complete(game) ? 0 : 1);
}
