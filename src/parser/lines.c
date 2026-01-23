/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:58:30 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/23 18:57:34 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//Devuelve el número de caracteres leídos (sin contar el \n)
static int	line_len_no_nl(const char *s)
{
	int i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

static int	lines_grow(t_lines *arr, int newcap)
{
	char	**tmp; //hacemos un array mas grande con la capacidad q vamos a reservar
	int		i;

	tmp = (char **)malloc(sizeof(char *) * newcap); //reservamos memoria que necesitamos para el newcap
	if (!tmp)
		return (1);
	i = 0;
	while (i < arr->count) //dentro del nuevo array copiamos los punteros a las lineas que ya teniamos guardadas
	{
		tmp[i] = arr->v[i];
		i++;
	}
	free(arr->v); //liberamos el viejo array de punteros a lineas
	arr->v = tmp; //ahora arr->v contiene tmp
	arr->cap = newcap; //srr-> se actualiza al nuevo tamaño
	return (0);
}

int	lines_push(t_lines *arr, char *line) //añade una linea a una lista, y la lista crece si hace falta
{
	int	len;
	int	newcap;

	if (arr->count == arr->cap) //Si el array está lleno, hay que aumentar su capacidad(se hace con lines_grow)
	{
		newcap = 16; //si es la primera vez, damos capacidad para 16 lineas
		if (arr->cap != 0) //si ya teniamos algo antes y nos quedamos sin espacio, duplicamos
			newcap = arr->cap * 2;
		if (lines_grow(arr, newcap) != 0) //reservas mas espacio para newcap
			return (1);
	}
	arr->v[arr->count] = line;
	arr->count++; //por cada linea valida que se guarde, aumenta el contador
	len = line_len_no_nl(line);
	if (len > arr->maxw) //cada vez que encuentras una linea mas larga que las anteriores
		arr->maxw = len; //actualizas maxw (objetivo: mapa rectangular)
	return (0);
}
//Liberar toda la memoria dinámica usada por una estructura t_lines
void	free_lines(t_lines *arr)
{
	int	i;

	if (!arr || !arr->v)
		return ;
	i = 0;
	while (i < arr->count)
	{
		free(arr->v[i]); //liberas cada línea del mapa que se había leído y guardado.
		i++;
	}
	free(arr->v); //liberas despues array de punteros
	arr->v = NULL; //dejamos estructura limpia por seguridad
	arr->count = 0;
	arr->cap = 0;
	arr->maxw = 0;
}
