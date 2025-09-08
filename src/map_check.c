/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:19:59 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/08 18:23:27 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	char_check(t_game *game, int j, int i)
{
	if (game->map_cpy[j][i] != '1' && game->map_cpy[j][i] != '0' \
			&& game->map_cpy[j][i] != 'P' && game->map_cpy[j][i] != 'E' \
				&& game->map_cpy[j][i] != 'C' && game->map_cpy[j][i] != 'R')
		return (perror("Invalid char in map"), 1);
	if (game->map_cpy[j][i] == 'P')
	{
		game->p++;
		game->x = i;
		game->y = j;
	}
	if (game->map_cpy[j][i] == 'E')
	{
		game->e++;
		game->x_exit = i;
		game->y_exit = j;
	}
	if (game->map_cpy[j][i] == 'C')
		game->count++;
	if (game->map_cpy[j][i] == 'R')
		bonus_check(game, j, i);
	return (0);
}

static int	map_check(t_game *game, int j, int i)
{
	if ((game->total_row * game->h > 1080)
		|| (game->line_len * game->w > 1920))
		return (perror("Map is too big"), 1);
	while (j < game->total_row)
	{
		i = 0;
		while (i < game->line_len)
		{
			if (char_check(game, j, i))
				return (1);
			i++;
		}
		j++;
	}
	if (game->p != 1 || game->e != 1 || game->count < 1)
		return (perror("Must be only one player, one exit and \
				at least one collectible"), 1);
	return (0);
}

static int	map_wall(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->line_len)
	{
		if (game->map_cpy[0][i] != '1' 
			|| game->map_cpy[game->total_row - 1][i] != '1')
			return (perror("Map not surrounded by wall"), 1);
		i++;
	}
	i = 0;
	while (i < game->total_row)
	{
		if (game->map_cpy[i][0] != '1' 
			|| game->map_cpy[i][game->line_len - 1] != '1')
			return (perror("Map not surrounded by wall"), 1);
		i++;
	}
	return (0);
}

static int	flood_fill(t_game *game, int y, int x)
{
	if (y < 0 || x < 0 || y >= game->total_row || x >= game->line_len)
		return (1);
	if (game->map_cpy[y][x] == '1' || game->map_cpy[y][x] == 'X'
		|| game->map_cpy[y][x] == 'A')
		return (0);
	if (game->map_cpy[y][x] == 'E')
	{
		game->map_cpy[y][x] = 'A';
		return (0);
	}
	game->map_cpy[y][x] = 'X';
	flood_fill(game, y - 1, x);
	flood_fill(game, y + 1, x);
	flood_fill(game, y, x + 1);
	flood_fill(game, y, x - 1);
	return (0);
}

int	valid_map(t_game *game, int i, int j)
{
	if (game->total_row < 3 || game->line_len < 3)
		return (perror("Map is too small"), 1);
	if (map_check(game, 0, 0))
		return (1);
	if (map_wall(game))
		return (1);
	if (flood_fill(game, game->y, game->x))
		return (perror("Invalid map"), 1);
	while (i < game->total_row)
	{
		j = 0;
		while (j < game->line_len)
		{
			if (game->map_cpy[i][j] == 'C' || game->map_cpy[i][j] == 'E')
				return (perror("Invalid map: cannot reach \
					exit or collectible"), 1);
			j++;
		}
		i++;
	}
	return (0);
}
