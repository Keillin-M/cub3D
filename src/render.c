/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthajan <tthajan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 00:00:00 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/29 15:46:54 by tthajan          ###   ########.fr       */
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
	
	// Draw background - ceiling and floor with parsed colors
	int ceiling_color = (game->render) ? game->render->ceiling_color : 0x87CEEB;
	int floor_color = (game->render) ? game->render->floor_color : 0x8B4513;
	
	for (y = 0; y < WIN_HEIGHT; y++)
	{
		for (x = 0; x < WIN_WIDTH; x++)
		{
			if (y < WIN_HEIGHT / 2)
				put_pixel_to_img(img_data, x, y, ceiling_color, line_len); // Ceiling
			else
				put_pixel_to_img(img_data, x, y, floor_color, line_len);   // Floor
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
		
		// Wall direction detection
		int tex_num = 0;  // Texture index
		
		// Determine which texture to use based on wall direction
		if (ray.side == 0) // X-side walls
		{
			if (ray.ray_dir_x > 0)
				tex_num = 3; // EA (East) texture
			else
				tex_num = 2; // WE (West) texture
		}
		else // Y-side walls  
		{
			if (ray.ray_dir_y > 0)
				tex_num = 1; // SO (South) texture
			else
				tex_num = 0; // NO (North) texture
		}
		
		// Calculate wall hit position for texture mapping
		double wall_x;
		int tex_x, tex_y;
		
		if (ray.side == 0)
			wall_x = game->player.y + ray.perp_wall_dist * ray.ray_dir_y;
		else
			wall_x = game->player.x + ray.perp_wall_dist * ray.ray_dir_x;
		wall_x -= floor(wall_x);
		
		// Ensure wall_x is in valid range [0, 1)
		if (wall_x < 0)
			wall_x = 0;
		if (wall_x >= 1)
			wall_x = 0.999;
		
		// Calculate X texture coordinate
		if (game->render && game->render->textures[tex_num].img.img && 
			game->render->textures[tex_num].width > 0)
		{
			tex_x = (int)(wall_x * (double)game->render->textures[tex_num].width);
			if ((ray.side == 0 && ray.ray_dir_x > 0) || 
				(ray.side == 1 && ray.ray_dir_y < 0))
				tex_x = game->render->textures[tex_num].width - tex_x - 1;
			
			// Clamp tex_x to valid range
			if (tex_x < 0)
				tex_x = 0;
			if (tex_x >= game->render->textures[tex_num].width)
				tex_x = game->render->textures[tex_num].width - 1;
		}
		else
		{
			tex_x = 0;
		}
		
		// Draw the wall stripe with texture or fallback colors
		for (y = ray.draw_start; y < ray.draw_end; y++)
		{
			// Get color from texture or use fallback
			if (game->render && game->render->textures[tex_num].img.img && 
				game->render->textures[tex_num].height > 0)
			{
				int d = y * 256 - WIN_HEIGHT * 128 + ray.line_height * 128;
				tex_y = ((d * game->render->textures[tex_num].height) / ray.line_height) / 256;
				
				// Clamp tex_y to valid range
				if (tex_y < 0)
					tex_y = 0;
				if (tex_y >= game->render->textures[tex_num].height)
					tex_y = game->render->textures[tex_num].height - 1;
				
				color = get_texture_pixel(&game->render->textures[tex_num], tex_x, tex_y);
			}
			else
			{
				// Fallback to directional colors
				if (tex_num == 0)
					color = 0x0000FF; // North - Blue
				else if (tex_num == 1)
					color = 0x00FF00; // South - Green  
				else if (tex_num == 2)
					color = 0xFFFF00; // West - Yellow
				else
					color = 0xFF0000; // East - Red
			}
			
			// Apply distance shading
			if (ray.perp_wall_dist > 8)
				color = (color >> 2) & 0x3F3F3F; // Much darker for very far walls
			else if (ray.perp_wall_dist > 4)
				color = (color >> 1) & 0x7F7F7F; // Darker for far walls
			
			// Draw pixels (fill RENDER_STEP pixels to avoid gaps)
			int i;
			for (i = 0; i < RENDER_STEP && (x + i) < WIN_WIDTH; i++)
				put_pixel_to_img(img_data, x + i, y, color, line_len);
		}
	}
}

/**
 * Load texture from XPM file into MLX image
 * @param game: Game structure containing MLX pointer
 * @param texture: Texture structure to store loaded image
 * @param filepath: Path to XPM file
 * @return: 1 on success, 0 on failure
 */
