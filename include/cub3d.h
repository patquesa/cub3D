/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:21:09 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/26 13:14:07 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42/MLX42.h>
# include <stdint.h>
#include <stdio.h>
# include <math.h>

# define WIDTH 1280  //tamaño de la ventana
# define HEIGHT 720
//t_game es el estado global del juego

/**************** STRUCTS ****************/

typedef struct s_player
{
	double	x; // posición X
	double	y; // posición Y
	double	dir_x; // dirección central X donde mira el jugador
	double	dir_y; // dirección central Y donde mira el juegador
	double	plane_x; // plano cámara X (desplazamiento lateral)
	double	plane_y; // plano cámara Y (desplazamiento vertical)
}	t_player;

typedef struct s_map
{
	char	**grid; // matriz del mapa
	int		width;
	int		height;
}	t_map;

typedef struct s_ray
{
	double	camera_x; // posición X en la cámara (-1 a 1)
	double	dir_x; // dirección del rayo X
	double	dir_y; // dirección del rayo Y
	int		map_x; //coordenada X del cuadrado actual del mapa
	int		map_y; // coordenada Y del cuadrado actual del mapa
	double	side_dis_x; // distancia al próximo lado X
	double	side_dis_y; // distancia al próximo lado Y
	double	delta_dist_x; // distancia entre lados X
	double	delta_dist_y; // distancia entre lados Y
	double	perp_wall_dist; // distancia perpendicular a la pared
	int		step_x; // dirección de paso X
	int		step_y; // dirección de paso Y
	int		hit; // cuando golpea a una pared
	int		side; // lado NS (0) o lado EO(1)
	int		line_height; // altura de la línea a dibujar
	int		draw_start; // pixel de inicio
	int		draw_end; // pixel de fin
}	t_ray;

/* Runtime struct */
typedef struct s_tex
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
}	t_tex;

typedef struct s_wall
{
	mlx_texture_t	*texture;
	double			wall_x;
	int				tex_x;
}	t_wall;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	uint32_t	ceiling; // uint32_t:nº(unsigned) 32 bits q guarda un color RGBA
	uint32_t	floor;
	t_player	player;
	t_map		map;
	t_tex		textures;
}	t_game;

/**************** RENDER ****************/

/* Raycasting */
void			init_ray(t_ray *ray, t_game *game, int x);
void			cast_ray(t_game *game);

/* DDA */
void			perform_dda(t_ray *ray, t_game *game);

/* Wall calculation */
void			calculate_wall_height(t_ray *ray);

/* Drawing */
t_wall			init_wall(t_game *game, t_ray *ray);
uint32_t		get_tex_color(mlx_texture_t *texture, int x, int y);
void			draw_wall(t_game *game, t_ray *ray, t_wall *wall, int x);
void			draw_column(t_game *game, t_ray *ray, int x);

/* Textures */
mlx_texture_t	*get_wall_texture(t_game *game, t_ray *ray);
double			get_wall_x(t_game *game, t_ray *ray);

/* Main render */
void			render_frame(void *param);

/**************** INPUT ****************/

/* Player movement */
void			update_player(t_game *game);

/**************** INIT ****************/

/* Init game */
void			init_game(t_game *game);

#endif
