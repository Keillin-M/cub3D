/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthajan <tthajan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:13:27 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/30 13:12:55 by tthajan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

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

static void	ft_move(t_player *player, t_map *map, char mov)
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

void	toggle_minimap(t_game *game)
{
	if (game->render)
		game->render->show_minimap = !game->render->show_minimap;
}

int	ft_key_event(int keycode, t_game *game)
{
	char	mov;
	char	rot;

	mov = 0;
	rot = 0;
	if (keycode == 65307)
		ft_close(game);
	else if (keycode == 'w')
		mov = 'w';
	else if (keycode == 's')
		mov = 's';
	else if (keycode == 'a')
		mov = 'a';
	else if (keycode == 'd')
		mov = 'd';
	else if (keycode == 65361)
		rot = 'l';
	else if (keycode == 65363)
		rot = 'r';
	else if (keycode == 'm')
		toggle_minimap(game);              // Toggle minimap display
	if (mov == 'w' || mov == 's' || mov == 'a' || mov == 'd')
		ft_move(&game->player, game->map, mov);
	if (rot)
		ft_rotate(&game->player, rot);
	return (0);
}
