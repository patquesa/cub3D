/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:23:21 by patquesa          #+#    #+#             */
/*   Updated: 2026/02/03 19:43:29 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//inicializamos toda la estructura t_game a 0 (punteros, enteros, char...)
/* Initialize the entire t_game structure to 0 (pointers, integers, chars...) */
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
