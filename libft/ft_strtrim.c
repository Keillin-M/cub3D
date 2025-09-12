/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:47:56 by kmaeda            #+#    #+#             */
/*   Updated: 2025/05/23 13:01:35 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*copy;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] != '\0' && ft_strchr(set, s1[start]) != NULL)
		start++;
	while (s1[end] != '\0' && (ft_strchr(set, s1[end]) != NULL))
		end--;
	if (start > end)
		return (ft_strdup(""));
	copy = malloc(end - start + 2);
	if (!copy)
		return (NULL);
	ft_memcpy(copy, &s1[start], end - start + 1);
	copy[end - start + 1] = '\0';
	return (copy);
}
