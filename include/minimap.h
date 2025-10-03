/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 20:37:45 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/03 15:33:48 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# define MINIMAP_SIZE 200
# define MINIMAP_SCALE 20
# define MINIMAP_X 1700
# define MINIMAP_Y 20

typedef struct s_minimap_data
{
	int		line_len;
	int		dynamic_scale;
	char	*img_data;
}	t_minimap_data;

// Minimap
void	draw_map_tiles(t_game *game, char *img_data, int line_len, 
			int dynamic_scale);
void	draw_player_on_minimap(t_game *game, char *img_data, int line_len, 
			int dynamic_scale);
void	draw_minimap_to_buffer(t_game *game, char *img_data, int line_len);

#endif
