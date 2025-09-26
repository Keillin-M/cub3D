/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:23:45 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/26 16:05:43 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include "parser.h"

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_tex		*tex;
	t_player	player;
}	t_game;

typedef struct s_player
{
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
	float	speed;
	float	rot;
	float	plane_x;
	float	plane_y;
	int		turn_dir;
}	t_player;

// Game functions

#endif
