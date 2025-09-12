/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:45:02 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/12 18:51:44 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>
#include <fcntl.h>

void	draw_map(t_map *map)
{
	int	row;

	row = 0;
	map->map[row] = ft_strdup(map->line);
	map->map_cpy[row] = ft_strdup(map->line);
	if (!map->map[row] || !map->map_cpy[row])
	{
		close(map->fd);
		return (free(map->line), perror("ft_strdup failed"), 1);
	}
	free(map->line);
	row++;
	map->line = get_next_line(map->fd);
}

int	read_map(t_map *map, t_tex *tex, char **argv)
{
	int	i;

	map->fd = open(argv[1], O_RDONLY);
	if (map->fd < 0)
		return (perror("Error opening file"), 1);
	map->line = get_next_line(map->fd);
	while (map->line && tex->count < 6)
	{
		if (texture_check(tex, map))
		{
			close(map->fd);
			free(map->line);
			return (perror("Error\ninvalid type identifier"), 1);
		}
		free(map->line);
		map->line = get_next_line(map->fd);
	}
	if (texture_file_check(tex))
		return (close(map->fd), 1);
	return (close(map->fd), 0);
}
