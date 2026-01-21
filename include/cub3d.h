/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:21:09 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/21 10:21:20 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42/MLX42.h>
# include <stdint.h>

# define W 800  //tamaño de la ventana
# define H 600
//t_game es el estado global del juego
typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	uint32_t	ceiling; //Un uint32_t es un número (unsigned) de 32 bits que guarda un color RGBA
	uint32_t	floor;
}	t_game;

#endif
