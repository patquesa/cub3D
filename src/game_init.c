/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:23:21 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/22 20:09:23 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//inicializamos toda la estructura a 0
void	game_init_zero(t_game *game)
{
	unsigned char	*p;
	int				i;

	p = (unsigned char *)game; //convierte game en un bloque de bytes (unsigned char *)
	i = 0;
	while (i < (int)sizeof(t_game)) //recorre cada byte (tamaño total structura) y lo pone a 0
	{
		p[i] = 0; //cada byte se pone a 0
		i++;
	}
}
