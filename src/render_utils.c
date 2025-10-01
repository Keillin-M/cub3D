/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:11:59 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/01 19:30:09 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"

static double	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000.0) + (time.tv_usec / 1000.0));
}

void	update_fps(t_game *game)
{
	double			delta_time;
	double			current_time;
	static int		fps_counter;
	static double	last_time;
	static double	fps_last_time;

	current_time = get_time();
	if (last_time == 0)
	{
		last_time = current_time;
		fps_last_time = current_time;
	}
	delta_time = current_time - last_time;
	last_time = current_time;
	fps_counter++;
	if (current_time - fps_last_time >= 1000)
	{
		if (game->render)
			game->render->fps = fps_counter;
		fps_counter = 0;
		fps_last_time = current_time;
	}
}
