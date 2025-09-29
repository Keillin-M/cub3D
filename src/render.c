/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthajan <tthajan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 00:00:00 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/29 11:13:23 by tthajan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <math.h>

// Local render constants (WIN_WIDTH and WIN_HEIGHT are defined in render.h)
#define RENDER_STEP 2    // Render every 2nd pixel for performance

// Forward declarations for internal functions
void	render_walls_raycast(t_game *game, char *img_data, int line_len);

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

    game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
    if (!game->win)
    {
        printf("Error: Failed to create window\n");
        return (0);
    }
    printf("Window created: %dx%d - cub3D\n", WIN_WIDTH, WIN_HEIGHT);
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
	
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		pixel_index = (y * line_len) + (x * 4);
		img_data[pixel_index] = color & 0xFF;           // Blue
		img_data[pixel_index + 1] = (color >> 8) & 0xFF;   // Green
		img_data[pixel_index + 2] = (color >> 16) & 0xFF;  // Red
		img_data[pixel_index + 3] = 0;                     // Alpha
	}
}



/**
 * Basic rendering function with integrated raycasting
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
	img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!img)
		return (1);
		
	img_data = mlx_get_data_addr(img, &bpp, &line_len, &endian);
	
	// Draw background - ceiling and floor
	for (y = 0; y < WIN_HEIGHT; y++)
	{
		for (x = 0; x < WIN_WIDTH; x++)
		{
			if (y < WIN_HEIGHT / 2)
				put_pixel_to_img(img_data, x, y, 0x87CEEB, line_len); // Ceiling
			else
				put_pixel_to_img(img_data, x, y, 0x8B4513, line_len); // Floor
		}
	}
	
	// Perform raycasting and draw walls
	render_walls_raycast(game, img_data, line_len);
	
	// Display the rendered frame
	mlx_put_image_to_window(game->mlx, game->win, img, 0, 0);
	mlx_destroy_image(game->mlx, img);
	
	return (0);
}

/**
 * Perform raycasting and render walls
 * @param game: Game structure  
 * @param img_data: Image buffer to draw to
 * @param line_len: Line length for image buffer
 */
void	render_walls_raycast(t_game *game, char *img_data, int line_len)
{
	int		x, y;
	t_ray	ray;
	int		color;
	
	// Cast a ray for each screen column (every nth pixel for performance)  
	for (x = 0; x < WIN_WIDTH; x += RENDER_STEP)
	{
		// Initialize ray
		ray.camera_x = 2 * x / (double)WIN_WIDTH - 1;
		ray.ray_dir_x = game->player.dir_x + game->player.plane_x * ray.camera_x;
		ray.ray_dir_y = game->player.dir_y + game->player.plane_y * ray.camera_x;
		
		// Current position
		ray.map_x = (int)game->player.x;
		ray.map_y = (int)game->player.y;
		
		// Calculate delta distances
		ray.delta_dist_x = (ray.ray_dir_x == 0) ? 1e30 : fabs(1 / ray.ray_dir_x);
		ray.delta_dist_y = (ray.ray_dir_y == 0) ? 1e30 : fabs(1 / ray.ray_dir_y);
		
		// Calculate step and initial side_dist
		if (ray.ray_dir_x < 0)
		{
			ray.step_x = -1;
			ray.side_dist_x = (game->player.x - ray.map_x) * ray.delta_dist_x;
		}
		else
		{
			ray.step_x = 1;
			ray.side_dist_x = (ray.map_x + 1.0 - game->player.x) * ray.delta_dist_x;
		}
		
		if (ray.ray_dir_y < 0)
		{
			ray.step_y = -1;
			ray.side_dist_y = (game->player.y - ray.map_y) * ray.delta_dist_y;
		}
		else
		{
			ray.step_y = 1;
			ray.side_dist_y = (ray.map_y + 1.0 - game->player.y) * ray.delta_dist_y;
		}
		
		// Perform DDA
		ray.hit = 0;
		while (ray.hit == 0)
		{
			if (ray.side_dist_x < ray.side_dist_y)
			{
				ray.side_dist_x += ray.delta_dist_x;
				ray.map_x += ray.step_x;
				ray.side = 0;
			}
			else
			{
				ray.side_dist_y += ray.delta_dist_y;
				ray.map_y += ray.step_y;
				ray.side = 1;
			}
			
			// Check if ray has hit a wall
			if (ray.map_x < 0 || ray.map_x >= game->map->width || 
				ray.map_y < 0 || ray.map_y >= game->map->height ||
				game->map->map[ray.map_y][ray.map_x] == '1')
			{
				ray.hit = 1;
			}
		}
		
		// Calculate distance
		if (ray.side == 0)
			ray.perp_wall_dist = (ray.map_x - game->player.x + (1 - ray.step_x) / 2) / ray.ray_dir_x;
		else
			ray.perp_wall_dist = (ray.map_y - game->player.y + (1 - ray.step_y) / 2) / ray.ray_dir_y;
		
		// Calculate line height
		ray.line_height = (int)(WIN_HEIGHT / ray.perp_wall_dist);
		
		// Calculate draw start and end
		ray.draw_start = -ray.line_height / 2 + WIN_HEIGHT / 2;
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		ray.draw_end = ray.line_height / 2 + WIN_HEIGHT / 2;
		if (ray.draw_end >= WIN_HEIGHT)
			ray.draw_end = WIN_HEIGHT - 1;
		
		// Choose wall color - different colors for different sides and distance
		if (ray.side == 0)
			color = 0xFF0000; // Red for X-side walls
		else
			color = 0x800000; // Darker red for Y-side walls
		
		// Apply distance shading
		if (ray.perp_wall_dist > 8)
			color = color >> 2; // Much darker for very far walls
		else if (ray.perp_wall_dist > 4)
			color = color >> 1; // Darker for far walls
		
		// Draw the wall stripe (fill RENDER_STEP pixels to avoid gaps)
		for (y = ray.draw_start; y < ray.draw_end; y++)
		{
			int i;
			for (i = 0; i < RENDER_STEP && (x + i) < WIN_WIDTH; i++)
				put_pixel_to_img(img_data, x + i, y, color, line_len);
		}
	}
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