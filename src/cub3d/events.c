/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:13:27 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/02 16:48:27 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdlib.h>

static void	hide_show_minimap(t_game *game)
{
	if (game->render)
		game->render->show_minimap = !game->render->show_minimap;
}

static void	ft_mov_or_rotate(t_game *game, char mov, char rot)
{
	if (mov == 'w' || mov == 's' || mov == 'a' || mov == 'd')
		ft_move(&game->player, game->map, mov);
	if (rot)
		ft_rotate(&game->player, rot);
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
		hide_show_minimap(game);
	ft_mov_or_rotate(game, mov, rot);
	return (0);
}

int	ft_mouse_event(int x, t_game *game)
{
	static int	initialized = 0;
	int			center_x;
	int			center_y;
	int			delta_x;
	float		mouse_sensitivity;

	mouse_sensitivity = 0.003f;
	center_x = WIN_WIDTH / 2;
	center_y = WIN_HEIGHT / 2;
	if (!initialized)
	{
		initialized = 1;
		return (0);
	}
	delta_x = x - center_x;
	if (abs(delta_x) > 5)
	{
		game->player.rot += delta_x * mouse_sensitivity;
		game->player.dir_x = cos(game->player.rot);
		game->player.dir_y = sin(game->player.rot);
		game->player.plane_x = -sin(game->player.rot) * game->player.fov;
		game->player.plane_y = cos(game->player.rot) * game->player.fov;
		mlx_mouse_move(game->mlx, game->win, center_x, center_y);
	}
	return (0);
}
