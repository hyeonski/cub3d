/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:45:28 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/29 20:00:50 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int			check_key(char *key, int *check_list)
{
	int		flag;

	if (!ft_strcmp(key, "R"))
		flag = 0;
	else if (!ft_strcmp(key, "NO"))
		flag = 1;
	else if (!ft_strcmp(key, "SO"))
		flag = 2;
	else if (!ft_strcmp(key, "WE"))
		flag = 3;
	else if (!ft_strcmp(key, "EA"))
		flag = 4;
	else if (!ft_strcmp(key, "S"))
		flag = 5;
	else if (!ft_strcmp(key, "F"))
		flag = 6;
	else if (!ft_strcmp(key, "C"))
		flag = 7;
	else
		return (0);
	if (check_list[flag])
		return (0);
	return (check_list[flag] = 1);
}

int			is_valid_rgb(char *rgb)
{
	int		ret;
	char	**token;
	int		i;
	int		size;

	ret = 0;
	token = ft_split(rgb, ',');
	if ((count_chars(rgb, ',') == 2) && (size = ft_2d_arr_size(token)) == 3)
	{
		i = -1;
		while (++i < 3)
			if (!is_num_str(token[i]) || ft_atoi(token[i]) > 255)
				break ;
		ret = (i == 3);
		free_2d_arr(token, size);
	}
	return (ret);
}

int			check_rfc(char **token, int size)
{
	int		ret;

	ret = 1;
	if (ft_strcmp("R", token[0]) == 0)
		ret = size == 3 && is_num_str(token[1]) && is_num_str(token[2]);
	else if (size != 2)
		ret = 0;
	else if (is_contain(token[0][0], "FC") && !is_valid_rgb(token[1]))
		ret = 0;
	return (ret);
}

int			is_valid_key(char *key, int *check_list)
{
	char	**token;
	int		size;
	int		len;
	int		ret;

	ret = 1;
	token = ft_split(key, ' ');
	if (((size = ft_2d_arr_size(token)) == 1)
			|| !check_key(token[0], check_list))
	{
		free_2d_arr(token, size);
		return (0);
	}
	len = ft_strlen(token[0]);
	if (len == 1)
		ret = check_rfc(token, size);
	else if (size == 2)
		ret = 1;
	free_2d_arr(token, size);
	return (ret);
}
