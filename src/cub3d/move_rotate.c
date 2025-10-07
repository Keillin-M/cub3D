/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:18:35 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/07 14:46:35 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_player_rotation(t_game *game, int delta_x, 
			float mouse_sensitivity)
{
	int	center_x;
	int	center_y;

	center_x = WIN_WIDTH / 2;
	center_y = WIN_HEIGHT / 2;
	game->player.rot += delta_x * mouse_sensitivity;
	game->player.dir_x = cos(game->player.rot);
	game->player.dir_y = sin(game->player.rot);
	game->player.plane_x = -sin(game->player.rot) * game->player.fov;
	game->player.plane_y = cos(game->player.rot) * game->player.fov;
	mlx_mouse_move(game->mlx, game->win, center_x, center_y);
}

static int	is_valid_pos(t_map *map, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0 || map_x >= map->width || map_y >= map->height)
		return (0);
	if (map->map[map_y][map_x] == '1')
		return (0);
	return (1);
}

static void	update_pos(t_player *player, t_map *map, float new_x, float new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)new_x;
	map_y = (int)new_y;
	if (is_valid_pos(map, map_x, map_y))
	{
		player->x = new_x;
		player->y = new_y;
	}
}

void	ft_move(t_player *player, t_map *map, char mov)
{
	float	new_x;
	float	new_y;

	if (mov == 'w')
	{
		new_x = player->x + player->dir_x * player->speed;
		new_y = player->y + player->dir_y * player->speed;
	}
	else if (mov == 's')
	{
		new_x = player->x - player->dir_x * player->speed;
		new_y = player->y - player->dir_y * player->speed;
	}
	else if (mov == 'd')
	{
		new_x = player->x + player->plane_x * player->speed;
		new_y = player->y + player->plane_y * player->speed;
	}
	else
	{
		new_x = player->x - player->plane_x * player->speed;
		new_y = player->y - player->plane_y * player->speed;
	}
	update_pos(player, map, new_x, new_y);
}

void	ft_rotate(t_player *player, char rot)
{
	if (rot == 'l')
		player->turn_dir = -1;
	else if (rot == 'r')
		player->turn_dir = 1;
	else
		return ;
	player->rot += player->turn_dir * 0.05f;
	player->dir_x = cos(player->rot);
	player->dir_y = sin(player->rot);
	player->plane_x = -sin(player->rot) * player->fov;
	player->plane_y = cos(player->rot) * player->fov;
}
