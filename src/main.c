/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:13:49 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/29 10:15:04 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <MLX42/MLX42.h>
#include <unistd.h>

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

/* Función principal */
int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (fail("Usage: ./cub3D map.cub"));
	game_init_zero(&game);
	/* Primero parseamos el archivo */
	if (parse_file(av[1], &game) != 0)
	{
		game_destroy(&game);
		return (1);
	}
	/* Inicializamos el juego (mapa, jugador, colores) */
	init_game(&game);
	/* Inicializamos MLX42 y creamos la ventana */
	game.mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!game.mlx)
		return (game_destroy(&game), 1);
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	if (!game.img)
		return (mlx_terminate(game.mlx), game_destroy(&game), 1);
	if (mlx_image_to_window(game.mlx, game.img, 0, 0) < 0)
		return (mlx_terminate(game.mlx), game_destroy(&game), 1);
	/* Configuramos hooks */
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	/* Iniciamos el loop */
	mlx_loop(game.mlx);
	/* Limpiar al salir */
	cleanup_game(&game);
	return (0);
}

