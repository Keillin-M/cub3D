/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:44:08 by kmaeda            #+#    #+#             */
/*   Updated: 2025/05/15 13:45:31 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_src;
	size_t	len_dst;
	size_t	len_cpy;

	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	if (size <= len_dst)
		return (size + len_src);
	len_cpy = size - len_dst - 1;
	if (len_cpy > len_src)
		len_cpy = len_src;
	ft_memcpy(dst + len_dst, src, len_cpy);
	dst[len_dst + len_cpy] = '\0';
	return (len_dst + len_src);
}
