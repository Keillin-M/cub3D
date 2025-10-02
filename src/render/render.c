/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:41:25 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/02 16:44:47 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"
#include "minimap.h"
#include <sys/time.h>

int	get_render_step(t_game *game)
{
	if (game && game->render && game->render->fps > 30)
		return (1);
	else if (game && game->render && game->render->fps > 15)
		return (2);
	else
		return (4);
}

/*static void	render_ceiling_and_floor(t_img *img, int ceiling_color, 
			int floor_color)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->height / 2)
	{
		x = 0;
		while (x < img->width)
		{
			put_pixel_to_img(img, x, y, ceiling_color);
			x++;
		}
		y++;
	}
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			put_pixel_to_img(img, x, y, floor_color);
			x++;
		}
		y++;
	}
}

static void	render_background(t_game *game)
{
	int	ceiling_color;
	int	floor_color;

	if (game->render)
	{
		ceiling_color = game->render->ceiling_color;
		floor_color = game->render->floor_color;
	}
	else
	{
		ceiling_color = 0x87CEEB;
		floor_color = 0x8B4513;
	}
	render_ceiling_and_floor(game->img, ceiling_color, floor_color);
}*/

static void	render_walls(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(&ray, game, x);
		perform_dda(&ray, game);
		wall_distance(&ray, game);
		wall_height(&ray);
		draw_wall_col(game, &ray, game->img, x);
		x += game->img->render_step;
	}
}

int	render(t_game *game)
{
	t_img	*img;

	update_fps(game);
	img = malloc(sizeof(t_img));
	if (ft_malloc_check(img))
		return (1);
	if (init_img_buffer(game, img))
		return (free(img), 1);
	img->render_step = get_render_step(game);
	if (game->img)
	{
		if (game->img->img)
			mlx_destroy_image(game->mlx, game->img->img);
		free(game->img);
	}
	game->img = img;
	render_walls(game);
	if (game->render && game->render->show_minimap)
		draw_minimap_to_buffer(game, img->addr, img->line_len);
	mlx_put_image_to_window(game->mlx, game->win, img->img, 0, 0);
	return (0);
}
