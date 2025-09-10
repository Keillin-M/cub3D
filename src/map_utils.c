/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:45:02 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/10 17:18:11 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_map(t_map *map)
{
	int	row;

	row = 0;
	game->map[row] = ft_strdup(game->line);
	game->map_cpy[row] = ft_strdup(game->line);
	if (!game->map[row] || !game->map_cpy[row])
	{
		close(game->fd);
		return (free(game->line), perror("ft_strdup failed"), 1);
	}
	free(game->line);
	row++;
	game->line = get_next_line(game->fd);
}

int	read_map(t_map *map, char **argv)
{
	int	i;

	map->fd = open(argv[1], O_RDONLY);
	if (map->fd < 0)
		return (perror("Error opening file"), 1);
	map->line = get_next_line(map->fd);
	while (map->line)
	{
		while (map->check != 1)
			texture_check(map);
		i = 0;
		While (i < 6)
	{
		if (!map->texture[i])
			return (1);
		i++;
	}
	}
	return (close(game->fd), 0);
}
