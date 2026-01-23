/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:59:49 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/23 13:52:03 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

static int	is_blank_line(const char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

static int	is_map_row(const char *s)
{
	int	i;
	int	has_cell;

	if (!s)
		return (0);
	i = 0;
	has_cell = 0;
	while (s[i] && s[i] != '\n')
	{
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\r')
			;
		else if (s[i] == '0' || s[i] == '1'
			|| s[i] == 'N' || s[i] == 'S' || s[i] == 'E' || s[i] == 'W')
			has_cell = 1;
		else
			return (0);
		i++;
	}
	return (has_cell);
}

//lee archivo.cub y guarda solo el bloque del mapa dentro de arr
int	read_map_lines(int fd, t_lines *arr) //con puntero arr accedemos y modificamos estructura original
{
	char	*line; //puntero a una linea del archivo
	int		in_map;
	int		end_map;
//& obtiene una dirección, * accede al contenido de esa dirección
	arr->v = NULL; //guarda cada linea
	arr->count = 0; //numero de lineas (filas) del mapa
	arr->cap = 0; //capacidad (cuantas lineas entran en arr->v sin hacer otro malloc)
	arr->maxw = 0; //ancho maximo del mapa = linea mas larga = numero columnas total
	in_map = 0;
	end_map = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (in_map == 0)
		{
			if (is_map_line(line)) //con esa funcion vemos si es una linea del mapa o no
				in_map = 1; //que lo es, estamos dentro del mapa
			else
			{
				free(line); //si la linea leida no es del mapa, la liberamos (no la necesitamos)
				line = get_next_line(fd); //lee hasta EOF
				continue ;
			}
		}
		if (end_map == 0) //si no llegamos al final del mapa
		{
			if (is_blank_line(line)) //si linea en blanco
			{
				end_map = 1; //hemos llegado al final
				free(line);
			}
			else if (is_map_row(line) == 0) // Línea NO válida de mapa
			{
				free(line);
				free_lines(arr); //liberamos todas las anteriores
				return (1);
			}
			else //si sí es linea valida, la guardamos en arr->
			{
				if (lines_push(arr, line) != 0)
				{
					free(line);
					free_lines(arr);
					return (1);
				}
			}
		}
		else
		{
			if (is_blank_line(line) == 0) // Línea NO vacía DESPUÉS del mapa
			{
				free(line);
				free_lines(arr);
				return (1); //error
			}
			free(line);
		}
		line = get_next_line(fd);
	}
	if (arr->count == 0) //no hay lineas validas
	{
		free_lines(arr);
		return (1);
	}
	return (0);
}
