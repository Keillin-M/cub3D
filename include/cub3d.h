/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pangjii <pangjii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:23:45 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/27 16:21:32 by pangjii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <mlx.h>
#include "parser.h"

typedef struct s_player
{
	float x;
	float y;
	float dir_x;
	float dir_y;
	float speed;
	float rot;
	float plane_x;
	float plane_y;
	int turn_dir;
} t_player;

typedef struct s_game
{
	void *mlx;
	void *win;
	t_map *map;
	t_tex *tex;
	t_player player;
	t_render *render;
} t_game;

// Forward declaration for render functions
typedef struct s_render t_render;

// Include rendering functions after forward declaration
#include "render.h"

// Game functions
int init_game(t_game *game, char **argv);
void cleanup_game(t_game *game);
int game_loop(t_game *game);

#endif
