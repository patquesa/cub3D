/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:13:49 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/21 10:20:30 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42/MLX42.h>
#include "cub3d.h"

//ESC //cuando MLX detecta la pulsación de una tecla, llama a key_hook
static void	key_hook(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}

int main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(W, H, "cub3D (MLX42 Linux)", true); //estructura interna (mlx_t)
	if (!mlx)
		return (1); //Devuelve un puntero a esa estructura (puntero mlx)
	img = mlx_new_image(mlx, W, H);
	if (!img)
		return (mlx_terminate(mlx), 1);
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		return (mlx_terminate(mlx), 1);
	mlx_key_hook(mlx, key_hook, mlx); //le dices q cuando llames a key_hook, pasale mlx como parametro
	mlx_loop(mlx); //permanece esperando hasta que pasa algo, como pulsar tecla
	mlx_terminate(mlx); //limpia y cierra todo lo que se creo con MLX
	return (0);
}
