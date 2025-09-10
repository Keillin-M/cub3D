/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:01:38 by kmaeda            #+#    #+#             */
/*   Updated: 2025/05/28 15:17:18 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_puthex_fd(unsigned long args, int fd, const char *hex)
{
	int			digit;
	int			count;

	count = 0;
	if (args == 0)
	{
		ft_putchar_fd('0', fd);
		return (1);
	}
	if (args >= 16)
		count = ft_puthex_fd(args / 16, fd, hex);
	digit = args % 16;
	ft_putchar_fd(hex[digit], fd);
	count++;
	return (count);
}
