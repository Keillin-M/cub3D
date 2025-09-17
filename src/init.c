/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:37:55 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/17 15:05:34 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init(t_map *map, t_tex *tex)
{
	map->x = 0;
	map->y = 0;
	map->fd = 0;
	map->width = 0;
	map->height = 0;
	map->player = 0;
	map->count = 0;
	map->fd_name = NULL;
	map->line = NULL;
	map->map = NULL;
	map->map_cpy = NULL;
	map->texture = NULL;
	tex->no = 0;
	tex->so = 0;
	tex->we = 0;
	tex->ea = 0;
	tex->c = 0;
	tex->f = 0;
	tex->count = 0;
	tex->texture = malloc(sizeof(char **) * 6);
	if (!tex->texture)
		return ;
}
