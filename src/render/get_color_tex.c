/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_tex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:27:29 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/02 14:17:25 by kmaeda           ###   ########.fr       */
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

int	get_wall_color(t_game *game, t_ray *ray, t_wall_data *wall_data)
{
	int			tex_y;
	int			d;
	t_texture	tex;

	if (wall_data->tex_num < 0 || wall_data->tex_num >= 4)
		return (get_fallback_color(0));
	if (!game->render)
		return (get_fallback_color(wall_data->tex_num));
	tex = game->render->textures[wall_data->tex_num];
	if (tex.img.img && tex.height > 0 && tex.width > 0)
	{
		d = wall_data->y * 256 - WIN_HEIGHT * 128 + ray->line_height * 128;
		tex_y = ((d * tex.height) / ray->line_height) / 256;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex.height)
			tex_y = tex.height - 1;
		if (wall_data->tex_x < 0)
			wall_data->tex_x = 0;
		if (wall_data->tex_x >= tex.width)
			wall_data->tex_x = tex.width - 1;
		return (get_texture_pixel(&tex, wall_data->tex_x, tex_y));
	}
	else
		return (get_fallback_color(wall_data->tex_num));
}