int	load_texture(t_game *game, t_texture *texture, char *filepath)
{
	texture->img.img = mlx_xpm_file_to_image(game->mlx, filepath, 
		&texture->width, &texture->height);
	if (!texture->img.img)
	{
		printf("Error: Failed to load texture: %s\n", filepath);
		return (0);
	}
	
	texture->img.addr = mlx_get_data_addr(texture->img.img,
		&texture->img.bits_per_pixel, &texture->img.line_length,
		&texture->img.endian);
	if (!texture->img.addr)
	{
		mlx_destroy_image(game->mlx, texture->img.img);
		return (0);
	}
	
	texture->img.width = texture->width;
	texture->img.height = texture->height;
	
	return (1);
}

/**
 * Convert RGB string to color value
 * @param rgb_str: String in format "R,G,B"
 * @return: Color as integer (0xRRGGBB)
 */
int	rgb_to_color(char *rgb_str)
{
	char	**rgb;
	int		r, g, b, color;
	
	rgb = ft_split(rgb_str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
	{
		if (rgb)
			free_array(rgb);
		return (0x000000); // Black as fallback
	}
	
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);  
	b = ft_atoi(rgb[2]);
	free_array(rgb);
	
	// Clamp values to 0-255 range
	if (r < 0)
		r = 0;
	if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	if (b > 255)
		b = 255;
	
	color = (r << 16) | (g << 8) | b;
	return (color);
}

/**
 * Initialize textures from parsed texture data
 * @param game: Game structure
 * @return: 1 on success, 0 on failure
 */
int	init_textures(t_game *game)
{
	t_render *render;
	
	// Check if game and tex are valid
	if (!game || !game->tex)
	{
		printf("Error: Invalid game or tex structure\n");
		return (0);
	}
	
	// Allocate render structure if not exists
	if (!game->render)
	{
		game->render = malloc(sizeof(t_render));
		if (!game->render)
		{
			printf("Error: Failed to allocate render structure\n");
			return (0);
		}
	}
	render = game->render;
	
	// Load wall textures (NO=0, SO=1, WE=2, EA=3)
	if (game->tex->texture[0] && game->tex->texture[0][1] &&
		game->tex->texture[1] && game->tex->texture[1][1] &&
		game->tex->texture[2] && game->tex->texture[2][1] &&
		game->tex->texture[3] && game->tex->texture[3][1])
	{
		if (!load_texture(game, &render->textures[0], game->tex->texture[0][1]) ||
			!load_texture(game, &render->textures[1], game->tex->texture[1][1]) ||
			!load_texture(game, &render->textures[2], game->tex->texture[2][1]) ||
			!load_texture(game, &render->textures[3], game->tex->texture[3][1]))
		{
			printf("Error: Failed to load wall textures\n");
			return (0);
		}
	}
	else
	{
		printf("Warning: Texture paths not found, using fallback colors\n");
		// Initialize empty texture structures
		int i;
		for (i = 0; i < 4; i++)
		{
			render->textures[i].img.img = NULL;
			render->textures[i].width = 0;
			render->textures[i].height = 0;
		}
	}
	
	// Set floor and ceiling colors from parsed data
	if (game->tex->texture[4] && game->tex->texture[4][1])
		render->floor_color = rgb_to_color(game->tex->texture[4][1]);     // F color
	else
		render->floor_color = 0x8B4513; // Default brown floor
		
	if (game->tex->texture[5] && game->tex->texture[5][1])
		render->ceiling_color = rgb_to_color(game->tex->texture[5][1]);   // C color
	else
		render->ceiling_color = 0x87CEEB; // Default sky blue ceiling
	
	printf("✅ Enhanced rendering initialized (textures + colors)\n");
	return (1);
}

/**
 * Get pixel color from texture
 * @param texture: Texture to sample from
 * @param x, y: Texture coordinates
 * @return: Color value
 */
int	get_texture_pixel(t_texture *texture, int x, int y)
{
	char *dst;
	
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	
	dst = texture->img.addr + (y * texture->img.line_length + 
		x * (texture->img.bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

// Cleanup implementation
void	ft_destroy_img(t_game *game)
{
	int i;
	
	if (!game->render)
		return;
		
	// Destroy texture images
	for (i = 0; i < 4; i++)
	{
		if (game->render->textures[i].img.img)
		{
			mlx_destroy_image(game->mlx, game->render->textures[i].img.img);
			game->render->textures[i].img.img = NULL;
		}
	}
	
	// Destroy screen buffer if it exists
	if (game->render->screen.img)
	{
		mlx_destroy_image(game->mlx, game->render->screen.img);
		game->render->screen.img = NULL;
	}
	
	// Free render structure
	free(game->render);
	game->render = NULL;
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