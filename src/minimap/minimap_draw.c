/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 20:33:55 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/03 15:20:37 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minimap.h"

static void	put_pixel_to_buffer(char *img_data, int x, int y, int color)
{
	char	*dst;
	int		line_len;

	line_len = WIN_WIDTH * 4;
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = img_data + (y * line_len + x * 4);
		*(unsigned int *)dst = color;
	}
}

static int	get_tile_color(t_game *game, int x, int y)
{
	if (y < game->map->height && x < (int)ft_strlen(game->map->map[y]))
	{
		if (game->map->map[y][x] == '1')
			return (WALL_COLOR);
		else
			return (FLOOR_COLOR);
	}
	return (WALL_COLOR);
}

static void	draw_single_tile(t_minimap_data *data, int pixel_x, int pixel_y, 
	int color)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < data->dynamic_scale - 1)
	{
		dx = 0;
		while (dx < data->dynamic_scale - 1)
		{
			put_pixel_to_buffer(data->img_data, pixel_x + dx, 
				pixel_y + dy, color);
			dx++;
		}
		dy++;
	}
}

void	draw_map_tiles(t_game *game, char *img_data, int line_len, 
	int dynamic_scale)
{
	t_minimap_data	data;
	int				var[4];

	data.img_data = img_data;
	data.line_len = line_len;
	data.dynamic_scale = dynamic_scale;
	var[1] = 0;
	while (var[1] < game->map->height)
	{
		var[0] = 0;
		while (var[0] < game->map->width)
		{
			var[2] = MINIMAP_X + var[0] * dynamic_scale;
			var[3] = MINIMAP_Y + var[1] * dynamic_scale;
			draw_single_tile(&data, var[2], var[3], 
				get_tile_color(game, var[0], var[1]));
			var[0]++;
		}
		var[1]++;
	}
}

void	draw_player_on_minimap(t_game *game, char *img_data, int line_len, 
	int dynamic_scale)
{
	int	player_pos[2];
	int	coords[2];
	int	i;

	(void)line_len;
	player_pos[0] = MINIMAP_X + (int)(game->player.x * dynamic_scale);
	player_pos[1] = MINIMAP_Y + (int)(game->player.y * dynamic_scale);
	coords[1] = -1;
	while (++coords[1] <= 1)
	{
		coords[0] = -1;
		while (coords[0] <= 1)
		{
			put_pixel_to_buffer(img_data, player_pos[0] + coords[0], 
				player_pos[1] + coords[1], PLAYER_COLOR);
			coords[0]++;
		}
	}
	i = 0;
	while (++i <= 15)
	{
		coords[0] = player_pos[0] + (int)(game->player.dir_x * i);
		coords[1] = player_pos[1] + (int)(game->player.dir_y * i);
		put_pixel_to_buffer(img_data, coords[0], coords[1], PLAYER_COLOR);
	}
}
