/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 08:03:33 by moel-idr          #+#    #+#             */
/*   Updated: 2024/11/20 08:03:34 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count);
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return ;
	str = (char *)s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	char	*res;
	int		i;
	int		j;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	if (s1)
	{
		while (s1[i] != 0)
		{
			res[i] = s1[i];
			i++;
		}
	}
	j = 0;
	while (s2[j] != 0)
		res[i++] = s2[j++];
	res[len] = 0;
	return (res);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	c = (char)c;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == (char)c)
			return (&((char *)str)[i]);
		i++;
	}
	if (c == '\0')
		return (&((char *)str)[i]);
	return (NULL);
}
