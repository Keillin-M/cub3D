/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:30:00 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/02 18:01:55 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

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
	int			floor_r;
	int			floor_g;
	int			floor_b;
	int			ceiling_r;
	int			ceiling_g;
	int			ceiling_b;
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
	char		dir;
	char		*fd_name;
	char		*line;
	char		**map;
	char		**map_cpy;
	char		**layout;
	char		***texture;
}	t_map;

typedef struct s_player	t_player;

// Initialization
void	ft_init(t_map *map, t_tex *tex);
void	ft_init_player(t_player *player, t_map *map);

// File Reading and Parsing
int		read_file(t_map *map, t_tex *tex, char **argv);
int		read_line(t_map *map, t_tex *tex);

// Map Validation
int		map_check(t_map *map);
int		texture_check(t_tex *tex, t_map *map);
int		texture_file_check(t_tex *tex);

#endif
