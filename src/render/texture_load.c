/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:34:16 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/02 15:14:27 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_texture(t_game *game, t_texture *tex, char *filepath)
{
	tex->img.img = mlx_xpm_file_to_image(game->mlx, filepath, 
			&tex->width, &tex->height);
	if (!tex->img.img)
	{
		printf("Error: Failed to load texture: %s\n", filepath);
		return (0);
	}
	tex->img.addr = mlx_get_data_addr(tex->img.img,
			&tex->img.bpp, &tex->img.line_len,
			&tex->img.endian);
	if (!tex->img.addr)
	{
		mlx_destroy_image(game->mlx, tex->img.img);
		return (0);
	}
	tex->img.width = tex->width;
	tex->img.height = tex->height;
	return (1);
}

static int	alloc_render_struct(t_game *game)
{
	if (!game->render)
	{
		game->render = malloc(sizeof(t_render));
		if (!game->render)
		{
			printf("Error: Failed to allocate render structure\n");
			return (0);
		}
	}
	return (1);
}

static void	init_texture_arrays(t_render *render)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		render->textures[i].img.img = NULL;
		render->textures[i].width = 0;
		render->textures[i].height = 0;
		render->textures[i].img.addr = NULL;
		i++;
	}
	render->screen.img = NULL;
}

static void	load_wall_textures(t_game *game, t_render *render)
{
	if (game->tex->texture[0] && game->tex->texture[0][1] 
		&& game->tex->texture[1] && game->tex->texture[1][1] 
		&& game->tex->texture[2] && game->tex->texture[2][1] 
		&& game->tex->texture[3] && game->tex->texture[3][1])
	{
		if (!load_texture(game, &render->textures[0], game->tex->texture[0][1])
			|| !load_texture(game, &render->textures[1], 
				game->tex->texture[1][1])
			|| !load_texture(game, &render->textures[2], 
				game->tex->texture[2][1])
			|| !load_texture(game, &render->textures[3], 
				game->tex->texture[3][1]))
		{
			printf("Error: One or more wall textures failed to load\n");
		}
	}
	else
	{
		printf("Warning: One or more wall texture paths are missing\n");
	}
}

int	init_textures(t_game *game)
{
	t_render	*render;

	if (!game || !game->tex)
	{
		printf("Error: Invalid game or tex structure\n");
		return (0);
	}
	if (!alloc_render_struct(game))
		return (0);
	render = game->render;
	init_texture_arrays(render);
	load_wall_textures(game, render);
	set_colors(game, render);
	render->show_minimap = 1;
	render->fps = 60;
	render->frame_count = 0;
	printf("✅ Enhanced rendering initialized (textures + colors)\n");
	return (1);
}
