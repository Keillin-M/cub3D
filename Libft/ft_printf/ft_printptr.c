/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:10:03 by kmaeda            #+#    #+#             */
/*   Updated: 2025/05/30 09:43:23 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_printptr(unsigned long args, int fd, const char *hex)
{
	int	count;

	count = 0;
	if (args == 0)
		count = ft_printstr("(nil)", fd);
	else 
	{
		count = ft_printstr("0x", fd);
		count += ft_puthex_fd(args, fd, hex);
	}
	return (count);
}
