/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:55:01 by mpellegr          #+#    #+#             */
/*   Updated: 2024/05/15 10:00:32 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static size_t	find_nl(char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str && *str)
	{
		if (*str == '\n')
		{
			len++;
			return (len);
		}
		str++;
		len++;
	}
	return (len);
}

static char	*one_line(char *str)
{
	char	*line;
	size_t	n;

	n = 0;
	if (!str[n])
		return (NULL);
	line = (char *)malloc(sizeof(char) * (find_nl(str) + 1));
	if (!line)
		return (NULL);
	while (str[n] != '\0' && str[n] != '\n')
	{
		line[n] = str[n];
		n++;
	}
	if (str[n] == '\n')
	{
		line[n] = '\n';
		n++;
	}
	line[n] = '\0';
	return (line);
}

static char	*cut_buffer(char *buffer)
{
	size_t	start;
	char	*new_buffer;
	size_t	n;

	n = 0;
	start = find_nl(buffer);
	if (!buffer[start])
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	new_buffer = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - start) + 1);
	if (!new_buffer)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	while (buffer[start] != '\0')
		new_buffer[n++] = buffer[start++];
	new_buffer[n] = '\0';
	free(buffer);
	buffer = NULL;
	return (new_buffer);
}

static char	*ft_buffer(char *str, int fd)
{
	char	*fake_buffer;
	ssize_t	bytes_read;

	fake_buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!fake_buffer)
	{
		str = n_f(str, NULL);
		return (NULL);
	}
	bytes_read = BUFFER_SIZE;
	while (!(ft_strchr_with_prot(str, '\n')) && bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, fake_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			str = n_f(str, fake_buffer);
			return (NULL);
		}
		fake_buffer[bytes_read] = '\0';
		str = create_buffer(str, fake_buffer);
		if (!str)
			return (NULL);
	}
	free(fake_buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = ft_buffer(buffer[fd], fd);
	if (!buffer[fd])
		return (NULL);
	line = one_line(buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = cut_buffer(buffer[fd]);
	return (line);
}
