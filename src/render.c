/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pangjii <pangjii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:30:00 by pangjii           #+#    #+#             */
/*   Updated: 2025/09/27 16:29:26 by pangjii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Initialize MiniLibX connection
 * @param game: Game structure containing mlx pointer
 * @return: 1 on success, 0 on failure
 */
int init_mlx(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        printf("Error: Failed to initialize MiniLibX\n");
        return (0);
    }
    printf("MiniLibX initialized successfully\n");
    return (1);
}

/**
 * Create window with specified dimensions
 * @param game: Game structure containing mlx and win pointers
 * @return: 1 on success, 0 on failure
 */
int create_window(t_game *game)
{
    if (!game->mlx)
    {
        printf("Error: MiniLibX not initialized\n");
        return (0);
    }

    game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
    if (!game->win)
    {
        printf("Error: Failed to create window\n");
        return (0);
    }
    printf("Window created: %dx%d - %s\n", WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
    return (1);
}

/**
 * Handle window close event
 * @param game: Game structure
 * @return: Always returns 0 to exit program
 */
int handle_close(t_game *game)
{
    printf("Closing window...\n");
    cleanup_game(game);
    exit(0);
    return (0);
}

/**
 * Handle key press events
 * @param keycode: The key that was pressed
 * @param game: Game structure
 * @return: 1 on success, 0 on failure
 */
int handle_keypress(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
    {
        printf("ESC pressed - closing game\n");
        handle_close(game);
    }
    else
    {
        printf("Key pressed: %d\n", keycode);
    }
    return (1);
}