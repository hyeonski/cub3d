/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 14:20:45 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/29 21:39:06 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t i;
	size_t j;

	if (*to_find == '\0')
		return ((char *)&str[0]);
	i = 0;
	while (str[i] != '\0' && i < n)
	{
		j = 0;
		while (str[i + j] == to_find[j] && i + j < n)
		{
			j++;
			if (to_find[j] == '\0')
				return ((char *)&str[i]);
		}
		i++;
	}
	return (0);
}
