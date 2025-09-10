/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 09:30:35 by kmaeda            #+#    #+#             */
/*   Updated: 2025/06/05 10:47:55 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_fetch(char **stash)
{
	size_t	len;
	size_t	i;
	char	*n_pos;
	char	*line;
	char	*temp;

	len = 0;
	n_pos = ft_strchr_gnl(*stash, '\n');
	if (!n_pos)
	{
		line = *stash;
		*stash = NULL;
		return (line);
	}
	i = n_pos - *stash + 1;
	line = ft_substr_gnl(*stash, 0, i);
	len = ft_strlen_gnl(*stash);
	temp = ft_substr_gnl(*stash, i, len - i + 1);
	free(*stash);
	*stash = temp;
	return (line);
}

static char	*ft_read_fd(int fd, char *stash, int *bytes_read)
{
	char	*buffer;
	char	*temp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	*bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (*bytes_read == -1)
	{
		free(buffer);
		free(stash);
		return (NULL);
	}
	if (*bytes_read == 0)
	{
		free(buffer);
		return (stash);
	}
	buffer[*bytes_read] = '\0';
	temp = ft_strjoin_gnl(stash, buffer);
	free(buffer);
	free(stash);
	if (!temp)
		return (NULL);
	return (temp);
}

char	*get_next_line(int fd)
{
	int			bytes_read;
	static char	*stash;
	char		*line;

	bytes_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_emptystr();
	while (!ft_strchr_gnl(stash, '\n') && bytes_read > 0)
	{
		stash = ft_read_fd(fd, stash, &bytes_read);
		if (!stash)
			return (NULL);
	}
	if (!stash || *stash == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = ft_fetch(&stash);
	return (line);
}
