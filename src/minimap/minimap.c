/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 20:28:50 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/03 15:20:23 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minimap.h"

static int	get_dynamic_scale(t_game *game)
{
	int	scale_x;
	int	scale_y;
	int	dynamic_scale;

	scale_x = MINIMAP_SIZE / game->map->width;
	scale_y = MINIMAP_SIZE / game->map->height;
	if (scale_x < scale_y)
		dynamic_scale = scale_x;
	else
		dynamic_scale = scale_y;
	if (dynamic_scale < 1)
		dynamic_scale = 1;
	return (dynamic_scale);
}

void	draw_minimap_to_buffer(t_game *game, char *img_data, int line_len)
{
	int	dynamic_scale;

	if (!game->map || !game->map->map)
		return ;
	dynamic_scale = get_dynamic_scale(game);
	draw_map_tiles(game, img_data, line_len, dynamic_scale);
	draw_player_on_minimap(game, img_data, line_len, dynamic_scale);
}
