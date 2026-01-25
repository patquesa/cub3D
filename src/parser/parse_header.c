/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:53:56 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/25 17:46:15 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"


static int	header_complete(t_game *g) //comprueba que header este completo (cd encuentra inicio mapa)
{
	return (g->cfg.north && g->cfg.south
		&& g->cfg.east && g->cfg.west
		&& g->cfg.floor_set && g->cfg.ceiling_set);
}

/* Convierte RGB a uint32 RGBA (útil para MLX42 al pintar) 
static uint32_t	rgb_to_rgba_u32(int r, int g, int b)
{
	return ((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | 255u;
}*/


//DIRECTOR DE ORQUESTA (COORDINA PARSER HEADER)
int	parse_header(int fd, t_game *game)
{//lee hasta que ve inicio del mapa, parsea cabecera y comprueba este completa
	char	*raw; //linea tal cual la devuelve get next line
	char	*line; //raw ya limpia, sin espacios ni \n a los lados

	raw = get_next_line(fd); //lees la primera linea
	while (raw)
	{
		if (is_blank_line(raw)) //1) ignoramos lineas en blanco entre elementos de la cabecera 
		{                 //estas lineas no significan nada
			free(raw);
			raw = get_next_line(fd);
			continue ;
		}
		line = ft_strtrim(raw, " \t\r\n"); //2)limpiamos y nos quedamos con line
		free(raw);
		if (!line)
			return (1);
		if (is_map_row(line)) //3) si detecto inicio mapa, la cabecera debe estar completa */
		{
			free(line);
			if (header_complete(game)) //si el header esta completo
				return (0);
			return (1);
		}//si linea No es Mapa (es decir, es NO, SO...)
		if (parse_header_element(line, game) != 0) //identifica el tipo
			return (free(line), 1);
		free(line); //libera linea procesada y leemos siguiente (vuelve while)
		raw = get_next_line(fd);
	}
	if (header_complete(game)) //si cabecera completa
		return (0); //ok
	return (1); //si no estaba completa
}
