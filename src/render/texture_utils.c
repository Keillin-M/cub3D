/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 20:03:29 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/09 12:07:12 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"
#include "render.h"

int	get_texture_pixel(t_texture *tex, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	dst = tex->img.addr + (y * tex->img.line_len 
			+ x * (tex->img.bpp / 8));
	return (*(unsigned int *)dst);
}

int	set_colors(t_game *game, t_render *render)
{
	if (!game->tex->texture[4] || !game->tex->texture[4][1])
	{
		ft_putstr_fd("Error\nFloor color not found\n", 2);
		return (0);
	}
	if (!game->tex->texture[5] || !game->tex->texture[5][1])
	{
		ft_putstr_fd("Error\nCeiling color not found\n", 2);
		return (0);
	}
	render->floor_color = (game->tex->floor_r << 16) 
		| (game->tex->floor_g << 8) | game->tex->floor_b;
	render->ceiling_color = (game->tex->ceiling_r << 16) 
		| (game->tex->ceiling_g << 8) | game->tex->ceiling_b;
	return (1);
}
