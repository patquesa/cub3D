/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:21:09 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/30 17:41:06 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <MLX42/MLX42.h>
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1280 // tamaño de la ventana
# define HEIGHT 720
// t_game es el estado global del juego

/**************** STRUCTS ****************/

typedef struct s_player
{
	double x;       // posición X
	double y;       // posición Y
	double dir_x;   // dirección central X donde mira el jugador
	double dir_y;   // dirección central Y donde mira el juegador
	double plane_x; // plano cámara X (desplazamiento lateral)
	double plane_y; // plano cámara Y (desplazamiento vertical)
}					t_player;

typedef struct s_cfg
{
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	int floor_color[3];   // R, G, B
	int ceiling_color[3]; // R, G, B
	int				floor_set;
	int				ceiling_set;
}					t_cfg;

typedef struct s_map
{
	char **grid;    // matriz del mapa (grid[y][x] y fila, x columna)
	int width;      // num columnas (ancho mapa) (game->map.width = arr->maxw)
	int height;     // num filas (game->map.height = arr->count)
	int spawn_x;    // columna x dd empieza el jugador
	int spawn_y;    // fila y dd empieza el jugador
	char spawn_dir; // direccion inicial del jugador ('N', 'S', 'E', 'W')
}					t_map;

typedef struct s_ray
{
	double camera_x;       // posición X en la cámara (-1 a 1)
	double dir_x;          // dirección del rayo X
	double dir_y;          // dirección del rayo Y
	int map_x;             // coordenada X del cuadrado actual del mapa
	int map_y;             // coordenada Y del cuadrado actual del mapa
	double side_dis_x;     // distancia al próximo lado X
	double side_dis_y;     // distancia al próximo lado Y
	double delta_dist_x;   // distancia entre lados X
	double delta_dist_y;   // distancia entre lados Y
	double perp_wall_dist; // distancia perpendicular a la pared
	int step_x;            // dirección de paso X
	int step_y;            // dirección de paso Y
	int hit;               // cuando golpea a una pared
	int side;              // lado NS (0) o lado EO(1)
	int line_height;       // altura de la línea a dibujar
	int draw_start;        // pixel de inicio
	int draw_end;          // pixel de fin
}					t_ray;
typedef struct s_tex
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
}					t_tex;

typedef struct s_wall
{
	mlx_texture_t *texture; // textura a usar
	double wall_x;          // Posición exacta donde golpeó (0.0 a 1.0)
	int tex_x;              // Columna de la textura (0 a width-1)
	double step;            // Cuánto avanzar en Y por cada píxel
	double tex_pos;         // Posición actual en la textura (Y)
}					t_wall;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	uint32_t		ceiling;
	// Un uint32_t es un número (unsigned) de 32 bits que guarda un color RGBA
	uint32_t		floor;
	t_player		player;
	t_map			map;
	t_cfg			cfg;
	t_tex			textures;
}					t_game;

// t_line es como un contenedor de lineas del mapa
typedef struct s_lines
{
	char **v;  // array dinamico de lineas
	int count; // contador de lineas
	int cap;   // capacidad reservada
	int maxw;  // ancho de la linea mas larga del mapa
}					t_lines;

typedef struct s_parse_state
{
	int				fd;
	int				in_map;
	int				end_map;
	char			*line;
}					t_parse_state;

/**************** INFRASTRUCTURE ****************/
void				game_init_zero(t_game *game);
void				game_destroy(t_game *game);

/**************** PARSER ****************/
int					parse_header(int fd, t_game *game);
int					parse_header_element(const char *line, t_game *g);
int					parse_file(const char *filename, t_game *game);
int					find_and_store_spawn(t_game *game);
int					validate_map(t_game *game);
int					read_map_lines(int fd, t_lines *arr);
int					process_map_step(t_parse_state *st, t_lines *arr);
int					build_grid(t_game *game, t_lines *arr);
void				free_lines(t_lines *arr);
int					is_map_line(const char *s);
int					is_blank_line(const char *s);
int					is_map_row(const char *s);
int					lines_push(t_lines *arr, char *line);

/**************** INIT ****************/
void				setup_game(t_game *game);
void				set_direction(t_game *game, char dir);
void				init_textures(t_game *game);
void				free_textures(t_game *game);

/**************** INPUT ****************/
void				update_player(t_game *game);

/**************** RENDER ****************/
void				init_ray(t_ray *ray, t_game *game, int x);
void				cast_ray(t_game *game);
void				perform_dda(t_ray *ray, t_game *game);
void				calculate_wall_height(t_ray *ray);
t_wall				init_wall(t_game *game, t_ray *ray);
uint32_t			get_tex_color(mlx_texture_t *texture, int x, int y);
void				draw_wall(t_game *game, t_ray *ray, t_wall *wall, int x);
void				draw_column(t_game *game, t_ray *ray, int x);
mlx_texture_t		*get_wall_texture(t_game *game, t_ray *ray);
double				get_wall_x(t_game *game, t_ray *ray);
void				render_frame(void *param);

/**************** CLEANUP ****************/
void				cleanup_game(t_game *game);

/**************** UTILS ****************/
int					fail(const char *msg);

#endif
