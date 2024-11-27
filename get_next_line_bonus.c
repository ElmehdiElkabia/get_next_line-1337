/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:44:28 by eelkabia          #+#    #+#             */
/*   Updated: 2024/11/26 18:11:18 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_lines(int fd, char *str, char *buffer)
{
	ssize_t	b_read;
	char	*temp;

	b_read = read(fd, buffer, BUFFER_SIZE);
	while (b_read > 0)
	{
		buffer[b_read] = '\0';
		if (!str)
			str = ft_strdup("");
		temp = ft_strjoin(str, buffer);
		free(str);
		if (!temp)
			return (NULL);
		str = temp;
		if (ft_strchr(buffer, '\n'))
			break ;
		b_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (b_read < 0)
	{
		free(str);
		str = NULL;
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
	if (!str || *str == '\0')
	{
		free(str);
		str = NULL;
	}
	line[i + 1] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str[FD_SIZE];
	char		*line;
	char		*buffer;

	if (fd < 0 || fd >= FD_SIZE || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(str[fd]);
		str[fd] = NULL;
		return (NULL);
	}
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = get_lines(fd, str[fd], buffer);
	free(buffer);
	if (!line)
	{
		free(str[fd]);
		str[fd] = NULL;
		return (NULL);
	}
	str[fd] = get_only_line(line);
	return (line);
}
