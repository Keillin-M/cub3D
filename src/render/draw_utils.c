/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:27:29 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/03 15:21:48 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"

void	texture_coords(t_ray *ray, t_game *game, int tex_num, int *tex_x)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	if (wall_x < 0)
		wall_x = 0;
	if (wall_x >= 1)
		wall_x = 0.999;
	if (game->render && game->render->textures[tex_num].img.img && 
		game->render->textures[tex_num].width > 0)
	{
		*tex_x = (int)(wall_x * (double)game->render->textures[tex_num].width);
		if ((ray->side == 0 && ray->ray_dir_x > 0) || 
			(ray->side == 1 && ray->ray_dir_y < 0))
			*tex_x = game->render->textures[tex_num].width - *tex_x - 1;
		if (*tex_x < 0)
			*tex_x = 0;
		if (*tex_x >= game->render->textures[tex_num].width)
			*tex_x = game->render->textures[tex_num].width - 1;
	}
	else
		*tex_x = 0;
}

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

int	get_wall_color(t_game *game, t_ray *ray, t_wall_data *wall_data)
{
	int			tex_y;
	int			d;
	t_texture	tex;

	tex = game->render->textures[wall_data->tex_num];
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
