/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 14:13:19 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/29 21:39:02 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_calloc(size_t count, size_t size)
{
	void	*result;

	if ((result = malloc(size * count)) == 0)
		return (0);
	ft_memset(result, 0, size * count);
	return (result);
}
