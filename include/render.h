/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthajan <tthajan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:00:00 by pangjii           #+#    #+#             */
/*   Updated: 2025/09/29 16:35:54 by tthajan          ###   ########.fr       */
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

/* Minimap constants */
#define MINIMAP_SIZE 200        /* Minimap dimensions */
#define MINIMAP_SCALE 20        /* Pixels per map unit */
#define MINIMAP_X (WIN_WIDTH - MINIMAP_SIZE - 20)   /* Top-right position */
#define MINIMAP_Y 20
#define MINIMAP_WALL_COLOR 0x404040     /* Dark gray for walls */
#define MINIMAP_FLOOR_COLOR 0xC0C0C0    /* Light gray for floor */
#define MINIMAP_PLAYER_COLOR 0xFF0000   /* Red dot for player */
#define MINIMAP_BORDER_COLOR 0x808080   /* Gray border */

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
    int show_minimap;      /* Toggle minimap display */
} t_render;

/* ************************************************************************** */
/*                           FUNCTION PROTOTYPES                             */
/* ************************************************************************** */

/* Initialization functions */
int init_mlx(t_game *game);

/* Window management */
int create_window(t_game *game);
int handle_close(t_game *game);
int handle_keypress(int keycode, t_game *game);



/* Texture functions */
int get_texture_pixel(t_texture *texture, int x, int y);



#endif