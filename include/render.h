/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:00:00 by pangjii           #+#    #+#             */
/*   Updated: 2025/10/02 18:02:32 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_game	t_game;

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_TITLE "Cub3D"

# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF
# define COLOR_WHITE 0xFFFFFF
# define COLOR_BLACK 0x000000
# define COLOR_GRAY 0x808080
# define COLOR_L_BLUE 0x87CEEB
# define COLOR_BROWN 0x8B4513

# define PI 3.14159265359
# define TWO_PI 6.28318530718
# define PI_2 1.57079632679
# define PI_3 1.04719755119

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
	int		render_step;
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

typedef struct s_wall_data
{
	int	tex_num;
	int	tex_x;
	int	y;
}	t_wall_data;

//MLX functions
int		init_mlx(t_game *game);
int		create_window(t_game *game);

//Rendering functions
int		render(t_game *game);
void	draw_wall_col(t_game *game, t_ray *ray, t_img *img, int x);
void	put_pixel_to_img(t_img *img, int x, int y, int color);
int		get_render_step(t_game *game);
void	update_fps(t_game *game);

//Texture functions
int		load_texture(t_game *game, t_texture *tex, char *filepath);
int		init_textures(t_game *game);
int		get_texture_pixel(t_texture *tex, int x, int y);
int		get_wall_color(t_game *game, t_ray *ray, t_wall_data *wall_data);
int		get_wall_texture(t_ray *ray);
void	set_colors(t_game *game, t_render *render);

//Raycasting functions
int		init_img_buffer(t_game *game, t_img *img);
void	init_ray(t_ray *ray, t_game *game, int x);
void	perform_dda(t_ray *ray, t_game *game);
void	wall_distance(t_ray *ray, t_game *game);
void	wall_height(t_ray *ray);
void	texture_coords(t_ray *ray, t_game *game, int tex_num, int *tex_x);

#endif
