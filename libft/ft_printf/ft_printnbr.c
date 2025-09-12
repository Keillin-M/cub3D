/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:58:08 by kmaeda            #+#    #+#             */
/*   Updated: 2025/05/28 15:53:53 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_nbrlen(int n)
{
	int		len;
	long	nb;

	len = 0;
	nb = n;
	if (nb <= 0)
	{
		len++;
		nb = -nb;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_printnbr(int n, int fd)
{
	ft_putnbr_fd(n, fd);
	return (ft_nbrlen(n));
}
