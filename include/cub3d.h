/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthajan <tthajan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:23:45 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/29 09:40:18 by tthajan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include "parser.h"

// Forward declaration for render functions
typedef struct s_render t_render;

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

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_tex		*tex;
	t_player	player;
	t_render	*render;
}	t_game;

// Include rendering functions after forward declaration
# include "render.h"

// Game functions
void	ft_init_player(t_player *player, t_map *map);
int		ft_key_event(int keycode, t_game *game);
int		ft_close(t_game *game);
void	ft_destroy_img(t_game *game);
int		render(t_game *game);
int		init_game(t_game *game, char **argv);
void	cleanup_game(t_game *game);
int		game_loop(t_game *game);

#endif
