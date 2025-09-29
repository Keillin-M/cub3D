/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthajan <tthajan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:40:00 by pangjii           #+#    #+#             */
/*   Updated: 2025/09/29 11:00:34 by tthajan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Initialize render system
 * @param game: Game structure
 * @return: 1 on success, 0 on failure
 */
int init_render(t_game *game)
{
    game->render = malloc(sizeof(t_render));
    if (!game->render)
    {
        printf("Error: Failed to allocate render structure\n");
        return (0);
    }

    // Initialize screen buffer
    if (!init_img(game, &game->render->screen, WIN_WIDTH, WIN_HEIGHT))
    {
        free(game->render);
        return (0);
    }

    // Set default colors
    game->render->ceiling_color = COLOR_GRAY;
    game->render->floor_color = COLOR_BLACK;

    printf("Render system initialized\n");
    return (1);
}

/**
 * Render background (ceiling and floor)
 * @param game: Game structure
 */
void render_background(t_game *game)
{
    // Draw ceiling (top half)
    draw_rect(&game->render->screen, 0, 0, WIN_WIDTH, WIN_HEIGHT / 2,
              game->render->ceiling_color);

    // Draw floor (bottom half)
    draw_rect(&game->render->screen, 0, WIN_HEIGHT / 2, WIN_WIDTH,
              WIN_HEIGHT / 2, game->render->floor_color);
}

/**
 * Test function - draw some basic shapes to verify pixel drawing
 * @param game: Game structure
 */
void test_pixel_drawing(t_game *game)
{
    // Draw a red rectangle in center
    draw_rect(&game->render->screen, WIN_WIDTH / 2 - 50, WIN_HEIGHT / 2 - 50,
              100, 100, COLOR_RED);

    // Draw green border
    draw_rect(&game->render->screen, WIN_WIDTH / 2 - 55, WIN_HEIGHT / 2 - 55,
              110, 5, COLOR_GREEN); // Top
    draw_rect(&game->render->screen, WIN_WIDTH / 2 - 55, WIN_HEIGHT / 2 + 50,
              110, 5, COLOR_GREEN); // Bottom
    draw_rect(&game->render->screen, WIN_WIDTH / 2 - 55, WIN_HEIGHT / 2 - 50,
              5, 100, COLOR_GREEN); // Left
    draw_rect(&game->render->screen, WIN_WIDTH / 2 + 50, WIN_HEIGHT / 2 - 50,
              5, 100, COLOR_GREEN); // Right
}

/**
 * Render single frame
 * @param game: Game structure
 */
void render_frame(t_game *game)
{
    // Clear and render background
    render_background(game);

    // Test drawing
    test_pixel_drawing(game);

    // Display the rendered frame
    mlx_put_image_to_window(game->mlx, game->win, game->render->screen.img, 0, 0);
}

/**
 * Cleanup render resources
 * @param game: Game structure
 */
void cleanup_render(t_game *game)
{
    if (game->render)
    {
        if (game->render->screen.img)
            mlx_destroy_image(game->mlx, game->render->screen.img);
        free(game->render);
        printf("Render resources cleaned up\n");
    }
}