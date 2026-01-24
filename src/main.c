/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:13:49 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/24 19:35:44 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"
# include <MLX42/MLX42.h>

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
	/* Si llega aquí, el parseo básico funciona */
	write(1, "OK\n", 3);
	game_destroy(&game);

	/* Debug opcional
	write(1, "Spawn dir: ", 11);
	write(1, &game.map.spawn_dir, 1);
	write(1, "\n", 1);
	*/
	return (0);
}

