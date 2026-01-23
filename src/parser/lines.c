/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:58:30 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/23 13:52:44 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	line_len_no_nl(const char *s)
{
	int i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

static int	lines_grow(t_lines *arr, int newcap)
{
	char	**tmp;
	int		i;

	tmp = (char **)malloc(sizeof(char *) * newcap);
	if (!tmp)
		return (1);
	i = 0;
	while (i < arr->count)
	{
		tmp[i] = arr->v[i];
		i++;
	}
	free(arr->v);
	arr->v = tmp;
	arr->cap = newcap;
	return (0);
}

int	lines_push(t_lines *arr, char *line) //añade una linea a una lista, y la lista crece si hace falta
{
	int	len;
	int	newcap;

	if (arr->count == arr->cap)
	{
		newcap = 16;
		if (arr->cap != 0)
			newcap = arr->cap * 2;
		if (lines_grow(arr, newcap) != 0)
			return (1);
	}
	arr->v[arr->count] = line;
	arr->count++; //por cada linea valida que se guarde, aumenta el contador
	len = line_len_no_nl(line);
	if (len > arr->maxw) //cada vez que encuentras una linea mas larga que las anteriores
		arr->maxw = len; //actualizas maxw (objetivo: mapa rectangular)
	return (0);
}

void	free_lines(t_lines *arr)
{
	int	i;

	if (!arr || !arr->v)
		return ;
	i = 0;
	while (i < arr->count)
	{
		free(arr->v[i]);
		i++;
	}
	free(arr->v);
	arr->v = NULL;
	arr->count = 0;
	arr->cap = 0;
	arr->maxw = 0;
}
