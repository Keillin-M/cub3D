/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:37:55 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/26 16:56:55 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init_player2(t_player *player, t_map *map)
{
	if (map->dir == 'E')
	{
		player->dir_x = 1.0f;
		player->dir_y = 0.0f;
		player->plane_x = 0.0f;
		player->plane_y = 0.66f;
	}
	else if (map->dir == 'W')
	{
		player->dir_x = -1.0f;
		player->dir_y = 0.0f;
		player->plane_x = 0.0f;
		player->plane_y = -0.66f;
	}
}

void	ft_init_player(t_player *player, t_map *map)
{
	player->x = (float)map->x + 0.5f;
	player->y = (float)map->y + 0.5f;
	if (map->dir == 'N')
	{
		player->dir_x = 0.0f;
		player->dir_y = -1.0f;
		player->plane_x = 0.66f;
		player->plane_y = 0.0f;
	}
	else if (map->dir == 'S')
	{
		player->dir_x = 0.0f;
		player->dir_y = 1.0f;
		player->plane_x = -0.66f;
		player->plane_y = 0.0f;
	}
	else
		ft_init_player2(player, map);
	player->speed = 0.1f;
	player->rot = 0.05f;
}

void	ft_init(t_map *map, t_tex *tex)
{
	map->x = 0;
	map->y = 0;
	map->fd = 0;
	map->width = 0;
	map->height = 0;
	map->player = 0;
	map->count = 0;
	map->fd_name = NULL;
	map->line = NULL;
	map->map = NULL;
	map->map_cpy = NULL;
	map->texture = NULL;
	tex->no = 0;
	tex->so = 0;
	tex->we = 0;
	tex->ea = 0;
	tex->c = 0;
	tex->f = 0;
	tex->count = 0;
	tex->texture = malloc(sizeof(char **) * 6);
	ft_malloc_check(tex->texture);
}
