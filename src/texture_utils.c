/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:18:56 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/12 14:31:17 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>

int	texture_file_check(t_tex *texture)
{
	fd = open(tex->path[i], O_RDONLY);
	if (fd < 0)
		return (perror("Error\nCannot open texture file", 1));
	close (fd);
}
