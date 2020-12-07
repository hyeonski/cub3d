/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:13:13 by wpark             #+#    #+#             */
/*   Updated: 2019/12/03 21:23:13 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			i;

	if (n == 0)
		return (0);
	p1 = (unsigned char*)s1;
	p2 = (unsigned char*)s2;
	i = 0;
	while (p1[i] != '\0' && p2[i] != '\0' && i < n - 1
			&& p1[i] == p2[i])
		i++;
	return (p1[i] - p2[i]);
}
