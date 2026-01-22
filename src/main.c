/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:13:49 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/22 16:39:00 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <MLX42/MLX42.h>

/* ESC
	- param = &game (direccion estructura game)
	- hook siempre recibe puntero a estructura
*/
static void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
}

int	main(void)
{
	t_game	game;

	init_game(&game); // inicializamos el juego (mapa, jugador, colores)
	// inicializa MLX42 y crea la ventana
	game.mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!game.mlx)
		return (1); // Devuelve un puntero a esa estructura (puntero mlx)
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	if (!game.img)
		return (mlx_terminate(game.mlx), 1);
	if (mlx_image_to_window(game.mlx, game.img, 0, 0) < 0)
		return (mlx_terminate(game.mlx), 1);
	// le dices q cuando llames a key_hook, pasale estructura game
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_loop_hook(game.mlx, render_frame, &game); // renderizado
	// permanece esperando hasta que pasa algo, como pulsar tecla
	mlx_loop(game.mlx);
	// limpia y cierra todo lo que se creo con MLX
	mlx_terminate(game.mlx);
	return (0);
}
