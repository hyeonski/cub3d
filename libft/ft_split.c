/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 14:18:24 by hyeonski          #+#    #+#             */
/*   Updated: 2020/10/11 21:05:59 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**drr_init(char const *s, char c, int *wd_cnt)
{
	int		i;
	int		key;
	char	**result;

	key = 0;
	*wd_cnt = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && key == 0)
		{
			key = 1;
			(*wd_cnt)++;
		}
		else if (s[i] == c)
			key = 0;
		i++;
	}
	if (!(result = (char **)malloc(sizeof(char *) * (*wd_cnt + 1))))
	{
		free(result);
		return (0);
	}
	return (result);
}

static char	*put_result(char const *s, int start, int end)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (str == 0)
	{
		free(str);
		return (0);
	}
	while (start < end)
		str[i++] = s[start++];
	str[i] = 0;
	return (str);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		k;
	int		wd_cnt;
	int		start;
	char	**result;

	i = 0;
	k = 0;
	if (s == 0)
		return (0);
	result = drr_init(s, c, &wd_cnt);
	if (result == 0)
		return (0);
	while (k < wd_cnt)
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		result[k++] = put_result(s, start, i);
		i++;
	}
	result[k] = 0;
	return (result);
}
