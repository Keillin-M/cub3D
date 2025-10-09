/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:41:34 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/09 14:00:23 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>

int	texture_file_check(t_tex *tex)
{
	int		fd;
	int		i;
	char	*trimmed;

	i = 0;
	fd = 0;
	if (tex->no == 1 && tex->so == 1 && tex->we == 1 && tex->ea == 1 
		&& tex->c == 1 && tex->f == 1)
	{
		while (i < 4)
		{
			trimmed = ft_strtrim(tex->texture[i][1], "\n");
			free(tex->texture[i][1]);
			tex->texture[i][1] = trimmed;
			fd = open(tex->texture[i][1], O_RDONLY);
			if (fd < 0)
				return (ft_putstr_fd("Error\nCannot open texture file\n", 2), 1);
			close(fd);
			i++;
		}
	}
	else
		return (ft_putstr_fd("Error\nInvalid texture identifiers\n", 2), 1);
	return (0);
}

static void	id_check2(t_tex *tex, char **temp)
{
	if (ft_strncmp(temp[0], "WE", 2) == 0)
	{
		if (tex->texture[2])
			free_array(tex->texture[2]);
		tex->texture[2] = temp;
		tex->we++;
	}
	else if (ft_strncmp(temp[0], "EA", 2) == 0)
	{
		if (tex->texture[3])
			free_array(tex->texture[3]);
		tex->texture[3] = temp;
		tex->ea++;
	}
}

static void	id_check(t_tex *tex, char **temp)
{
	if (ft_strncmp(temp[0], "NO", 2) == 0)
	{
		if (tex->texture[0])
			free_array(tex->texture[0]);
		tex->texture[0] = temp;
		tex->no++;
	}
	else if (ft_strncmp(temp[0], "SO", 2) == 0)
	{
		if (tex->texture[1])
			free_array(tex->texture[1]);
		tex->texture[1] = temp;
		tex->so++;
	}
	else
		id_check2(tex, temp);
	tex->count++;
}

static char	**space_trim(t_map *map)
{
	char	*trimmed;
	char	**temp;
	int		count;

	trimmed = ft_strtrim(map->line, " \n\t");
	if (!trimmed)
		return (NULL);
	temp = ft_split(trimmed, ' ');
	free(map->line);
	map->line = trimmed;
	if (!temp)
	{
		free_array(temp);
		return (NULL);
	}
	count = 0;
	while (temp[count])
		count++;
	if (count != 2)
	{
		free_array(temp);
		return (NULL);
	}
	return (temp);
}

int	texture_check(t_tex *tex, t_map *map)
{
	char	**temp;

	temp = space_trim(map);
	if (!temp)
		return (1);
	if (ft_strncmp(temp[0], "F", 1) == 0)
	{
		if (handle_floor_color(tex, temp))
			return (1);
	}
	else if (ft_strncmp(temp[0], "C", 1) == 0)
		return (handle_ceiling_color(tex, temp));
	else
		id_check(tex, temp);
	return (0);
}
