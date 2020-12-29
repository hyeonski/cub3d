/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 14:21:32 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/29 21:39:06 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	size;
	char	*result;

	if (s == 0)
		return (0);
	if ((result = (char *)malloc(sizeof(char) * (len + 1))) == 0)
		return (0);
	size = ft_strlen(s);
	i = 0;
	while (i < len && i + start < size)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = 0;
	return (result);
}
