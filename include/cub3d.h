/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:23:45 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/03 15:37:34 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include "parser.h"
# include "render.h"
# include "colors.h"

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
	float	fov;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_tex		*tex;
	t_player	player;
	t_render	*render;
	t_ray		*ray;
	t_img		*img;
}	t_game;

// Memory Management
void	free_array(char **array);
void	ft_clean_map(t_map *map);
void	ft_clean_tex(t_tex *tex);
void	ft_destroy_img(t_game *game);
int		ft_malloc_check(void *ptr);
int		ft_close(t_game *game);

// Events and Movement
int		ft_key_event(int keycode, t_game *game);
void	ft_rotate(t_player *player, char rot);
int		ft_mouse_event(int x, int y, t_game *game);
void	ft_move(t_player *player, t_map *map, char mov);
void	update_player_rotation(t_game *game, int delta_x, 
			float mouse_sensitivity);

//Welcome banner
void	print_welcome_banner(void);

#endif
