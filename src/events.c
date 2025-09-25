/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:13:27 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/25 17:29:48 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	move_forward(t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->player.x + game->player.dir_x * game->player.mov_speed;
	new_y = game->player.y + game->player.dir_y * game->player.mov_speed;
	if (is_valid_pos(game, new_x, new_y))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

int	ft_key_event(int keycode, t_game *game)
{
	if (keycode == 65307)
		ft_close(game);
	else if (keycode == 'w')
		move_forward(game);
	else if (keycode == 's')
		move_backward(game);
	else if (keycode == 'a')
		move_left(game);
	else if (keycode == 'd')
		move_right(game);
	else if (keycode == 65361)
		rotate_left(game);
	else if (keycode == 6536)
		rotate_right(game);
	return (0);
}
