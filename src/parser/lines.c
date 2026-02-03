/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:58:30 by patquesa          #+#    #+#             */
/*   Updated: 2026/02/03 17:35:14 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Calculate line length without newline characters */
static int	line_len_no_nl(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n' && s[i] != '\r')
		i++;
	return (i);
}

/* Grow the lines array capacity (dynamic reallocation) */
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

/* Add a line to the list, growing the array if necessary */
int	lines_push(t_lines *arr, char *line)
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
	arr->count++;
	len = line_len_no_nl(line);
	if (len > arr->maxw)
		arr->maxw = len;
	return (0);
}

/* Free all dynamic memory used by a t_lines structure */
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
