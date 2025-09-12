/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:04:14 by kmaeda            #+#    #+#             */
/*   Updated: 2025/05/23 12:38:33 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *s, char c)
{
	int	word;
	int	i;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			word++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (word);
}

static void	ft_free(char **array, int j)
{
	while (j > 0)
		free(array[--j]);
	free(array);
}

static char	**ft_word_copy(char const *s, char c, char **array)
{
	int	start;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			start = i;
			while (s[i] != c && s[i] != '\0')
				i++;
			array[j] = ft_substr(s, start, i - start);
			if (!array[j])
				return (ft_free(array, j), NULL);
			j++;
		}
	}
	array[j] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	int		word;
	char	**array;

	word = ft_word_count(s, c);
	array = malloc((word + 1) * sizeof (char *));
	if (!array)
		return (NULL);
	return (ft_word_copy(s, c, array));
}
