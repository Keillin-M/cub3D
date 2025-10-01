/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 20:37:45 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/01 20:41:01 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# define MINIMAP_SIZE 200
# define MINIMAP_SCALE 20
# define MINIMAP_X 1700
# define MINIMAP_Y 20
# define WALL_COLOR 0x404040
# define FLOOR_COLOR 0xC0C0C0
# define PLAYER_COLOR 0xFF0000
# define BORDER_COLOR 0x808080

typedef struct s_minimap_data
{
    char	*img_data;
    int		line_len;
    int		dynamic_scale;
}	t_minimap_data;

// Minimap helper functions
void	put_pixel_to_buffer(char *img_data, int x, int y, int color, int line_len);
void	draw_map_tiles(t_game *game, char *img_data, int line_len, int dynamic_scale);
void	draw_player_on_minimap(t_game *game, char *img_data, int line_len, int dynamic_scale);

#endif