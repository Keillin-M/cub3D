/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:41:34 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/17 17:25:30 by kmaeda           ###   ########.fr       */
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
				return (perror("Error\nCannot open texture file"), 1);
			close(fd);
			i++;
		}
	}
	else
		return (perror("Error\nInvalid number of texture identifiers"), 1);
	return (0);
}

int	color_check(char *temp)
{
	int		val;
	char	**rgb;

	rgb = ft_split(temp, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (1);
	while (*rgb)
	{
		val = ft_atoi(*rgb);
		if (val < 0 || val > 255)
			return (free_array(rgb), 1);
		rgb++;
	}
	return (0);
}

void	id_check(t_tex *tex, char **temp)
{
	if (ft_strncmp(temp[0], "NO", 2) == 0)
	{
		tex->texture[0] = temp;
		tex->no++;
	}
	else if (ft_strncmp(temp[0], "SO", 2) == 0)
	{
		tex->texture[1] = temp;
		tex->so++;
	}
	else if (ft_strncmp(temp[0], "WE", 2) == 0)
	{
		tex->texture[2] = temp;
		tex->we++;
	}
	else if (ft_strncmp(temp[0], "EA", 2) == 0)
	{
		tex->texture[3] = temp;
		tex->ea++;
	}
	tex->count++;
}

int	texture_check(t_tex *tex, t_map *map)
{
	char	**temp;

	temp = ft_split(map->line, ' ');
	if (!temp || temp[2])
		return (1);
	if (ft_strncmp(temp[0], "F", 1) == 0 || ft_strncmp(temp[0], "C", 1) == 0)
	{
		if (color_check(temp[1]))
			return (1);
		if (ft_strncmp(temp[0], "F", 1) == 0)
		{
			tex->texture[4] = temp;
			tex->f++;
		}
		else if (ft_strncmp(temp[0], "C", 1) == 0)
		{
			tex->texture[5] = temp;
			tex->c++;
		}
		tex->count++;
	}
	else
		id_check(tex, temp);
	return (0);
}
