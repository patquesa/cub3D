/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:53:56 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/27 12:13:25 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	header_complete(t_game *g) //comprueba que header este completo (cd encuentra inicio mapa)
{
	return (g->cfg.north && g->cfg.south
		&& g->cfg.east && g->cfg.west
		&& g->cfg.floor_set && g->cfg.ceiling_set);
}

static int	free_and_return(char *line, int ret)
{
	free(line);
	return (ret);
}

static int	process_header_step(int fd, t_game *game, char **raw) //raw puntero a linea actual
{
	char	*line;

	if (is_blank_line(*raw)) //1) ignoramos lineas en blanco entre elementos de la cabecera
	{
		free(*raw);
		*raw = get_next_line(fd); //raw es lo q devuelve gnl
		return (0); //seguir leyendo
	}
	line = ft_strtrim(*raw, " \t\r\n"); //2)limpiamos y nos quedamos con line (raw ya limpio)
	free(*raw);
	*raw = NULL; //por seguridad
	if (!line)
		return (1); //error
	if (is_map_row(line)) //3) si detecto inicio mapa, la cabecera debe estar completa
	{
		free(line);
		if (header_complete(game)) //si el header esta completo
			return (2); //terminado
		return (1);
	}
	if (parse_header_element(line, game) != 0)  //identifica el tipo
		return (free_and_return(line, 1)); //libera linea procesada y leemos siguiente (vuelve while)
	free(line);
	*raw = get_next_line(fd);
	return (0);
}

//DIRECTOR DE ORQUESTA (COORDINA PARSER HEADER)
int	parse_header(int fd, t_game *game) //lee hasta que ve inicio del mapa, parsea cabecera y comprueba este completa
{
	char	*raw;//linea tal cual la devuelve get next line
	int		status;

	raw = get_next_line(fd);
	while (raw)
	{
		status = process_header_step(fd, game, &raw); //(status)Procesa esta línea y dime qué ha pasado”.
		if (status == 1) //si error
			return (1);
		if (status == 2) //si ok
			return (0);
	}
	if (header_complete(game))
		return (0);
	return (1);
}
