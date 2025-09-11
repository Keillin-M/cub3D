/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:00:38 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/10 13:46:17 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	char_check(t_map *map, int i, int j)
{
	if (map->map_cpy[j][i] != '1' && map->map_cpy[j][i] != '0' \
			&& map->map_cpy[j][i] != 'N' && map->map_cpy[j][i] != 'S' \
				&& map->map_cpy[j][i] != 'W' && map->map_cpy[j][i] != 'E' \
					&& map->map_cpy[j][i] != ' ')
		return (perror("Invalid char in map"), 1);
	if (map->map_cpy[j][i] == 'N' || && map->map_cpy[j][i] != 'S' \
			&& map->map_cpy[j][i] != 'W' && map->map_cpy[j][i] != 'E')
	{
		map->player++;
		map->x = i;
		map->y = j;
	}
	return (0);
}

int	map_check(t_map *map, int i, int j)
{
	if ((map->total_row * map->h > 1080) || (map->line_len * map->w > 1920))
		return (perror("Map is too big"), 1);
	while (j < map->total_row)
	{
		i = 0;
		while (i < game->line_len)
		{
			if (char_check(map, j, i))
				return (1);
			i++;
		}
		j++;
	}
	if (map->player != 1)
		return (perror("Must be one player"), 1);
	return (0);
}

int	map_wall(t_map *map)
{
	if (())
}

static int	flood_fill(t_game *game, int y, int x)
{
	if (y < 0 || x < 0 || y >= game->total_row || x >= game->line_len)
		return (1);
	if (game->map_cpy[y][x] == '1' || game->map_cpy[y][x] == 'X'
		|| game->map_cpy[y][x] == 'A')
		return (0);
	if (game->map_cpy[y][x] == 'E')
	{
		game->map_cpy[y][x] = 'A';
		return (0);
	}
	game->map_cpy[y][x] = 'X';
	flood_fill(game, y - 1, x);
	flood_fill(game, y + 1, x);
	flood_fill(game, y, x + 1);
	flood_fill(game, y, x - 1);
	return (0);
}
