/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 13:27:55 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/28 19:37:36 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			is_contain_only_map_arg(char **map, int width, int height)
{
	int		i;
	int		j;
	char	dir;

	dir = 0;
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			if (!is_map_arg(map[i][j]))
				return (0);
		}
	}
	return (1);
}

int			dfs(char ***map, int i, int j)
{
	int		dir;
	int		node_x;
	int		node_y;

	if (i == g_cub.map.height - 1 || j == g_cub.map.width - 1
			|| (*map)[i][j] == ' ')
		return (0);
	(*map)[i][j] = '1';
	dir = 0;
	while (dir < 4)
	{
		node_x = get_next_dir_x(j, dir);
		node_y = get_next_dir_y(i, dir);
		if ((*map)[node_y][node_x] != '1' && !dfs(map, node_y, node_x))
			return (0);
		dir++;
	}
	return (1);
}

int			is_valid_map_structure(char **map, int width, int height)
{
	int		i;
	int		j;

	i = 1;
	while (i < height)
	{
		j = 1;
		while (j < width)
		{
			if (map[i][j] != ' ' && map[i][j] != '1' && !dfs(&map, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int			is_valid_map(t_str_arr *conf, int *i, int *check_list, t_map *map)
{
	int		ret;

	if (check_list[8])
		return (0);
	check_list[8] = 1;
	ret = 1;
	check_map_size(conf, *i);
	if (map->width < 3 || map->height < 3)
		ret = 0;
	else
	{
		set_map(conf->elem, *i);
		if (!is_contain_only_map_arg(map->data, map->width, map->height)
				|| !is_valid_map_structure(map->data, map->width, map->height))
			ret = 0;
		free_2d_arr(map->data, map->height);
	}
	*i += map->height;
	return (1);
}
