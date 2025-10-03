/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:41:25 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/03 15:37:55 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"
#include "minimap.h"

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

static int	get_render_step(t_game *game)
{
	if (game && game->render && game->render->fps > 30)
		return (1);
	else if (game && game->render && game->render->fps > 15)
		return (2);
	else
		return (4);
}

static int	init_img_buffer(t_game *game, t_img *img)
{
	img->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!img->img)
		return (1);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, 
			&img->endian);
	img->width = WIN_WIDTH;
	img->height = WIN_HEIGHT;
	return (0);
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
