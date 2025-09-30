/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthajan <tthajan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:23:45 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/30 12:37:11 by tthajan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include "parser.h"
# include "render.h"

typedef struct s_render	t_render;

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
}	t_game;
void	ft_init_player(t_player *player, t_map *map);
int		ft_key_event(int keycode, t_game *game);
void	adjust_fov(t_player *player, float delta);
void	toggle_minimap(t_game *game);
int		ft_close(t_game *game);
void	ft_destroy_img(t_game *game);
int		render(t_game *game);
int		init_game(t_game *game, char **argv);
void	cleanup_game(t_game *game);
int		game_loop(t_game *game);
int		init_textures(t_game *game);
int		load_texture(t_game *game, t_texture *texture, char *filepath);
int		get_texture_pixel(t_texture *texture, int x, int y);
int		rgb_to_color(char *rgb_str);
void	draw_performance_info(t_game *game);
void	render_background_optimized(char *img_data, int line_len,
			int ceiling_color, int floor_color);
void	draw_minimap(t_game *game);
void	draw_minimap_to_buffer(t_game *game, char *img_data, int line_len);
void	draw_minimap_border(t_game *game);
void	draw_minimap_tile(t_game *game, int x, int y, int color);
void	draw_minimap_player(t_game *game);

#endif
