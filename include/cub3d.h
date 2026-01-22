/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:21:09 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/22 20:06:56 by patquesa         ###   ########.fr       */
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
	char	**grid; // matriz del mapa (grid[y][x] y fila, x columna)
	int		width; //num columnas (ancho mapa) (game->map.width = arr->maxw)
	int		height; //num filas (game->map.height = arr->count)
	int		spawn_x; //columna x dd empieza el jugador
	int		spawn_y; //fila y dd empieza el jugador
	char	spawn_dir; //direccion inicial del jugador ('N', 'S', 'E', 'W')

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
//t_line es como un contenedor de lineas del mapa
typedef struct s_lines
{
	char	**v; //array dinamico de lineas
	int		count; // contador de lineas
	int		cap; //capacidad reservada
	int		maxw; //ancho de la linea mas larga del mapa
}	t_lines;

//infraestructura
void	game_init_zero(t_game *game);
void	game_destroy(t_game *game);
//parser
int		parse_file(const char *filename, t_game *game);
int		find_and_store_spawn(t_game *game);
int		validate_map(t_game *game);
/* helpers del parser */
int		read_map_lines(int fd, t_lines *arr);
int		build_grid(t_game *game, t_lines *arr);
void	free_lines(t_lines *arr);
int		is_map_line(const char *s);
int		lines_push(t_lines *arr, char *line);

#endif
