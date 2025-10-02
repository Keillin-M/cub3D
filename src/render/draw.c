/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:10:36 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/02 18:00:24 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"

void	put_pixel_to_img(t_img *img, int x, int y, int color)
{
	int	pixel_index;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		pixel_index = (y * img->line_len) + (x * 4);
		img->addr[pixel_index] = color & 0xFF;
		img->addr[pixel_index + 1] = (color >> 8) & 0xFF;
		img->addr[pixel_index + 2] = (color >> 16) & 0xFF;
		img->addr[pixel_index + 3] = 0;
	}
}

static void	draw_ceiling_section(t_img *img, t_game *game, 
			int x_pos, t_ray *ray)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel_to_img(img, x_pos, y, game->render->ceiling_color);
		y++;
	}
}

static void	draw_wall_section(t_img *img, t_game *game, 
			int x_pos, t_ray *ray)
{
	t_wall_data	wall_data;
	int			color;
	int			y;

	wall_data.tex_num = get_wall_texture(ray);
	texture_coords(ray, game, wall_data.tex_num, &wall_data.tex_x);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		wall_data.y = y;
		color = get_wall_color(game, ray, &wall_data);
		put_pixel_to_img(img, x_pos, y, color);
		y++;
	}
}

static void	draw_floor_section(t_img *img, t_game *game, 
			int x_pos, t_ray *ray)
{
	int	y;

	y = ray->draw_end;
	while (y < WIN_HEIGHT)
	{
		put_pixel_to_img(img, x_pos, y, game->render->floor_color);
		y++;
	}
}

void	draw_wall_col(t_game *game, t_ray *ray, t_img *img, int x)
{
	int	i;

	i = 0;
	while (i < img->render_step && (x + i) < WIN_WIDTH)
	{
		draw_ceiling_section(img, game, x + i, ray);
		draw_wall_section(img, game, x + i, ray);
		draw_floor_section(img, game, x + i, ray);
		i++;
	}
}
