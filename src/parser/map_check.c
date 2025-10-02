/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:00:38 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/02 13:12:38 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static int	check(t_map *map, int y, int x)
{
	if (map->map_cpy[y][x] == ' ' || map->map_cpy[y][x] == '\n')
		return (1);
	return (0);
}

static int	edge_check(t_map *map)
{
	int	i;
	int	j;
	int	len;

	j = 0;
	while (j < map->height)
	{
		i = 0;
		len = ft_strlen(map->map_cpy[j]);
		while (i < len && map->map_cpy[j][i] != '\n')
		{
			if (map->map_cpy[j][i] == 'X' || map->map_cpy[j][i] == 'N')
			{
				if (check(map, j + 1, i + 1) || check(map, j + 1, i - 1) \
					|| check(map, j - 1, i + 1) || check(map, j - 1, i - 1))
					return (1);
			}
			i++;
		}
		j++;
	}
	return (0);
}

static int	char_check(t_map *map, int i, int j)
{
	if (map->map_cpy[j][i] != '1' && map->map_cpy[j][i] != '0' \
			&& map->map_cpy[j][i] != 'N' && map->map_cpy[j][i] != 'S' \
				&& map->map_cpy[j][i] != 'W' && map->map_cpy[j][i] != 'E' \
					&& map->map_cpy[j][i] != ' ')
		return (perror("Invalid char in map"), 1);
	if (map->map_cpy[j][i] == 'N' || map->map_cpy[j][i] == 'S' \
			|| map->map_cpy[j][i] == 'W' || map->map_cpy[j][i] == 'E')
	{
		map->player++;
		map->x = i;
		map->y = j;
		if (map->map_cpy[j][i] == 'N')
			map->dir = 'N';
		else if (map->map_cpy[j][i] == 'S')
			map->dir = 'S';
		else if (map->map_cpy[j][i] == 'W')
			map->dir = 'W';
		else
			map->dir = 'E';
	}
	return (0);
}

static int	flood_fill(t_map *map, int y, int x)
{
	int	len;

	if (y < 0 || x < 0 || y >= map->height || x >= map->width)
		return (1);
	len = ft_strlen(map->map_cpy[y]);
	if (x >= len || map->map_cpy[y][x] == '\n')
		return (1);
	if (map->map_cpy[y][x] == '1' || map->map_cpy[y][x] == 'X')
		return (0);
	if (map->map_cpy[y][x] == ' ')
		map->map_cpy[y][x] = '1';
	map->map_cpy[y][x] = 'X';
	flood_fill(map, y - 1, x);
	flood_fill(map, y + 1, x);
	flood_fill(map, y, x + 1);
	flood_fill(map, y, x - 1);
	return (0);
}

int	map_check(t_map *map)
{
	int	i;
	int	j;
	int	len;

	map->player = 0;
	j = 0;
	while (j < map->height)
	{
		i = 0;
		len = ft_strlen(map->map_cpy[j]);
		while (i < len && map->map_cpy[j][i] != '\n')
		{
			if (char_check(map, i, j))
				return (1);
			i++;
		}
		j++;
	}
	if (map->player != 1)
		return (perror("Must be one player"), 1);
	if (flood_fill(map, map->y, map->x) || edge_check(map))
		return (perror("Error\nMap must be surrounded by walls"), 1);
	return (0);
}
