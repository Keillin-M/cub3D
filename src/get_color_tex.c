/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_tex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:27:29 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/01 19:27:44 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"

int	get_wall_texture(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (3);
		else
			return (2);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (1);
		else
			return (0);
	}
}

static int	get_fallback_color(int tex_num)
{
	if (tex_num == 0)
		return (0x0000FF);
	else if (tex_num == 1)
		return (0x00FF00);
	else if (tex_num == 2)
		return (0xFFFF00);
	else
		return (0xFF0000);
}

int	get_wall_color(t_game *game, t_ray *ray, int tex_num, int tex_x, int y)
{
	int			tex_y;
	int			d;
	t_texture	tex;

	if (tex_num < 0 || tex_num >= 4)
		return (get_fallback_color(0));
	if (!game->render)
		return (get_fallback_color(tex_num));
	tex = game->render->textures[tex_num];
	if (tex.img.img && tex.height > 0 && tex.width > 0)
	{
		d = y * 256 - WIN_HEIGHT * 128 + ray->line_height * 128;
		tex_y = ((d * tex.height) / ray->line_height) / 256;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex.height)
			tex_y = tex.height - 1;
		if (tex_x < 0)
			tex_x = 0;
		if (tex_x >= tex.width)
			tex_x = tex.width - 1;
		return (get_texture_pixel(&tex, tex_x, tex_y));
	}
	else
		return (get_fallback_color(tex_num));
}
