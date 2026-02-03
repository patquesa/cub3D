/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:23:21 by patquesa          #+#    #+#             */
/*   Updated: 2026/02/03 17:34:56 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Initialize the entire t_game structure to 0 (pointers, integers, chars...) */
void	game_init_zero(t_game *game)
{
	unsigned char	*p;
	int				i;

	p = (unsigned char *)game;
	i = 0;
	while (i < (int) sizeof(t_game))
	{
		p[i] = 0;
		i++;
	}
}
