/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:45:02 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/15 18:56:41 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>
#include <fcntl.h>

int	skip_to_map(t_map *map)
{
	int		texture_count;
	char	*line;

	map->fd = open(map->fd_name, O_RDONLY);
	if (map->fd < 0)
		return (perror("Error opening file"), 1);
	line = get_next_line(map->fd);
	texture_count = 0;
	while (texture_count < 6)
	{
		if (ft_strncmp(line, "\n", 1) != 0)
			texture_count++;
		free(line);
		line = get_next_line(map->fd);
	}
	while (line && ft_strncmp(line, "\n", 1) == 0)
	{
		free(line);
		line = get_next_line(map->fd);
	}
	map->line = line;
	return (0);
}

int	map_size(t_map *map)
{
	map->count = 0;
	while (map->line)
	{
		map->count++;
		free(map->line);
		map->line = get_next_line(map->fd);
	}
	close(map->fd);
	map->line = NULL;
	map->map = malloc(sizeof(char *) * (map->count + 1));
	map->map_cpy = malloc(sizeof(char *) * (map->count + 1));
	if (!map->map || !map->map_cpy)
		return (perror("Error\nmalloc failed"), 1);
	if (skip_to_map(map))
		return (1);
	return (0);
}

int	draw_map(t_map *map)
{
	int	row;

	row = 0;
	if (map_size(map))
		return (1);
	while (map->line)
	{
		map->map[row] = ft_strdup(map->line);
		map->map_cpy[row] = ft_strdup(map->line);
		if (!map->map[row] || !map->map_cpy[row])
		{
			close(map->fd);
			return (free(map->line), perror("ft_strdup failed"), 1);
		}
		if (ft_strlen(map->line) > map->width)
			map->width = ft_strlen(map->line);
		free(map->line);
		row++;
		map->line = get_next_line(map->fd);
	}
	map->height = row;
	return (0);
}

int	read_line(t_map *map, t_tex *tex)
{
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
			return (perror("Error\ninvalid type identifier"), 1);
		}
		free(map->line);
		map->line = get_next_line(map->fd);
	}
	if (tex->count == 6 && draw_map(map))
		return (1);
	return (0);
}

int	read_file(t_map *map, t_tex *tex, char **argv)
{
	int	i;

	map->fd_name = argv[1];
	map->fd = open(map->fd_name, O_RDONLY);
	if (map->fd < 0)
		return (perror("Error opening file"), 1);
	map->line = get_next_line(map->fd);
	if (read_line(map, tex))
		return (1);
	if (texture_file_check(tex))
		return (close(map->fd), 1);
	if (map_check(map))
		return (close(map->fd), 1);
	return (close(map->fd), 0);
}
