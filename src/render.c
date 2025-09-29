/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthajan <tthajan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 00:00:00 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/29 09:52:15 by tthajan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

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

    game->win = mlx_new_window(game->mlx, 800, 600, "cub3D");
    if (!game->win)
    {
        printf("Error: Failed to create window\n");
        return (0);
    }
    printf("Window created: 800x600 - cub3D\n");
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
    if (keycode == 65307) // ESC key
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

/**
 * Put pixel in image data
 */
void	put_pixel_to_img(char *img_data, int x, int y, int color, int line_len)
{
	int	pixel_index;
	
	if (x >= 0 && x < 1920 && y >= 0 && y < 1080)
	{
		pixel_index = (y * line_len) + (x * 4);
		img_data[pixel_index] = color & 0xFF;           // Blue
		img_data[pixel_index + 1] = (color >> 8) & 0xFF;   // Green
		img_data[pixel_index + 2] = (color >> 16) & 0xFF;  // Red
		img_data[pixel_index + 3] = 0;                     // Alpha
	}
}

/**
 * Basic rendering function - draws background and prepares for raycasting
 * @param game: Game structure with mlx, window, and game data
 * @return: 0 on success
 */
int	render(t_game *game)
{
	void	*img;
	char	*img_data;
	int		bpp, line_len, endian;
	int		x, y;
	
	// Create image for better performance
	img = mlx_new_image(game->mlx, 1920, 1080);
	if (!img)
		return (1);
		
	img_data = mlx_get_data_addr(img, &bpp, &line_len, &endian);
	
	// Draw background - ceiling and floor
	for (y = 0; y < 1080; y++)
	{
		for (x = 0; x < 1920; x++)
		{
			if (y < 540)
				put_pixel_to_img(img_data, x, y, 0x87CEEB, line_len); // Ceiling
			else
				put_pixel_to_img(img_data, x, y, 0x8B4513, line_len); // Floor
		}
	}
	
	// TODO: Add raycasting here
	// For now, draw a simple test wall in the center
	for (y = 200; y < 880; y++) // Wall height
	{
		for (x = 950; x < 970; x++) // Wall width (center of screen)
		{
			put_pixel_to_img(img_data, x, y, 0xFF0000, line_len); // Red wall
		}
	}
	
	// Display the rendered frame
	mlx_put_image_to_window(game->mlx, game->win, img, 0, 0);
	mlx_destroy_image(game->mlx, img);
	
	return (0);
}

// Placeholder implementation - TODO: Implement proper cleanup
void	ft_destroy_img(t_game *game)
{
	(void)game; // Suppress unused parameter warning
	// TODO: Implement proper image cleanup
	// This function should clean up any images loaded for textures
}

/**
 * Initialize the game structure and components
 * @param game: Game structure to initialize
 * @param argv: Command line arguments (for map file)
 * @return: 1 on success, 0 on failure
 */
int	init_game(t_game *game, char **argv)
{
	(void)argv; // TODO: Use argv for map loading
	
	// Initialize MiniLibX
	if (!init_mlx(game))
		return (0);
		
	// Create window
	if (!create_window(game))
		return (0);
		
	// TODO: Initialize render system
	game->render = NULL;
	
	// TODO: Load map and initialize player
	// This should be integrated with Person 1's parsing code
	
	return (1);
}

/**
 * Cleanup game resources
 * @param game: Game structure to cleanup
 */
void	cleanup_game(t_game *game)
{
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	
	printf("Game cleaned up successfully\n");
}

/**
 * Main game loop
 * @param game: Game structure
 * @return: Exit status
 */
int	game_loop(t_game *game)
{
	// Set up event handlers
	mlx_hook(game->win, 17, 0, handle_close, game);
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);
	mlx_loop_hook(game->mlx, render, game);
	
	// Start the main loop
	mlx_loop(game->mlx);
	
	return (0);
}