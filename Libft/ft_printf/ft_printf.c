/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:30:33 by kmaeda            #+#    #+#             */
/*   Updated: 2025/05/27 18:11:20 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_conversion(va_list args, char type)
{
	if (type == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1), 1);
	if (type == 's')
		return (ft_printstr(va_arg(args, char *), 1));
	if (type == 'p')
		return (ft_printptr((unsigned long)va_arg(args, void *),
				1, "0123456789abcdef"));
	if (type == 'd' || type == 'i')
		return (ft_printnbr(va_arg(args, int), 1));
	if (type == 'u')
		return (ft_printunbr(va_arg(args, unsigned int), 1));
	if (type == 'x')
		return (ft_puthex_fd(va_arg(args, unsigned int), 
				1, "0123456789abcdef"));
	if (type == 'X')
		return (ft_puthex_fd(va_arg(args, unsigned int), 
				1, "0123456789ABCDEF"));
	if (type == '%')
		return (ft_putchar_fd('%', 1), 1);
	else
		return (-1);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	int		i;
	va_list	args;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			count += ft_conversion(args, format[i]);
		}
		else
		{
			ft_putchar_fd(format[i], 1);
			count += 1;
		}
		i++;
	}
	va_end(args);
	return (count);
}
