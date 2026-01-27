/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:13:49 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/27 19:16:24 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
# include "cub3d.h"
# include <MLX42/MLX42.h>*/

/*
//ESC //param = &game (direccion estructura game) //hook siempre recibe puntero a estructura
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

	game.mlx = mlx_init(W, H, "cub3D", false); //inicializa MLX42 y crea la ventana
	if (!game.mlx)
		return (1); //Devuelve un puntero a esa estructura (puntero mlx)
	game.img = mlx_new_image(game.mlx, W, H);
	if (!game.img)
		return (mlx_terminate(game.mlx), 1);
	if (mlx_image_to_window(game.mlx, game.img, 0, 0) < 0)
		return (mlx_terminate(game.mlx), 1);
	mlx_key_hook(game.mlx, key_hook, &game); //le dices q cuando llames a key_hook, pasale estructura game
	mlx_loop(game.mlx); //permanece esperando hasta que pasa algo, como pulsar tecla
	mlx_terminate(game.mlx); //limpia y cierra todo lo que se creo con MLX
	return (0);
}*/

#include "cub3d.h"
#include <unistd.h>

static void	put_error(const char *msg)
{
	while (*msg)
		write(2, msg++, 1);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		put_error("Error\nUsage: ./cub3D map.cub\n"); //av[0] = ./cub3D, av[1] = map.cub
		return (1);
	}
	game_init_zero(&game);
	/* Llamamos al parser */
	if (parse_file(av[1], &game) != 0) //&game (t_game *game puntero a estructura principal)
	{
		put_error("Error\nInvalid map\n");
		game_destroy(&game);
		return (1);
	}
	/* DEBUG Si llega aquí, el parseo básico funciona
	dump_cfg(&game.cfg);
	dump_grid(game.map.grid, game.map.height);
	dump_spawn(&game);*/
	write(1, "OK\n", 3);
	game_destroy(&game);
	return (0);
	
	/* Init runtime (PARTE DE ELLA)
	if (init_game(&game) != 0)
	{
		put_error("Error\nInit game failed\n");
		game_destroy(&game);
		return (1);
	}

	// MLX / hooks / loop
	game.mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!game.mlx)
	{
		put_error("Error\nmlx_init failed\n");
		game_destroy(&game);
		return (1);
	}
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	if (!game.img)
	{
		game_destroy(&game);
		return (1);
	}
	if (mlx_image_to_window(game.mlx, game.img, 0, 0) < 0)
	{
		game_destroy(&game);
		return (1);
	}
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);
	
	// Limpieza FINAL
	game_destroy(&game);
	return (0);*/
}

