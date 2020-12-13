/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 16:53:09 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/13 16:10:19 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		set_map(char **strs, int start)
{
	char	**data;
	int		i;
	int		j;

	data = init_chars_array(g_cub.map.height, g_cub.map.width, ' ');
	i = 0;
	j = 0;
	while (i < g_cub.map.height)
	{
		j = ft_strlen(strs[start + i]);
		while (--j >= 0)
			data[i][j] = strs[start + i][j];
		++i;
	}
	g_cub.map.data = data;
}

void	check_map_size(t_str_arr *arr, int i)
{
	int			ret_width;
	int			ret_height;
	int			len;

	ret_width = 0;
	ret_height = 0;
	while (i < arr->size &&
			(len = (int)ft_strlen(arr->elem[i])) &&
			is_contain(arr->elem[i][0], " 01"))
	{
		ret_height++;
		ret_width = (ret_width > len ? ret_width : len);
		i++;
	}
	g_cub.map.width = ret_width;
	g_cub.map.height = ret_height;
}
