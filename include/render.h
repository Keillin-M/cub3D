/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pangjii <pangjii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:00:00 by pangjii           #+#    #+#             */
/*   Updated: 2025/09/27 16:21:32 by pangjii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
#define RENDER_H

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "cub3d.h"

/* ************************************************************************** */
/*                               CONSTANTS                                    */
/* ************************************************************************** */

#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080
#define WIN_TITLE "Cub3D"

/* Colors */
#define COLOR_RED 0xFF0000
#define COLOR_GREEN 0x00FF00
#define COLOR_BLUE 0x0000FF
#define COLOR_WHITE 0xFFFFFF
#define COLOR_BLACK 0x000000
#define COLOR_GRAY 0x808080

/* Math constants */
#define PI 3.14159265359
#define TWO_PI 6.28318530718
#define PI_2 1.57079632679
#define PI_3 1.04719755119

/* Key codes (macOS) */
#define KEY_ESC 53
#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_LEFT 123
#define KEY_RIGHT 124
#define KEY_UP 126
#define KEY_DOWN 125

/* Mouse codes */
#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2
#define MOUSE_MIDDLE 3

/* Event codes */
#define ON_KEYDOWN 2
#define ON_KEYUP 3
#define ON_MOUSEDOWN 4
#define ON_MOUSEUP 5
#define ON_MOUSEMOVE 6
#define ON_EXPOSE 12
#define ON_DESTROY 17

/* ************************************************************************** */
/*                               STRUCTURES                                   */
/* ************************************************************************** */

/* Image data structure for MiniLibX */
typedef struct s_img
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
    int width;
    int height;
} t_img;

/* Ray structure for raycasting */
typedef struct s_ray
{
    double camera_x;       /* X-coordinate on camera plane */
    double ray_dir_x;      /* X-direction of ray */
    double ray_dir_y;      /* Y-direction of ray */
    int map_x;             /* Current map grid position X */
    int map_y;             /* Current map grid position Y */
    double side_dist_x;    /* Distance to next X-side */
    double side_dist_y;    /* Distance to next Y-side */
    double delta_dist_x;   /* Distance from one X-side to next */
    double delta_dist_y;   /* Distance from one Y-side to next */
    double perp_wall_dist; /* Perpendicular distance to wall */
    int step_x;            /* Step direction in X */
    int step_y;            /* Step direction in Y */
    int hit;               /* Was a wall hit? */
    int side;              /* Which side was hit? (0=X-side, 1=Y-side) */
    int line_height;       /* Height of line to draw on screen */
    int draw_start;        /* Lowest pixel to fill in current stripe */
    int draw_end;          /* Highest pixel to fill in current stripe */
} t_ray;

/* Texture data structure */
typedef struct s_texture
{
    t_img img;
    int width;
    int height;
} t_texture;

/* Rendering data structure */
typedef struct s_render
{
    t_img screen;          /* Main screen buffer */
    t_texture textures[4]; /* Wall textures (N, S, E, W) */
    int floor_color;       /* Floor color */
    int ceiling_color;     /* Ceiling color */
    double fps;            /* Frames per second */
    int frame_count;       /* Frame counter */
} t_render;

/* ************************************************************************** */
/*                           FUNCTION PROTOTYPES                             */
/* ************************************************************************** */

/* Initialization functions */
int init_mlx(t_game *game);
int init_img(t_game *game, t_img *img, int width, int height);
int init_render(t_game *game);
void cleanup_render(t_game *game);

/* Window management */
int create_window(t_game *game);
int handle_close(t_game *game);
int handle_keypress(int keycode, t_game *game);
int handle_keyrelease(int keycode, t_game *game);

/* Drawing functions */
void put_pixel(t_img *img, int x, int y, int color);
int get_pixel(t_img *img, int x, int y);
void clear_image(t_img *img, int color);
void draw_line(t_img *img, int x0, int y0, int x1, int y1, int color);
void draw_rect(t_img *img, int x, int y, int width, int height, int color);

/* Raycasting functions */
void cast_rays(t_game *game);
void cast_single_ray(t_game *game, int x);
void init_ray(t_game *game, t_ray *ray, int x);
void perform_dda(t_game *game, t_ray *ray);
void calculate_wall_distance(t_ray *ray);
void calculate_wall_height(t_ray *ray);

/* Rendering functions */
void render_frame(t_game *game);
void render_background(t_game *game);
void render_walls(t_game *game);
void render_wall_stripe(t_game *game, t_ray *ray, int x);

/* Texture functions */
int load_textures(t_game *game);
void free_textures(t_game *game);
int get_texture_pixel(t_texture *texture, int x, int y);
void apply_texture_to_wall(t_game *game, t_ray *ray, int x);

/* Utility functions */
double deg_to_rad(double degrees);
double rad_to_deg(double radians);
int create_color(int r, int g, int b);
void get_rgb(int color, int *r, int *g, int *b);

/* Debug functions */
void print_ray_info(t_ray *ray);
void print_player_info(t_player *player);

#endif