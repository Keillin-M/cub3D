/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthajan <tthajan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:26:43 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/30 14:58:03 by tthajan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"

static int	map_ext(char *argv)
{
	int	len;

	len = ft_strlen(argv);
	if (len < 9)
	{
		ft_printf("File extension invalid\n");
		return (1);
	}
	if (!ft_isalnum(argv[len - 5]) && argv[len - 5] != '-'
		&& argv[len - 5] != '_')
	{
		ft_printf("File extension invalid\n");
		return (1);
	}
	if (ft_strncmp(argv + len - 4, ".cub", 4) == 0)
		return (0);
	ft_printf("File extension invalid\n");
	return (1);
}

int	ft_open(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
		return (1);
	
	// Hide mouse cursor and center it for FPS-style control
	mlx_mouse_hide(game->mlx, game->win);
	mlx_mouse_move(game->mlx, game->win, WIN_WIDTH/2, WIN_HEIGHT/2);
	
	return (0);
}

int	ft_close(t_game *game)
{
	if (game->render)
		ft_destroy_img(game);
	if (game->map)
		ft_clean_map(game->map);
	if (game->tex)
		ft_clean_tex(game->tex);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	return (exit(0), 0);
}

static int	setup_game(t_game *game, t_map *map, t_tex *tex, t_player *player)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map = map;
	game->tex = tex;
	if (ft_open(game))
		return (1);
	ft_init_player(player, map);
	game->player = *player;
	game->render = NULL;
	if (!init_textures(game))
	{
		ft_printf("Error: Failed to initialize textures\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_map		map;
	t_tex		tex;
	t_game		game;
	t_player	player;

	if (argc != 2)
		return (perror("Wrong number of arguments"), 1);
	if (map_ext(argv[1]))
		return (1);
	ft_init(&map, &tex);
	if (read_file(&map, &tex, argv))
		return (ft_clean_map(&map), 1);
	if (setup_game(&game, &map, &tex, &player))
		return (ft_clean_map(&map), 1);
	mlx_hook(game.win, 17, 0, ft_close, &game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_hook(game.win, 2, 1L << 0, ft_key_event, &game);
	mlx_hook(game.win, 6, 1L << 6, ft_mouse_event, &game);
	mlx_loop(game.mlx);
	return (0);
}
