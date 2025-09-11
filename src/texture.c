/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:41:34 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/10 14:41:34 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	id_check(t_map *map, char *temp)
{
	if (temp[0] == 'NO')
		map->texture[0] = temp;
	else if (temp[0] == 'SO')
		map->texture[1] = temp;
	else if (temp[0] == 'WE')
		map->texture[2] = temp;
	else if (temp[0] == 'EA')
		map->texture[3] = temp;
	else if (temp[0] == 'F')
		map->texture[4] = temp;
	else if (temp[0] == 'C')
		map->texture[5] = temp;

}

int	texture_check(t_map *map)
{
	char	*temp;

	temp = split(line, " ");
	if (!temp || temp[2])
		return (1);
	if (temp[1][0] != '.' && temp[1][1] != '/' && temp[1][2] != '-' \
		&& temp[1][2] != '_' && !ft_isalnum(temp[1][2]))
		return (1);
	id_check(map, temp);
}
