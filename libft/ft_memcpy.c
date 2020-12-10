/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 14:16:27 by hyeonski          #+#    #+#             */
/*   Updated: 2020/10/19 16:41:26 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memcpy(void *dest, const void *source, size_t n)
{
	unsigned char	*temp;
	unsigned char	*cpyd;

	if (dest == NULL && source == NULL)
		return (dest);
	temp = (unsigned char *)source;
	cpyd = (unsigned char *)dest;
	while (n)
	{
		*cpyd++ = *temp++;
		n--;
	}
	return (dest);
}
