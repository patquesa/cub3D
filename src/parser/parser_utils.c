/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:55:48 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/23 20:52:46 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Devuelve 1 si la línea contiene solo " 01NSEW" (hasta \n) y tiene al menos un '1' */
int	is_map_line(const char *s)
{
	int	i;
	int	has_wall;

	if (!s)
		return (0);
	i = 0;
	has_wall = 0;
	while (s[i] && s[i] != '\n')
	{
		if (s[i] == '1')
			has_wall = 1;
		else if (s[i] == '0' || s[i] == 'N' || s[i] == 'S'
			|| s[i] == 'E' || s[i] == 'W' || s[i] == ' ')
			;
		else
			return (0);
		i++;
	}
	return (has_wall);
}
