/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:18:41 by kmaeda            #+#    #+#             */
/*   Updated: 2025/05/22 10:47:46 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*t_dest;
	unsigned char	*t_src;

	t_dest = (unsigned char *) dest;
	t_src = (unsigned char *) src;
	if (dest == NULL && src == NULL)
		return (dest);
	while (n > 0)
	{
		*(t_dest++) = *(t_src++);
		n--;
	}
	return (dest);
}
