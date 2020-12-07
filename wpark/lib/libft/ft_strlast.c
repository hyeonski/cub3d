/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:23:06 by wpark             #+#    #+#             */
/*   Updated: 2019/12/03 21:23:06 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlast(char const *str, char const *last)
{
	int	len;
	int	l_len;

	len = ft_strlen(str);
	l_len = ft_strlen(last);
	if (l_len > len)
		return (0);
	return (!ft_strcmp(str + len - l_len, last));
}
