/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:23:45 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/10 17:18:18 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <mlx.h>
# include "libft.h"
# include "get_next_line.h"

typedef struct s_map
{
	int		x;
	int		y;
	int		line_len;
	int		total_row;
	int		player;
	int		count;
	char	*line;
	char	**map;
	char	**map_cpy;
	char	***texture;
}	t_map;

#endif
