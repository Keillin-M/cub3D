/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 20:28:50 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/01 21:02:46 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minimap.h"

static void	put_pixel_to_buffer(char *img_data, int x, int y, int color, int line_len)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = img_data + (y * line_len + x * (32 / 8));
		*(unsigned int*)dst = color;
	}
}

static int	get_dynamic_scale(t_game *game)
{
	int	scale_x;
	int	scale_y;
	int	dynamic_scale;

	scale_x = MINIMAP_SIZE / game->map->width;
	scale_y = MINIMAP_SIZE / game->map->height;
	dynamic_scale = (scale_x < scale_y) ? scale_x : scale_y;
	if (dynamic_scale < 1)
		dynamic_scale = 1;
	return (dynamic_scale);
}

void	draw_minimap_to_buffer(t_game *game, char *img_data, int line_len)
{
    int	dynamic_scale;

    if (!game->map || !game->map->map)
        return;
    dynamic_scale = get_dynamic_scale(game);
    draw_map_tiles(game, img_data, line_len, dynamic_scale);
    draw_player_on_minimap(game, img_data, line_len, dynamic_scale);
}
