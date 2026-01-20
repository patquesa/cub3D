#include <MLX42/MLX42.h>

#define W 800 //tamaño de la ventana
#define H 600
//ESC //cuando MLX detecta la pulsación de una tecla, llama a key_hook
static void key_hook(mlx_key_data_t keydata, void *param)
{
	mlx_t *mlx = (mlx_t *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}

int main(void)
{
	mlx_t *mlx = mlx_init(W, H, "cub3D (MLX42 Linux)", true); //estructura interna (mlx_t)
	if (!mlx)
		return (1); //Devuelve un puntero a esa estructura (puntero mlx)

	mlx_key_hook(mlx, key_hook, mlx); //le dices q cuando llames a key_hook, pasale mlx como parametro
	mlx_loop(mlx); //permanece esperando hasta que pulsas la tecla
	mlx_terminate(mlx); //limpia
	return (0);
}
