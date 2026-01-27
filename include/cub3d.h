/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:21:09 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/27 19:18:23 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <MLX42/MLX42.h>
# include <stdint.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# define WIDTH 1280  //tamaño de la ventana
# define HEIGHT 720
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

typedef struct s_cfg
{
    char	*north;
    char	*south;
    char	*east;
    char	*west;
    int		floor_color[3];    // R, G, B
    int		ceiling_color[3];  // R, G, B
	int		floor_set;
	int		ceiling_set;
}	t_cfg;

typedef struct s_map
{
	char	**grid; // matriz del mapa (grid[y][x] y fila, x columna)
	int		width; //num columnas (ancho mapa) (game->map.width = arr->maxw)
	int		height; //num filas (game->map.height = arr->count)
	int		spawn_x; //columna x dd empieza el jugador
	int		spawn_y; //fila y dd empieza el jugador
	char	spawn_dir; //direccion inicial del jugador ('N', 'S', 'E', 'W')

}	t_map;

typedef struct s_tex
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
}	t_tex;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	uint32_t	ceiling; //Un uint32_t es un número (unsigned) de 32 bits que guarda un color RGBA
	uint32_t	floor;
	t_player	player;
	t_map		map;
	t_cfg		cfg;
	t_tex		textures;
}	t_game;
//t_line es como un contenedor de lineas del mapa
typedef struct s_lines
{
	char	**v; //array dinamico de lineas
	int		count; // contador de lineas
	int		cap; //capacidad reservada
	int		maxw; //ancho de la linea mas larga del mapa
}	t_lines;

typedef struct s_parse_state
{
	int		fd;
	int		in_map;
	int		end_map;
	char	*line;
}	t_parse_state;

//infraestructura
void	game_init_zero(t_game *game);
void	game_destroy(t_game *game);
//parser header
int		parse_header(int fd, t_game *game);
int		parse_header_element(const char *line, t_game *g);
//parser
int		parse_file(const char *filename, t_game *game);
int		find_and_store_spawn(t_game *game);
int		validate_map(t_game *game);
/* helpers del parser map */
int		read_map_lines(int fd, t_lines *arr);
int		process_map_step(t_parse_state *st, t_lines *arr);
int		build_grid(t_game *game, t_lines *arr);
void	free_lines(t_lines *arr);
int		is_map_line(const char *s);
int		is_blank_line(const char *s);
int		is_map_row(const char *s);
int		lines_push(t_lines *arr, char *line);

/*debug
void	dump_cfg(t_cfg *cfg);
void	dump_grid(char **grid, int height);
void	dump_spawn(t_game *game);*/


#endif
