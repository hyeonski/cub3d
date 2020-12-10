/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 16:53:09 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/10 17:35:57 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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


char		**init_map(char **strs, int start, t_map *map)
{
	char	**data;
	int		i;
	int		j;

	data = init_chars_array(map->height, map->width, ' ');
	i = 0;
	j = 0;
	while (i < map->height)
	{
		j = (int)ft_strlen(strs[start + i]);
		while (--j >= 0)
			data[i][j] = strs[start + i][j];
		++i;
	}
	return (data);
}

void	calc_size(t_str_arr *arr, int i, t_map *map)
{
	int			ret_width;
	int			ret_height;
	int			len;

	ret_width = 0;
	ret_height = 0;
	while (i < arr->size &&
			(len = (int)ft_strlen(arr->elem[i])) &&
			is_included(arr->elem[i][0], " 01"))
	{
		++ret_height;
		ret_width = ft_max(ret_width, len);
		++i;
	}
	map->width = ret_width;
	map->height = ret_height;
}
