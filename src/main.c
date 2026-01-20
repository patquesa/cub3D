#include <MLX42/MLX42.h>

#define W 800
#define H 600

static void key_hook(mlx_key_data_t keydata, void *param)
{
	mlx_t *mlx = (mlx_t *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}

int main(void)
{
	mlx_t *mlx = mlx_init(W, H, "cub3D (MLX42 Linux)", true);
	if (!mlx)
		return (1);

	mlx_key_hook(mlx, key_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
