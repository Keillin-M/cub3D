/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthajan <tthajan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:00:00 by pangjii           #+#    #+#             */
/*   Updated: 2025/09/29 17:23:38 by tthajan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include "cub3d.h"

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_TITLE "Cub3D"

# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF
# define COLOR_WHITE 0xFFFFFF
# define COLOR_BLACK 0x000000
# define COLOR_GRAY 0x808080

# define MINIMAP_SIZE 200
# define MINIMAP_SCALE 20
# define MINIMAP_X 1700
# define MINIMAP_Y 20
# define MINIMAP_WALL_COLOR 0x404040
# define MINIMAP_FLOOR_COLOR 0xC0C0C0
# define MINIMAP_PLAYER_COLOR 0xFF0000
# define MINIMAP_BORDER_COLOR 0x808080

# define PI 3.14159265359
# define TWO_PI 6.28318530718
# define PI_2 1.57079632679
# define PI_3 1.04719755119

# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_UP 126
# define KEY_DOWN 125

# define MOUSE_LEFT 1
# define MOUSE_RIGHT 2
# define MOUSE_MIDDLE 3

# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_MOUSEDOWN 4
# define ON_MOUSEUP 5
# define ON_MOUSEMOVE 6
# define ON_EXPOSE 12
# define ON_DESTROY 17

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_texture
{
	t_img	img;
	int		width;
	int		height;
}	t_texture;

typedef struct s_render
{
	t_img		screen;
	t_texture	textures[4];
	int			floor_color;
	int			ceiling_color;
	double		fps;
	int			frame_count;
	int			show_minimap;
}	t_render;

int	init_mlx(t_game *game);
int	create_window(t_game *game);
int	handle_close(t_game *game);
int	handle_keypress(int keycode, t_game *game);
int	get_texture_pixel(t_texture *texture, int x, int y);

#endif