/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:45:39 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/28 18:53:24 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		is_valid_file_name(char *file_path)
{
	int	len;
	int	ret;

	len = ft_strlen(file_path);
	if (len <= 3)
		return (0);
	while (len - 4 > 0)
	{
		file_path++;
		len--;
	}
	ret = ft_strcmp(file_path, ".cub");
	if (ret != 0)
		return (0);
	return (1);
}

int		is_check_list_completed(int *check_list)
{
	int	i;

	i = 0;
	while (i < 9)
		if (check_list[i++] != 1)
			return (0);
	return (1);
}

int		is_valid_cub(t_str_arr *conf)
{
	int	i;
	int	check_list[9];

	ft_bzero(check_list, sizeof(check_list));
	i = -1;
	while (++i < conf->size)
	{
		if (ft_strlen(conf->elem[i]) == 0)
			continue ;
		if (is_contain(conf->elem[i][0], " 01"))
		{
			if (!is_valid_map(conf, &i, check_list, &g_cub.map))
				return (0);
			break ;
		}
		else if (!is_valid_key(conf->elem[i], check_list))
			return (0);
	}
	while (i < conf->size)
		if (ft_strlen(conf->elem[i++]) != 0)
			return (0);
	return (is_check_list_completed(check_list));
}
