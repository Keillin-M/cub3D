/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:16:37 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/09 13:24:16 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_destroy_img2(t_game *game)
{
	if (game->img->img)
	{
		mlx_destroy_image(game->mlx, game->img->img);
		game->img->img = NULL;
	}
	free(game->img);
	game->img = NULL;
}

void	ft_destroy_img(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (game->render->textures[i].img.img)
		{
			mlx_destroy_image(game->mlx, 
				game->render->textures[i].img.img);
			game->render->textures[i].img.img = NULL;
		}
	}
	if (game->img)
		ft_destroy_img2(game);
	if (game->render->screen.img)
	{
		mlx_destroy_image(game->mlx, game->render->screen.img);
		game->render->screen.img = NULL;
	}
	free(game->render);
	game->render = NULL;
}

void	ft_clean_tex(t_tex *tex)
{
	int	i;

	if (!tex || !tex->texture)
		return ;
	i = 0;
	while (i < 6)
	{
		if (tex->texture[i])
		{
			free_array(tex->texture[i]);
			tex->texture[i] = NULL;
		}
		i++;
	}
	free(tex->texture);
	tex->texture = NULL;
}

void	ft_clean_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	if (map->height > 0)
	{
		while (i < map->height)
		{
			if (map->map && map->map[i])
				free(map->map[i]);
			if (map->map_cpy && map->map_cpy[i])
				free(map->map_cpy[i]);
			i++;
		}
	}
	if (map->map)
		free(map->map);
	if (map->map_cpy)
		free(map->map_cpy);
	map->map_cpy = NULL;
	map->map = NULL;
}

int	ft_clean_on_error(t_game game, t_map map, t_tex tex)
{
	if (game.render)
		ft_destroy_img(&game);
	if (game.win)
		mlx_destroy_window(game.mlx, game.win);
	if (game.mlx)
	{
		mlx_destroy_display(game.mlx);
		free(game.mlx);
	}
	return (ft_clean_map(&map), ft_clean_tex(&tex), gnl_cleanup(), 1);
}
