/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthajan <tthajan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:35:00 by pangjii           #+#    #+#             */
/*   Updated: 2025/09/29 11:00:24 by tthajan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Initialize image buffer for drawing
 * @param game: Game structure containing mlx pointer
 * @param img: Image structure to initialize
 * @param width: Image width
 * @param height: Image height
 * @return: 1 on success, 0 on failure
 */
int init_img(t_game *game, t_img *img, int width, int height)
{
    img->img = mlx_new_image(game->mlx, width, height);
    if (!img->img)
    {
        printf("Error: Failed to create image buffer\n");
        return (0);
    }

    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
                                  &img->line_length, &img->endian);
    img->width = width;
    img->height = height;

    printf("Image buffer created: %dx%d\n", width, height);
    return (1);
}

/**
 * Put a pixel at specified coordinates with given color
 * @param img: Image structure
 * @param x: X coordinate
 * @param y: Y coordinate
 * @param color: Color value
 */
void put_pixel(t_img *img, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= img->width || y < 0 || y >= img->height)
        return;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

/**
 * Get pixel color at specified coordinates
 * @param img: Image structure
 * @param x: X coordinate
 * @param y: Y coordinate
 * @return: Color value at the pixel
 */
int get_pixel(t_img *img, int x, int y)
{
    char *src;

    if (x < 0 || x >= img->width || y < 0 || y >= img->height)
        return (0);

    src = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    return (*(unsigned int *)src);
}

/**
 * Clear entire image with specified color
 * @param img: Image structure
 * @param color: Color to fill with
 */
void clear_image(t_img *img, int color)
{
    int x;
    int y;

    y = 0;
    while (y < img->height)
    {
        x = 0;
        while (x < img->width)
        {
            put_pixel(img, x, y, color);
            x++;
        }
        y++;
    }
}

/**
 * Draw a rectangle filled with specified color
 * @param img: Image structure
 * @param x: Top-left X coordinate
 * @param y: Top-left Y coordinate
 * @param width: Rectangle width
 * @param height: Rectangle height
 * @param color: Fill color
 */
void draw_rect(t_img *img, int x, int y, int width, int height, int color)
{
    int i;
    int j;

    j = 0;
    while (j < height)
    {
        i = 0;
        while (i < width)
        {
            put_pixel(img, x + i, y + j, color);
            i++;
        }
        j++;
    }
}