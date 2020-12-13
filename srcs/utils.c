/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 12:52:33 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/13 16:04:08 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_list_strjoin(t_str_arr *str_arr, char *str)
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

char	**init_chars_array(int row, int col, char c)
{
	char	**ret;
	int		i;

	ret = (char **)malloc(sizeof(char *) * row);
	i = 0;
	while (i < row)
	{
		ret[i] = (char *)malloc(sizeof(char) * col);
		ft_memset(ret[i], c, col);
		++i;
	}
	return (ret);
}

int			is_contain(char c, char *str)
{
	while (*str)
		if (c == *str++)
			return (1);
	return (0);
}

int		ft_2d_arr_size(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		++i;
	return (i);
}

void	free_2d_arr(char **arr, int size)
{
	int i;

	i = 0;
	while (i < size)
		free(arr[i++]);
	free(arr);
}