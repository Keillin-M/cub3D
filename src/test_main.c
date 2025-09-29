/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthajan <tthajan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:45:00 by pangjii           #+#    #+#             */
/*   Updated: 2025/09/29 11:00:31 by tthajan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Game loop function - called continuously by mlx_loop_hook
 * @param game: Game structure
 * @return: 0 to continue, non-zero to stop
 */
int game_loop(t_game *game)
{
    // Render single frame
    render_frame(game);
    return (0);
}

/**
 * Initialize game structure for testing
 * @param game: Game structure to initialize
 * @return: 1 on success, 0 on failure
 */
int init_game_test(t_game *game)
{
    // Initialize all pointers to NULL first
    game->mlx = NULL;
    game->win = NULL;
    game->render = NULL;

    // Initialize MiniLibX
    if (!init_mlx(game))
        return (0);

    // Create window
    if (!create_window(game))
    {
        free(game->mlx);
        return (0);
    }

    // Initialize render system
    if (!init_render(game))
    {
        mlx_destroy_window(game->mlx, game->win);
        free(game->mlx);
        return (0);
    }

    return (1);
}

/**
 * Cleanup game resources
 * @param game: Game structure
 */
void cleanup_game(t_game *game)
{
    cleanup_render(game);

    if (game->win)
        mlx_destroy_window(game->mlx, game->win);

    if (game->mlx)
        free(game->mlx);

    printf("Game cleaned up successfully\n");
}

/**
 * Main function for testing rendering
 */
int main(void)
{
    t_game game;

    printf("Starting Cub3D Render Test...\n");

    // Initialize game
    if (!init_game_test(&game))
    {
        printf("Failed to initialize game\n");
        return (1);
    }

    // Set up event handlers
    mlx_hook(game.win, ON_DESTROY, 0, handle_close, &game);
    mlx_hook(game.win, ON_KEYDOWN, 1L << 0, handle_keypress, &game);

    // Set up game loop
    mlx_loop_hook(game.mlx, game_loop, &game);

    printf("Starting game loop... Press ESC to quit\n");

    // Start main loop
    mlx_loop(game.mlx);

    return (0);
}