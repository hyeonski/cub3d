/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 12:52:33 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/29 20:00:50 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int			ft_list_strjoin(t_str_arr *str_arr, char *str)
{
	char	**temp_elem;
	int		i;

	if (!(temp_elem = (char **)malloc(sizeof(char *) * (str_arr->size + 1))))
		return (0);
	i = 0;
	while (i < str_arr->size)
	{
		temp_elem[i] = str_arr->elem[i];
		i++;
	}
	temp_elem[i] = ft_strdup(str);
	if (str_arr->elem)
		free(str_arr->elem);
	str_arr->size += 1;
	str_arr->elem = temp_elem;
	return (1);
}

int			is_contain(char c, char *str)
{
	while (*str)
		if (c == *str++)
			return (1);
	return (0);
}

int			is_num_str(const char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int			count_chars(const char *s, int c)
{
	int		cnt;

	cnt = 0;
	while (*s)
	{
		if (*s == c)
			++cnt;
		++s;
	}
	return (cnt);
}

void		update_img_from_buf(t_window *window, int *data)
{
	int		x;
	int		y;

	y = 0;
	while (y < window->height)
	{
		x = 0;
		while (x < window->width)
		{
			data[y * window->width + x] = window->buf[y][x];
			x++;
		}
		y++;
	}
}
