/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:00:38 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/15 16:04:37 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	char_check(t_map *map, int i, int j)
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
	}
	return (0);
}

int	flood_fill(t_map *map, int y, int x)
{
	if (y < 0 || x < 0 || y >= map->height || x >= map->width)
		return (1);
	if (map->map_cpy[y][x] == '1' || map->map_cpy[y][x] == 'X')
		return (0);
	if (map->map_cpy[y][x] == ' ')
		return (1);
	map->map_cpy[y][x] = 'X';
	if (flood_fill(map, y - 1, x) || flood_fill(map, y + 1, x) 
		|| flood_fill(map, y, x + 1) || flood_fill(map, y, x - 1))
		return (1);
	return (0);
}

int	map_check(t_map *map, int i, int j)
{
	if ((map->height > 1080) || (map->width > 1920))
		return (perror("Map is too big"), 1);
	while (j < map->height)
	{
		i = 0;
		while (i < map->width)
		{
			if (char_check(map, i, j))
				return (1);
			i++;
		}
		j++;
	}
	if (map->player != 1)
		return (perror("Must be one player"), 1);
	if (flood_fill(map, map->y, map->x))
		return (perror("Error\nMap must be surrounded by walls"), 1);
	return (0);
}
