/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 08:03:42 by moel-idr          #+#    #+#             */
/*   Updated: 2024/11/20 09:18:06 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*free_join(char *buffer, char *added_string)
{
	char	*temp;

	temp = ft_strjoin(buffer, added_string);
	free(buffer);
	buffer = NULL;
	return (temp);
}

char	*take_line(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	if (!buffer || !*buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		j = i + 1;
	else
		j = i;
	line = (char *)ft_calloc(j + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*leftovers(char *buffer)
{
	int		i;
	int		j;
	char	*next;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	next = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	if (!next)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		next[j++] = buffer[i++];
	free(buffer);
	return (next);
}

char	*read_line(char *outcome, int fd)
{
	char	buf[BUFFER_SIZE + 1];
	int		num_of_bytes;

	num_of_bytes = 1;
	while (num_of_bytes > 0)
	{
		num_of_bytes = read(fd, buf, BUFFER_SIZE);
		if (num_of_bytes < 0)
		{
			free(outcome);
			outcome = NULL;
			return (NULL);
		}
		buf[num_of_bytes] = 0;
		outcome = free_join(outcome, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (outcome);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer [OPEN_MAX];

	if (BUFFER_SIZE < 1 || read(fd, 0, 0) < 0 || fd < 0)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = read_line(buffer[fd], fd);
	if (!buffer[fd])
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	line = take_line(buffer[fd]);
	buffer[fd] = leftovers(buffer[fd]);
	return (line);
}
