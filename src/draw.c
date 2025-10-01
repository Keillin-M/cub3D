/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:10:36 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/01 19:28:12 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"

static void	draw_pixels_with_step(t_img *img, int x, int y, int color)
{
	int	i;

	i = 0;
	while (i < img->render_step && (x + i) < WIN_WIDTH)
	{
		put_pixel_to_img(img, x + i, y, color);
		i++;
	}
}

static void	apply_shade(int *color, double distance)
{
	if (distance > 8)
		*color = (*color >> 2) & 0x3F3F3F;
	else if (distance > 4)
		*color = (*color >> 1) & 0x7F7F7F;
}

void	draw_wall_col(t_game *game, t_ray *ray, t_img *img, int x)
{
	int	tex_num;
	int	tex_x;
	int	y;
	int	color;

	tex_num = get_wall_texture(ray);
	texture_coords(ray, game, tex_num, &tex_x);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		color = get_wall_color(game, ray, tex_num, tex_x, y);
		apply_shade(&color, ray->perp_wall_dist);
		draw_pixels_with_step(img, x, y, color);
		y += img->render_step;
	}
}

