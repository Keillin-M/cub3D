/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:16:37 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/25 17:09:32 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	ft_clean_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->height <= 0)
		return ;
	if (!map->map || !map->map_cpy)
		return ;
	while (i < map->height)
	{
		if (map->map && map->map[i])
			free(map->map[i]);
		if (map->map_cpy && map->map_cpy[i])
			free(map->map_cpy[i]);
		i++;
	}
	if (map->map)
		free(map->map);
	if (map->map_cpy)
		free(map->map_cpy);
	map->map_cpy = NULL;
	map->map = NULL;
	return ;
}


