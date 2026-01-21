/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:21:09 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/21 19:22:37 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42/MLX42.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# define W 800  //tamaño de la ventana
# define H 600
//t_game es el estado global del juego

typedef struct s_player
{
	double	x; // posición X
	double	y; // posición Y
	double	dir_x; // dirección X
	double	dir_y; // dirección Y
	double	plane_x; // plano cámara X
	double	plane_y; // plano cámara Y
	
}	t_player;

typedef struct s_textures
{
    char	*north;
    char	*south;
    char	*east;
    char	*west;
    int		floor_color[3];    // R, G, B
    int		ceiling_color[3];  // R, G, B
}	t_textures;

typedef struct s_map
{
	char	**grid; // matriz del mapa
	int		width;
	int		height;
}	t_map;


typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	uint32_t	ceiling; //Un uint32_t es un número (unsigned) de 32 bits que guarda un color RGBA
	uint32_t	floor;
	t_player	player;
	t_map		map;
	t_textures	textures;
}	t_game;

/* Funciones de parseo
int		parse_file(char *filename, t_game *game);
void	free_game(t_game *game);
void	error_exit(char *msg, t_game *game);

// Get Next Line (necesitarás implementar esto)
char	*get_next_line(int fd);*/

#endif
