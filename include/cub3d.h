/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:21:09 by patquesa          #+#    #+#             */
/*   Updated: 2026/02/03 16:44:27 by adruz-to         ###   ########.fr       */
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

# define WIDTH 1280
# define HEIGHT 720

/**************** STRUCTS ****************/

typedef struct s_player
{
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}					t_player;

typedef struct s_cfg
{
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	int				floor_color[3];
	int				ceiling_color[3];
	int				floor_set;
	int				ceiling_set;
}					t_cfg;

typedef struct s_map
{
	char			**grid;
	int				width;
	int				height;
	int				spawn_x;
	int				spawn_y;
	char			spawn_dir;
}					t_map;

typedef struct s_ray
{
	double			camera_x;
	double			dir_x;
	double			dir_y;
	int				map_x;
	int				map_y;
	double			side_dis_x;
	double			side_dis_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
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
	mlx_texture_t	*texture;
	double			wall_x;
	int				tex_x;
	double			step;
	double			tex_pos;
}					t_wall;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	uint32_t		ceiling;
	uint32_t		floor;
	t_player		player;
	t_map			map;
	t_cfg			cfg;
	t_tex			textures;
}					t_game;

typedef struct s_lines
{
	char			**v;
	int				count;
	int				cap;
	int				maxw;
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
int					parse_color_payload(const char *payload, int rgb[3]);
int					set_path_once(char **dst, const char *payload);
int					parse_file(const char *filename, t_game *game);
int					find_and_store_spawn(t_game *game);
int					validate_map(t_game *game);
int					read_map_lines(int fd, t_lines *arr);
int					process_map_step(t_parse_state *st, t_lines *arr);
int					build_grid(t_game *game, t_lines *arr);
void				free_lines(t_lines *arr);
int					is_blank_line(const char *s);
int					is_map_row(const char *s);
int					lines_push(t_lines *arr, char *line);
int					is_ws(char c);
int					is_valid_cell(char c);
void				free_grid_copy(char **g, int h);

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

/**************** UTILS ****************/
int					fail(const char *msg);

#endif
