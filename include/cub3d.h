/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:23:45 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/15 18:58:47 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <mlx.h>
# include "libft.h"
# include "get_next_line.h"

typedef struct s_tex
{
	int			no;
	int			so;
	int			we;
	int			ea;
	int			c;
	int			f;
	int			count;
	char		***texture;
}	t_tex;

typedef struct s_map
{
	int			x;
	int			y;
	int			fd;
	int			width;
	int			height;
	int			player;
	int			count;
	char		*fd_name;
	char		*line;
	char		**map;
	char		**map_cpy;
	char		***texture;
}	t_map;

#endif
