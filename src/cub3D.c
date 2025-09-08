/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:26:43 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/08 17:27:13 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	map_ext(char *argv)
{
	int	len;

	len = ft_strlen(argv);
	if (len < 9)
	{
		ft_printf("File extension invalid\n");
		return (1);
	}
	if (!ft_isalnum(argv[len - 5]) && argv[len - 5] != '-'
		&& argv[len - 5] != '_')
	{
		ft_printf("File extension invalid\n");
		return (1);
	}
	if (ft_strncmp(argv + len - 4, ".cub", 4) == 0)
		return (0);
	ft_printf("File extension invalid\n");
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (perror("Wrong number of arguments"), 1);
	if (map_ext(argv[1]))
		return (1);
	ft_init(game);
	if (ft_open(&game, argv))
		return (exit(0), 1);
	if (draw_map(&game, 0, 0))
		game.error = 1;
	if (game.error)
		return (ft_close(&game), 1);
	mlx_hook(game.win, 17, 0, ft_close, &game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_hook(game.win, 2, 1L << 0, ft_key_event, &game);
	mlx_loop(game.mlx);
	return (0);
}
