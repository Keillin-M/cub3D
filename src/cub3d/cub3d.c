/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:26:43 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/09 13:54:26 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"
#include <stdlib.h>
#include <stdio.h>

static int	map_ext(char *argv)
{
	int	len;

	len = ft_strlen(argv);
	if (len < 9)
	{
		ft_putstr_fd("Error\nFile extension invalid\n", 2);
		return (1);
	}
	if (!ft_isalnum(argv[len - 5]) && argv[len - 5] != '-'
		&& argv[len - 5] != '_')
	{
		ft_putstr_fd("Error\nFile extension invalid\n", 2);
		return (1);
	}
	if (ft_strncmp(argv + len - 4, ".cub", 4) == 0)
		return (0);
	ft_putstr_fd("Error\nFile extension invalid\n", 2);
	return (1);
}

static int	ft_init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	return (0);
}

int	ft_close(t_game *game)
{
	if (!game)
		return (exit(0), 0);
	if (game->map)
		ft_clean_map(game->map);
	if (game->tex)
		ft_clean_tex(game->tex);
	if (game->render)
		ft_destroy_img(game);
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	return (exit(0), 0);
}

static int	setup_game(t_game *game, t_map *map, t_tex *tex, t_player *player)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map = map;
	game->tex = tex;
	game->render = NULL;
	game->img = NULL;
	if (ft_init_mlx(game))
		return (1);
	ft_init_player(player, map);
	game->player = *player;
	if (init_textures(game))
		return (1);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
		return (1);
	mlx_mouse_move(game->mlx, game->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	return (0);
}

int	main(int argc, char **argv)
{
	t_map		map;
	t_tex		tex;
	t_game		game;
	t_player	player;

	if (argc != 2)
		return (ft_putstr_fd("Error\nWrong number of arguments\n", 2), 1);
	if (map_ext(argv[1]))
		return (1);
	ft_init(&map, &tex);
	if (read_file(&map, &tex, argv))
		return (ft_clean_map(&map), ft_clean_tex(&tex), gnl_cleanup(), 1);
	if (setup_game(&game, &map, &tex, &player))
		return (ft_clean_on_error(game, map, tex));
	print_welcome_banner();
	mlx_hook(game.win, 17, 0, ft_close, &game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_hook(game.win, 2, 1L << 0, ft_key_event, &game);
	mlx_hook(game.win, 6, 1L << 6, ft_mouse_event, &game);
	mlx_loop(game.mlx);
	return (0);
}
