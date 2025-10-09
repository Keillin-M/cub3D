/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:00:00 by pangjii           #+#    #+#             */
/*   Updated: 2025/10/09 12:02:45 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <mlx.h>
# include <math.h>

typedef struct s_game	t_game;

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_TITLE "Cub3D"

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

//Rendering functions
int		render(t_game *game);
void	update_fps(t_game *game);

//Drawing functions
void	draw_wall_col(t_game *game, t_ray *ray, t_img *img, int x);
void	texture_coords(t_ray *ray, t_game *game, int tex_num, int *tex_x);
int		get_wall_color(t_game *game, t_ray *ray, t_wall_data *wall_data);
int		get_wall_texture(t_ray *ray);

//Texture functions
int		load_texture(t_game *game, t_texture *tex, char *filepath);
int		init_textures(t_game *game);
int		set_colors(t_game *game, t_render *render);
int		get_texture_pixel(t_texture *tex, int x, int y);

//Raycasting functions
void	init_ray(t_ray *ray, t_game *game, int x);
void	perform_dda(t_ray *ray, t_game *game);
void	wall_distance(t_ray *ray, t_game *game);
void	wall_height(t_ray *ray);

#endif
