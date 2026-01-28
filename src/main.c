/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:13:49 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/28 15:52:27 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"
#include <unistd.h>

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		return (fail("Usage: ./cub3D map.cub")); //av[0] = ./cub3D, av[1] = map.cub
		return (1);
	}
	game_init_zero(&game);
	/* Llamamos al parser */
	if (parse_file(av[1], &game) != 0) //&game (t_game *game puntero a estructura principal)
	{
		//fail("Invalid map\n");
		game_destroy(&game);
		return (1);
	}
	write(1, "OK\n", 3);
	game_destroy(&game);
	return (0);
	
	/* Init runtime 
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

