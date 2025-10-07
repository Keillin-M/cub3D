/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:45:02 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/07 17:45:24 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

static int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	check_disconnected_map(t_map *map)
{
	int	y;
	int	map_ended;
	int	found;

	y = 0;
	map_ended = 0;
	found = 0;
	while (y < map->height)
	{
		if (is_empty_line(map->map_cpy[y]))
		{
			if (found)
				map_ended = 1;
		}
		else
		{
			found = 1;
			if (map_ended)
				return (ft_putstr_fd("Error\nDisconnected map section", 2), 1);
		}
		y++;
	}
	return (0);
}

static int	skip_to_map(t_map *map)
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
		if (!line)
			return (ft_putstr_fd("Error\nNot enough texture identifiers", 2), 1);
	}
	while (line && ft_strncmp(line, "\n", 1) == 0)
	{
		free(line);
		line = get_next_line(map->fd);
	}
	map->line = line;
	return (0);
}

static int	map_size(t_map *map)
{
	map->count = 0;
	while (map->line)
	{
		map->count++;
		free(map->line);
		map->line = get_next_line(map->fd);
	}
	close(map->fd);
	map->map = malloc(sizeof(char *) * (map->count + 1));
	map->map_cpy = malloc(sizeof(char *) * (map->count + 1));
	if (ft_malloc_check(map->map) || ft_malloc_check(map->map_cpy))
		return (1);
	map->map[map->count] = NULL;
	map->map_cpy[map->count] = NULL;
	if (skip_to_map(map))
		return (ft_clean_map(map), 1);
	return (0);
}

int	copy_map(t_map *map)
{
	int	row;
	int	len;

	row = 0;
	if (map_size(map))
		return (1);
	while (map->line)
	{
		map->map[row] = ft_strdup(map->line);
		map->map_cpy[row] = ft_strdup(map->line);
		if (!map->map[row] || !map->map_cpy[row])
			return (ft_clean_map(map), free(map->line), 
				perror("ft_strdup failed"), 1);
		len = ft_strlen(map->line);
		if (len > 0 && map->line[len - 1] == '\n')
			len--;
		if (len > map->width)
			map->width = len;
		free(map->line);
		row++;
		map->line = get_next_line(map->fd);
	}
	map->height = row;
	return (close(map->fd), 0);
}
