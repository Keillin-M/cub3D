/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:55:02 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/07 16:00:16 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	color_check(char *temp, int *r, int *g, int *b)
{
	char	**rgb;

	rgb = ft_split(temp, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_array(rgb), 1);
	*r = ft_atoi(rgb[0]);
	*g = ft_atoi(rgb[1]);
	*b = ft_atoi(rgb[2]);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (free_array(rgb), 1);
	free_array(rgb);
	return (0);
}

int	handle_floor_color(t_tex *tex, char **temp)
{
	if (color_check(temp[1], &tex->floor_r, &tex->floor_g, 
			&tex->floor_b) == 1)
	{
		free_array(temp);
		return (1);
	}
	tex->texture[4] = temp;
	tex->f++;
	tex->count++;
	return (0);
}

int	handle_ceiling_color(t_tex *tex, char **temp)
{
	if (color_check(temp[1], &tex->ceiling_r, &tex->ceiling_g,
			&tex->ceiling_b) == 1)
	{
		free_array(temp);
		return (1);
	}
	tex->texture[5] = temp;
	tex->c++;
	tex->count++;
	return (0);
}
