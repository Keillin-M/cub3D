/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:37:19 by kmaeda            #+#    #+#             */
/*   Updated: 2025/09/25 16:37:58 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_malloc_check(void *ptr)
{
	if (!ptr)
	{
		perror("Malloc failed");
		exit(EXIT_FAILURE);
		return (1);
	}
	return (0);
}
