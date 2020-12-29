/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 19:44:21 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/29 20:00:50 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
