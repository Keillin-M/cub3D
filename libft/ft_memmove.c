/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:03:29 by kmaeda            #+#    #+#             */
/*   Updated: 2025/05/22 12:19:53 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_backward(void *dest, const void *src, size_t n)
{
	unsigned char	*t_src;
	unsigned char	*t_dest;

	t_src = (unsigned char *)src + n - 1;
	t_dest = (unsigned char *)dest + n - 1;
	while (n > 0)
	{
		*(t_dest--) = *(t_src--);
		n--;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest == NULL && src == NULL)
		return (dest);
	if (src > dest)
		ft_memcpy(dest, src, n);
	else
		ft_backward(dest, src, n);
	return (dest);
}
