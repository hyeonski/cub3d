/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 10:51:01 by wpark             #+#    #+#             */
/*   Updated: 2019/12/03 21:22:39 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	count_digit(unsigned int n)
{
	unsigned int	cnt;

	cnt = 0;
	while (n >= 10)
	{
		n = n / 10;
		cnt++;
	}
	return (cnt + 1);
}

static void			assign_num(unsigned int num, char *ptr)
{
	*ptr-- = '\0';
	if (num == 0)
		*ptr = '0';
	while (num)
	{
		*ptr-- = (num % 10) + '0';
		num = num / 10;
	}
}

char				*ft_itoa(int n)
{
	char			*ret;
	unsigned int	cnt;
	unsigned int	sign;
	unsigned int	num;

	num = (n < 0) ? -n : n;
	sign = (n < 0) ? 1 : 0;
	cnt = count_digit(num);
	if (!(ret = (char*)malloc(sizeof(char) * (cnt + sign + 1))))
		return (0);
	if (sign == 1 && (*ret = '-'))
		assign_num(num, ret + cnt + 1);
	else
		assign_num(num, ret + cnt);
	return (ret);
}
