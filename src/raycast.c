/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:10:35 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/01 19:28:42 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"

static void	texture_coords(t_ray *ray, t_game *game, int tex_num, int *tex_x)
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

void	wall_height(t_ray *ray)
{
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

void	wall_distance(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
	{
		ray->perp_wall_dist = (ray->map_x - game->player.x + 
				(1 - ray->step_x) / 2) / ray->ray_dir_x;
	}
	else
	{
		ray->perp_wall_dist = (ray->map_y - game->player.y + 
				(1 - ray->step_y) / 2) / ray->ray_dir_y;
	}
}

static int	is_wall(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map->width || y < 0 || y >= game->map->height)
		return (1);
	return (game->map->map[y][x] == '1');
}

void	perform_dda(t_ray *ray, t_game *game)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (is_wall(game, ray->map_x, ray->map_y))
			ray->hit = 1;
	}
}

