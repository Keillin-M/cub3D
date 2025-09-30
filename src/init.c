/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthajan <tthajan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:37:55 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/30 14:48:38 by tthajan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void	ft_init_player2(t_player *player, t_map *map)
{
	if (map->dir == 'E')
	{
		player->dir_x = 1.0f;
		player->dir_y = 0.0f;
		player->plane_x = 0.0f;
		player->plane_y = player->fov;
		player->rot = 0.0f;       // East = 0 degrees
	}
	else if (map->dir == 'W')
	{
		player->dir_x = -1.0f;
		player->dir_y = 0.0f;
		player->plane_x = 0.0f;
		player->plane_y = -player->fov;
		player->rot = 3.14159f;   // West = 180 degrees (π)
	}
}

void	ft_init_player(t_player *player, t_map *map)
{
	player->x = (float)map->x + 0.5f;
	player->y = (float)map->y + 0.5f;
	player->fov = 0.66f;  // Initialize default FOV
	if (map->dir == 'N')
	{
		player->dir_x = 0.0f;
		player->dir_y = -1.0f;
		player->plane_x = player->fov;
		player->plane_y = 0.0f;
		player->rot = -1.5708f;   // North = -90 degrees (-π/2)
	}
	else if (map->dir == 'S')
	{
		player->dir_x = 0.0f;
		player->dir_y = 1.0f;
		player->plane_x = -player->fov;
		player->plane_y = 0.0f;
		player->rot = 1.5708f;    // South = 90 degrees (π/2)
	}
	else
		ft_init_player2(player, map);
	player->speed = 0.1f;
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
