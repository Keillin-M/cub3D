/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:23:45 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/16 18:38:12 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <mlx.h>
# include "../libft/libft.h"

typedef struct s_tex
{
	int			no;
	int			so;
	int			we;
	int			ea;
	int			c;
	int			f;
	int			count;
	char		***texture;
}	t_tex;

typedef struct s_map
{
	int			x;
	int			y;
	int			fd;
	int			width;
	int			height;
	int			player;
	int			count;
	char			dir;
	char		*fd_name;
	char		*line;
	char		**map;
	char		**map_cpy;
	char		***texture;
}	t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
}

// Initialization
void	ft_init(t_map *map, t_tex *tex);

// File Reading and Parsing
int		read_file(t_map *map, t_tex *tex, char **argv);
int		read_line(t_map *map, t_tex *tex);

// Map Processing
int		skip_to_map(t_map *map);
int		map_size(t_map *map);
int		draw_map(t_map *map);

// Map Validation
int		map_check(t_map *map);
int		char_check(t_map *map, int i, int j);
int		flood_fill(t_map *map, int y, int x);

// Texture Processing
int		texture_check(t_tex *tex, t_map *map);
int		texture_file_check(t_tex *tex);
int		color_check(char *temp);
void	id_check(t_tex *tex, char **temp);

// Memory Management
void	free_array(char **array);
void	ft_clean_map(t_map *map);

#endif
