/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:55:48 by patquesa          #+#    #+#             */
/*   Updated: 2026/02/04 13:10:56 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Check if a line contains only whitespace */
int	is_blank_line(const char *s)
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

/* Check if a line is a valid map row (contains only valid map chars) */
int	is_map_row(const char *s)
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

/* Check if a character is a valid cell in the final map (0, 1, or space) */
int	is_valid_cell(char c)
{
	return (c == '0' || c == '1' || c == ' ');
}

/* Free a grid copy (used in validation) */
void	free_grid_copy(char **g, int h)
{
	int	y;

	if (!g)
		return ;
	y = 0;
	while (y < h)
	{
		free(g[y]);
		y++;
	}
	free(g);
}
