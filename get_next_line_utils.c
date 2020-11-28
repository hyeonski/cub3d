/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 09:56:53 by hyeonski          #+#    #+#             */
/*   Updated: 2020/10/17 21:11:55 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			ft_strlen(const char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char		*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*result;

	i = 0;
	if (!(result = (char *)malloc(sizeof(char) *
					(ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (0);
	while (*s1)
		result[i++] = *s1++;
	while (*s2)
		result[i++] = *s2++;
	result[i] = '\0';
	return (result);
}

char		*ft_strdup(char *src)
{
	char	*dup;
	int		index;

	if (!(dup = malloc(sizeof(char) * (ft_strlen(src) + 1))))
		return (0);
	index = 0;
	while (src[index] != '\0')
	{
		dup[index] = src[index];
		index++;
	}
	dup[index] = src[index];
	return (dup);
}

char		*ft_substr(char *s, unsigned int start, int len)
{
	int		i;
	int		size;
	char	*result;

	if (s == 0)
		return (0);
	if ((result = (char *)malloc(sizeof(char) * (len + 1))) == 0)
		return (0);
	size = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = 0;
	return (result);
}

char		*ft_strchr(char *str, int c)
{
	if (str == NULL)
		return (0);
	while (*str != c)
	{
		if (!*str)
			return (0);
		str++;
	}
	return (str);
}
