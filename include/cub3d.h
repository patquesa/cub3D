#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42/MLX42.h>
# include <stdint.h>

# define W 800
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
