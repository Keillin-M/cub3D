/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:16:26 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/07 16:23:08 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static int	read_line(t_map *map, t_tex *tex)
{
	map->width = 0;
	while (tex->count < 6)
	{
		if (ft_strncmp(map->line, "\n", 1) == 0)
		{
			free(map->line);
			map->line = get_next_line(map->fd);
		}
		if (texture_check(tex, map))
		{
			close(map->fd);
			free(map->line);
			ft_putstr_fd("Error\nInvalid texture identifiers", 2);
			return (1);
		}
		free(map->line);
		map->line = get_next_line(map->fd);
	}
	if (copy_map(map))
		return (1);
	return (0);
}

int	read_file(t_map *map, t_tex *tex, char **argv)
{
	map->fd_name = argv[1];
	map->fd = open(map->fd_name, O_RDONLY);
	if (map->fd < 0)
		return (perror("Error opening file"), 1);
	map->line = get_next_line(map->fd);
	if (!map->line)
		return (close(map->fd), ft_putstr_fd("Error\nEmpty file", 2), 1);
	if (read_line(map, tex))
		return (1);
	if (texture_file_check(tex) || tex->c != 1 || tex->f != 1)
		return (ft_clean_map(map), ft_clean_tex(tex), 1);
	if (map_check(map))
		return (ft_clean_map(map), ft_clean_tex(tex), 1);
	return (0);
}
