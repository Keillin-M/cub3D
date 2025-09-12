/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:53:42 by kmaeda            #+#    #+#             */
/*   Updated: 2025/05/30 09:44:15 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_unbrlen(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_printunbr(unsigned int n, int fd)
{
	if (n > 9)
		ft_printunbr(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
	return (ft_unbrlen(n));
}
