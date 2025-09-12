/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:59:54 by kmaeda            #+#    #+#             */
/*   Updated: 2025/05/28 19:36:24 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "../libft.h"

int	ft_printf(const char *format, ...);
int	ft_puthex_fd(unsigned long args, int fd, const char *hex);
int	ft_printnbr(int n, int fd);
int	ft_printunbr(unsigned int n, int fd);
int	ft_printstr(char *s, int fd);
int	ft_printptr(unsigned long args, int fd, const char *hex);

#endif
