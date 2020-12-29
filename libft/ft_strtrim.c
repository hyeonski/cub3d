/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 14:21:17 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/29 21:39:06 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		len;
	char		*result;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *(s1)))
		s1++;
	len = ft_strlen(s1);
	while (len && ft_strchr(set, *(s1 + len)))
		len--;
	result = ft_substr((char*)s1, 0, len + 1);
	return (result);
}
