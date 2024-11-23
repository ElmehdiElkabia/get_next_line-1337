/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:44:28 by eelkabia          #+#    #+#             */
/*   Updated: 2024/11/23 11:58:49 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_lines(int fd, char *str, char *buffer)
{
	ssize_t	b_read;

	b_read = read(fd, buffer, BUFFER_SIZE);
	if (b_read < 0)
	{
		free(str);
		return (NULL);
	}
	while (b_read > 0)
	{
		if (b_read == 0)
			break ;
		buffer[b_read] = '\0';
		if (!str)
			str = ft_strdup("");
		str = ft_strjoin(str, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
		b_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (str);
}

static char	*get_only_line(char *line)
{
	int		i;
	char	*str;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (NULL);
	str = ft_strdup(line + i + 1);
	if (!str)
		return (NULL);
	if (*str == '\0')
	{
		free(str);
		str = NULL;
	}
	line[i + 1] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = get_lines(fd, str, buffer);
	if (!line)
		return (NULL);
	free(buffer);
	str = get_only_line(line);
	return (line);
}
