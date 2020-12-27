/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:45:39 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/27 15:58:06 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		is_valid_file_name(char *file_path)
{
	int		len;
	int		ret;

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

int		check_key(char *key, int *check_list)
{
	int flag;
	
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

int	is_num_str(const char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int		count_chars(const char *s, int c)
{
	int cnt;

	cnt = 0;
	while (*s)
	{
		if (*s == c)
			++cnt;
		++s;
	}
	return (cnt);
}


int	is_valid_rgb(char *str)
{
	int		ret;
	char	**token;
	int		i;
	int		size;

	ret = 0;
	token = ft_split(str, ',');
	if ((count_chars(str, ',') == 2) && (size = ft_2d_arr_size(token)) == 3)
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

int		check_rfc(char **token, int size)
{
	int ret;

	ret = 1;
	if (ft_strcmp("R", token[0]) == 0)
		ret = size == 3 && is_num_str(token[1]) && is_num_str(token[2]);
	else if (size != 2)
		ret = 0;
	else if (is_contain(token[0][0], "FC") && !is_valid_rgb(token[1]))
		ret = 0;
	return (ret);
}

int		is_valid_key(char *key, int *check_list)
{
	char **token;
	int size;
	int	len;
	int	ret;
	
	ret = 1;
	token = ft_split(key, ' ');
	if (((size = ft_2d_arr_size(token)) == 1) || !check_key(token[0], check_list))
	{
		free_2d_arr(token, size);
		return (0);
	}
	len = ft_strlen(token[0]);
	if (len == 1)
		ret = check_rfc(token, size);
	else
		if (size == 2)
			ret = 1;
	free_2d_arr(token, size);
	return (ret);
}

int			is_valid_map(t_str_arr *conf, int *i, int *check_list, t_map *map)
{
	int			ret;

	if (check_list[8])
		return (0);
	check_list[8] = 1;
	ret = 1;
	check_map_size(conf, *i);
	if (map->width < 3 || map->height < 3)
		ret = 0;
	return (1);
}

int is_check_list_completed(int *check_list)
{
	int i;

	i = 0;
	while (i < 9)
		if (check_list[i++] != 1)
			return (0);
	return (1);
}

int		is_valid_cub(t_str_arr *conf)
{
	int i;
	int	check_list[9];

	ft_bzero(check_list, sizeof(check_list));
	i = 0;
	while (i < conf->size)
	{
		if (ft_strlen(conf->elem[i]) == 0)
		{
			i++;
			continue ;
		}
		if (is_contain(conf->elem[i][0], " 01"))
		{
			if (!is_valid_map(conf, &i, check_list, &g_cub.map))
				return (0);
			break ;
		}
		else if (!is_valid_key(conf->elem[i], check_list))
			return (0);
		i++;
	}
	// while (i < conf->size)
	// 	if (ft_strlen(conf->elem[i++]) != 0)
	// 		return (0);
	return (is_check_list_completed(check_list));
}